#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct mesg_buffer{
        long mesg_type;
        char mesg_char[100];
}message;
int main(int argc, char *argv[]){
        if(argc!=2){
                printf("System include message<type>%s",argv[0]);
                return 1;
        }
        key_t key=ftok("progfile",65);
        int msgid=msgget(key, IPC_CREAT |0666);
        int type=atoi(argv[1]);

        msgrcv(msgid,&message,sizeof(message.mesg_char),type,0);
        printf("Reciever %d got: %s\n",type,message.mesg_char);
        return 0;
}
