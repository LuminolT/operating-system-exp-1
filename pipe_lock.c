#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

extern int errno;

int test_1(){
	int i, p, r, fd[2];
	char buf[50], s_buf[50];
	pipe(fd);
	printf("test: \nchild process use lockf then parent process write.\n\n");
	while((p=fork()) == -1);
	if(p == 0){
		printf("child process awaken\n\n");
		printf("trying to lock pipe. \n");
		if((r = lockf(fd[1],1,0)) == 0)					// 锁上写
			printf("pipe write has been locked. \n");
		else{
			printf("value of return: %d\n", r);
			printf("value of errno: %d\n", errno);
			printf("error opening file: %s\n", strerror(errno));
		}
		sprintf(buf, "child process write in the pipe. \n");
		sleep(4);
		if (read(fd[0], s_buf, 50) == -1)
			printf("Can't read pipe. \n");
		else
			printf("\nread from pipe: %s \n", s_buf);
		sleep(2);
		printf("trying to unlock pipe. \n");
		if((r = lockf(fd[1],0,0)) == 0)
			printf("pipe write has been unlocked. \n");
		else{
			printf("value of return: %d\n", r);
			printf("value of errno: %d\n", errno);
			printf("error opening file: %s\n", strerror(errno));
		}
		exit(0);
	}
	else{
		sleep(2);
		printf("\nparent process has slept 1. \n");
		sprintf(buf, "parent process rewrite the pipe! \n");
		write(fd[1], buf, 50);
		sleep(8);
		exit(0);
	}
}

int test_2(){
	int i, p, r, fd[2];
	char buf[50], s_buf[50];
	pipe(fd);
	printf("test: \nparent process use lockf then child process write.\n\n");
	while((p=fork()) == -1);
	if(p == 0){
		printf("child process awaken\n");
		sleep(2);
		printf("\nchild process has slept 1. \n");
		sprintf(buf, "child process rewrite the pipe! \n");
		write(fd[1], buf, 50);
		exit(0);
	}
	else{
		printf("trying to lock pipe. \n");
		if((r = lockf(fd[1],1,0)) == 0)					// 锁上写
			printf("pipe write has been locked. \n");
		else{
			printf("value of return: %d\n", r);
			printf("value of errno: %d\n", errno);
			printf("error opening file: %s\n", strerror(errno));
		}
		sprintf(buf, "parent process write in the pipe. \n");
		sleep(4);
		if (read(fd[0], s_buf, 50) == -1)
			printf("Can't read pipe. \n");
		else
			printf("\nread from pipe: %s \n", s_buf);
		sleep(2);
		printf("trying to unlock pipe. \n");
		if((r = lockf(fd[1],0,0)) == 0)
			printf("pipe write has been unlocked. \n");
		else{
			printf("value of return: %d\n", r);
			printf("value of errno: %d\n", errno);
			printf("error opening file: %s\n", strerror(errno));
		}
		exit(0);
	}
}

int main(){
	test_1();
	return 0;
}

// test_out:
// child process use lockf then parent process write.
//
// child process awaken
//
// trying to lock pipe.
// value of return: -1
// value of errno: 9
// error opening file: Bad file descriptor
//
// parent process has slept 1.
//
// read from pipe: parent process rewrite the pipe!
//
// trying to unlock pipe.
// value of return: -1
// value of errno: 9
// error opening file: Bad file descriptor