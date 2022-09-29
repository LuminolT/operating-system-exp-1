#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int i;
    pid_t fpid = fork();
    if (fpid) {
        i = wait(0);  // Wait for sub-process to exit
        printf("It is parent process.\n");
        printf("My pid is %d, ppid is %d.\n", getpid(), getppid());
        printf("The child process, ID number%d, is finished.\n", i);
        exit(0);
    } else {
        printf("It is child process.\n");
        printf("My pid is %d, ppid is %d.\n", getpid(), getppid());
        sleep(3);
        exit(0);
    }

    return 0;
}

/*
思考题
子进程由父进程通过fork()函数创建产生，通过exit()函数或者主函数的return()自我结束。
子进程被创建后，核心为其分配一个进程表项和进程标识符pid，检查同时运行的进程数目，并拷贝父进程的进程表项的数据，由子进程继承父进程的所有文件。
*/