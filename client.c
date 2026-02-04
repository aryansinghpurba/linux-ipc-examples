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
 key=ftok("progfile",65);
 message.mesg_type=1;
 msgid=msgget(key,0666|IPC_CREAT);
 msgrcv(msgid,&message,sizeof(message),1,0);//recieving message
 printf("the message recieved is %s",message.mesg_char);
 msgctl(msgid,IPC_RMID,NULL);//deleting the message queue
 return 0;
}
