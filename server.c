// server.c
#include <stdio.h>      
#include <sys/ipc.h>    
#include <sys/msg.h>    

#define MAX 10          

// Structure for message queue
struct mesg_buffer {
    long mesg_type;      // Message type (must be > 0)
    char mesg_char[100]; // Message data
} message;

int main() {
    key_t key;           // Key to identify the message queue
    int msgid;           // Message queue ID

    // Set message type
    message.mesg_type = 1;

    // Generate a unique key using file name and project ID
    key = ftok("progfile", 65);

    // Create a new message queue or get existing one
    // 0666 → read/write permissions
    // IPC_CREAT → create queue if it does not exist
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Ask user to enter the message
    printf("The message to be sent is: ");

    // Read input message from standard input
    // MAX limits how many characters are read
    fgets(message.mesg_char, MAX, stdin);

    // Send message to the queue
    // sizeof(message.mesg_char) → size of message text
    // 0 → default flags (blocking send)
    msgsnd(msgid, &message, sizeof(message.mesg_char), 0);

    // Print the sent message
    printf("The message sent is: %s", message.mesg_char);

    return 0;
}
