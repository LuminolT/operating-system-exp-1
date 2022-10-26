#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int child_pid1, child_pid2, child_pid3;
    int pid, status;
    // printf("%d\n", status);
    setbuf(stdout, NULL);
    child_pid1 = fork();
    /*创建子进程1*/
    if (child_pid1 == 0) {
        printf("1");
        exit(0);
    }
    child_pid2 = fork();
    /*创建子进程2*/
    if (child_pid2 == 0) {
        printf("2");
        exit(0);
    }
    child_pid3 = fork();
    /*创建子进程3*/
    if (child_pid3 == 0) {
        printf("3");
        exit(0);
    }
    return 0;
}
//思考题
//子进程运行其他程序后，新程序将取代这个进程，但是进程标识号不改变，
//但旧进程的其他信息，代码段，数据段，栈段等均被新程序的信息所代替。新程序从自己的main()函数开始进行。
//反复运行此程序发现运行结束的先后次序是不可预知的，那是因为子进程运行的顺序是不可预知的，所以那些新程序结束的先后次序会发生改变。