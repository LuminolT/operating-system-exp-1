#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int i, j;
    printf("My pid is %d, my father's pid is %d\n", getpid(), getppid());
    for (i = 0; i < 3; i++) {
        if (fork() == 0)
            printf("%d pid=%d ppid=%d\n", i, getpid(), getppid());
        else {
            j = wait(0);
            printf("%d:The chile %d is finished.\n", getpid(), j);
        }
    }
    // int k;
    // scanf("%d", &k);
    return 0;
}

/*
思考 1:
家族树：
\-+= 30945
  |-+- 30946
  | |-+- 30949
  | | \--- 30952
  | \--- 30951
  |-+- 30947
  | \--- 30950
  \--- 30948

子进程被创建后将由内核分配一个进程表项和进程标识符，检查同时运行的进程数目，并且拷贝进程表项的数据，由子进程继承父进程所有文件。

反复运行此程序，初始的进程的 ppid 保持不变，运行一次共创建 8 个进程，pid
均不相同，初始进程的父进程是用户使用的 SHELL 进程，初始进程与其后 fork() 产生的子进程的 pid
逐渐递增。
*/