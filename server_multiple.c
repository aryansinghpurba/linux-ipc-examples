#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg {
    long mtype;
    int client_id;
    char text[100];
};

int main() {
    key_t key = ftok("progfile", 65);

    // Clean old queue if exists
    int old = msgget(key, 0666);
    if (old != -1) {
        msgctl(old, IPC_RMID, NULL);
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg message;
    int clients[50];
    int count = 0;

    printf("Server running...\n");

    // Handle client registrations in background
    while (1) {
        // Non-blocking registration receive
        while (msgrcv(msgid, &message,
                      sizeof(message) - sizeof(long),
                      1, IPC_NOWAIT) > 0) {

            int exists = 0;
            for (int i = 0; i < count; i++) {
                if (clients[i] == message.client_id)
                    exists = 1;
            }

            if (!exists) {
                clients[count++] = message.client_id;
                printf("Client %d registered. Total online: %d\n",
                       message.client_id, count);
            }
        }

        int target;
        char buffer[100];

        printf("Enter <client_id> <message>: ");
        fflush(stdout);

        // WAIT for user input (this blocks, prevents spam)
        if (scanf("%d %[^\n]", &target, buffer) == 2) {
            message.mtype = target;
            strcpy(message.text, buffer);

            msgsnd(msgid, &message,
                   sizeof(message) - sizeof(long), 0);
        }
    }
}
