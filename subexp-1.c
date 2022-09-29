#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// int main() {
//     pid_t pid;
//     pid = fork();
//     int info;
//     int i = wait(&info);
//     if (pid == 0) {
//         printf("SOn, pid = %d, %d\n", getpid(), pid);
//     }
//     else {
//         printf("Dad, pid = %d,.%d\n", getpid(), pid);
//     }

//     printf("%d %d\n", i, info);
//     return 0;
// }
int main() {
    printf("进程标识：%d\n真实用户标识：%d\n真实组标识: %d\n", getpid(), getuid(), getgid());
    // int x;
    // scanf("%d",&x);
    int i = fork();
    if (!i)  //是子进程
    {
        // sleep(1);
        execlp("ls", "ls", (char *)0);
        exit(1);
    }
    int j = wait(0);
    printf("Do you want to quit?(Y/N)\n");
    char option;
    scanf("%c", &option);
    if (option == 'y' || option == 'Y')
        exit(0);
}