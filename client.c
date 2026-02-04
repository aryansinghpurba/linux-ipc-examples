#include <stdio.h>      
#include <sys/ipc.h>    
#include <sys/msg.h>    

#define MAX 10          

// Structure for message queue
struct mesg_buffer {
    long mesg_type;     // Message type (must be > 0)
    char mesg_char[100]; // Message data (text)
} message;

int main() {
    key_t key;          // Key to identify the message queue
    int msgid;          // Message queue ID

    // Generate a unique key using a file name and project ID
    key = ftok("progfile", 65);

    // Set message type (receiver will read this type)
    message.mesg_type = 1;

    // Create a message queue or get existing one
    // 0666 → read & write permissions for everyone
    // IPC_CREAT → create queue if it doesn't exist
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive message from the queue
    // sizeof(message) → size of message 
    // 1 → receive message of type 1
    // 0 → blocking call (wait until message arrives)
    msgrcv(msgid, &message, sizeof(message.mesg_char), 1, 0);

    // Print the received message
    printf("The message received is: %s\n", message.mesg_char);

    // Remove (delete) the message queue from the system
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

