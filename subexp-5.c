#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
int glob=5;
int main()
{
    int var=15;
    pid_t fpid=fork();
    if (fpid<0)
    {
        printf("fork error!\n");
        exit(0);
    }
    else if(fpid==0)
    {
        glob++;
        var--;
        printf("Child %d have changed the var and glob value!\n",getpid());
        printf("My pid=%d, glob=%d and var=%d !\n",getpid(),glob,var);
        exit(0);
    }
    else
    {
        wait(0);
        printf("Parent %d did not changed the var and glob values.\n",getpid());
        printf("My pid=%d, glob=%d and var=%d !\n",getpid(),glob,var);
        exit(0);
    }
    return 0;
}


/*
思考题
子进程被创建后，对父进程的运行环境无影响。因为子进程被创建后，他拥有独立的代码段和数据段，并可以对其单独修改。
而父进程的代码段和数据段不会随着子进程代码段和数据段的改变而受到影响。
*/