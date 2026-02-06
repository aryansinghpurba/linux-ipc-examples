#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/stat.h>
int main(){
        sem_t *sem;
        sem=sem_open("/mysem",O_CREAT,0644,1);
        printf("Waiting\n");
        sem_wait(sem);
        printf("Entering critical section pid:%d\n",getpid());
        sleep(5);
        printf("leaving critical section pid:%d\n",getpid());
        sem_post(sem);
        sem_close(sem);
        sem_unlink("mysem");
}
