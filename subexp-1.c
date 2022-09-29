#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Process ID：%d\nUser ID：%d\nGroup ID: %d\n", getpid(), getuid(), getgid());

    sleep(1);

    if (fork() == 0) {
        execlp("ls", "ls", (char *)0);
        exit(1);
    }

    wait(0);

    printf("Do you want to quit?(Y/N)\n");

    char option;

    printf("Process still exist.\n");

    for (;;) {
        scanf("%c", &option);

        getchar();

        if (option == 'y' || option == 'Y') {
            exit(0);
        }

        printf("Process still exist.\n");
        printf("%d", getpid());
    }
}