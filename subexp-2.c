#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    int i;
    pid_t fpid=fork();
    if(fpid)
    {
        i=wait (0);
        printf("It is parent process.\n");
        printf("My pid is %d, ppid is %d.\n", getpid(), getppid());
        printf("The child process, ID number%d, is finished.\n",i);
        exit(0);
    }
    else
    {
        printf("It is child process.\n");
        printf("My pid is %d, ppid is %d.\n", getpid(), getppid());
        sleep(3);
        exit(0);
    }
}