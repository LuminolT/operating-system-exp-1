#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
int main()
{
    int child_pid1 ,child_pid2,child_pid3;
    int pid,status;
    setbuf(stdout,NULL);
    child_pid1=fork();
    /*创建子进程1*/
    if(child_pid1==0)
    { 
        execlp("echo","echo" ,"child process 1",(char *)0);
        perror("exec1 error.\n ");
        exit(1);
    }
    child_pid2=fork();
    /*创建子进程2*/
    if(child_pid2==0)
    { 
        execlp("date","date" ,(char *)0);
        /*子进程2启动其它程序*/
        perror("exec2 error.In ");
        exit(2); 
    }
    child_pid3=fork();
    /*创建子进程3*/
    if(child_pid3==0)
    { 
        execlp("ls","ls", (char *)0);
        perror("exec3 error.n ");
        exit(3);
        puts("Parent process is waiting for chile process return!");
    }
    while((pid=wait(0))!=-1)
    { 
        if(child_pid1==pid)
        /*若子进程1结束*/
        printf("child process 1 terminated with status %d\n",(status>>8));
        else
        {
            if(child_pid2==pid)
            /*若子进程2结束*/
            printf("child process 2 terminated with status %d\n",(status>>8));
        else
        { 
            if(child_pid3==pid)
            /*若子进程3结束*/
            printf("child process 3 terminated with status %d\n" ,(status>>8));
        }
        }
    }
    puts("All child processes terminated.");
    puts("Parent process terminated.");
    exit(0);
}
//思考题
//子进程运行其他程序后，新程序将取代这个进程，但是进程标识号不改变，
//但旧进程的其他信息，代码段，数据段，栈段等均被新程序的信息所代替。新程序从自己的main()函数开始进行。
//反复运行此程序发现运行结束的先后次序是不可预知的，那是因为子进程运行的顺序是不可预知的，所以那些新程序结束的先后次序会发生改变。
