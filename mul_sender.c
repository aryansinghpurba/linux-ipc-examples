#include<stdio.h>
#include<sys/msg.h>
#include<string.h>
struct mesg_buffer{
        long mesg_type;
        char mesg_text[100];
}message;
int main(){
        key_t key;
        int msgid;
        key=ftok("progfile",65);
        msgid=msgget(key,IPC_CREAT | 0666);

        message.mesg_type=1;
        strcpy(message.mesg_text,"hello from reciever 1");
        msgsnd(msgid,&message,sizeof(message.mesg_text),0);

        message.mesg_type=2;
        strcpy(message.mesg_text,"hello from reciever 2");
        msgsnd(msgid,&message,sizeof(message.mesg_text),0);

        printf("the messages are sent successfully");
        msgctl(msgid,IPC_RMID,NULL);
        return 0;
}
