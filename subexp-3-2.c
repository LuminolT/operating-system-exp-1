#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int i, j;
    printf("My pid is %d, my father's pid is %d\n", getpid(), getppid());
    for (i = 0; i < 3; i++) {
        if (fork() == 0)
            printf("%d pid=%d ppid=%d\n", i, getpid(), getppid());
        else
            break;
    }
    int k;
    scanf("%d", &k);
    return 0;
}

/*
思考 2:
家族树：
\-+= 33016
  \-+- 33017
    \-+- 33018
      \--- 33019

程序将 wait() 函数替换为 break 语句，即程序在 for
循环中创建子进程后跳出循环，即每个父进程只产生一个子进程，实现单分支结构。
*/