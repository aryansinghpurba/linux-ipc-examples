#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct msg {
    long mtype;
    int client_id;
    char text[100];
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <client_id>\n", argv[0]);
        return 1;
    }

    int client_id = atoi(argv[1]);

    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg message;

    // Register with server (type 1)
    message.mtype = 1;
    message.client_id = client_id;
    msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);

    printf("Client %d online. Waiting for messages...\n", client_id);

    while (1) {
        // BLOCK until message for THIS client arrives
        msgrcv(msgid, &message,
               sizeof(message) - sizeof(long),
               client_id, 0);

        printf("Client %d received: %s\n",
               client_id, message.text);
    }
}
