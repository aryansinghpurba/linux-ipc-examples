//server.c
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10

struct mesg_buffer{
 long mesg_type;
 char mesg_char[100];
}message;

int main(){
 key_t key;
 int msgid;
 message.mesg_type=1;
 key=ftok("progfile",65);//generating key
 msgid=msgget(key,0666|IPC_CREAT); //msgid is generated
 printf("the message to be sent is: ");
 fgets(message.mesg_char,MAX,stdin);//fetch the message to be sent
 msgsnd(msgid,&message,sizeof(message.mesg_char),0);//sending the message
 printf("the message sent is : %s",message.mesg_char);//printing message
 return 0;
}
