#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int i, r, j, k, l, p1, p2, fd[2];  // fd[1]专用于写，fd[0]专用于读
    char buf[50], s[50];
    pipe(fd);
    /*建立一个管道fd*/
    while ((p1 = fork()) == -1)
        ;
    /*创建 子进程1*/
    if (p1 == 0) {
        /*子进程1执行*/
        lockf(fd[1], 1, 0);
        /*管道写入端加锁*/
        sprintf(buf, "Child process P1 is sending messages!\n");
        printf("Child process P1!\n");
        write(fd[1], buf, 50);
        /*信息写入管道*/
        lockf(fd[1], 0, 0);
        /*管道写 入端解锁*/
        sleep(5);
        printf("P1 %d is weakup.My parent process ID is %d.\n", getpid(), getppid());
        exit(0);
    } else {
        while ((p2 = fork()) == -1)
            ;
        /*创建子进程2*/
        if (p2 == 0) {
            lockf(fd[1], 1, 0);
            /*子进程2执行*/
            /*管道写入端加锁*/
            sprintf(buf, "Child process P2 is sending messages!\n ");
            printf("Child process P2!\n");
            write(fd[1], buf, 50);
            /*信息写入管道*/
            lockf(fd[1], 0, 0);
            /*管道写 入端解锁*/
            sleep(5);
            printf("P2 %d is weakup.My parent process ID is %d.\n", getpid(), getppid());
            exit(0);
        }

        else {
            l = getpid();
            // wait(0); /*等 待被唤醒*/
            if ((r = read(fd[0], s, 50) == -1))
                printf("Can't read pipe.\n");
            else
                printf("Parent %d:%s \n", l, s);
            // wait(0); /*等 待被唤醒*/
            if ((r = read(fd[0], s, 50) == -1))
                printf("Can't read pipe.\n");
            else
                printf("Parent %d:%s \n ", l, s);
            exit(0);
        }
    }
}
//通过去除样例代码的wait语句，使得子进程不能保证在父进程之前运行完毕，当父进程结束后子进程会成为孤儿进程，孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集工作，即init成为了其新的父进程。