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

int main()
{
    int msgqid,pid,*pint;
    msgqid=msgget(MSGKEY,0777);
    pid=getpid();
    pint=(int*)msg.mtext;
    *pint=getpid();
    msg.mtype=1;
    msgsnd(msgqid,&msg,sizeof(int),0);
    msgrcv(msgqid,&msg,256,pid,0);
    printf("Client:receive from pid %d.\n",*pint);
    msgrcv(msgqid,&msg,256,pid,0);
    printf("Client:receive from ppid %d.\n",*pint);
    return 0;
}