#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 75
struct msgform
{
    long mtype;
    char mtext[256];
}msg;

int msgqid;

int main()
{
    int pid, *pint;
    extern cleanup();
    for (int i = 0; i < 20; i++)
    {
        signal(i,cleanup);
    }
    msgqid=msgget(MSGKEY, 0777|IPC_CREAT);
    while (1)
    {
        msgrcv(msgqid,&msg,256,1,0);
        pint=(int *)msg.mtext;
        pid=*pint;
        printf("Server: receive from pid %d.\n",pid);
        msg.mtype=pid;
        *pint=getpid();
        msgsnd(msgqid,&msg,sizeof(int),0);
        *pint=getppid();
        msgsnd(msgqid,&msg,sizeof(int),0);
    }
    
    return 0;
}

cleanup()
{
    msgctl(msgqid,IPC_RMID,0);
    exit(0);
}