#include<unistd.h>
#include<stdio.h>
//#include<sys/types.h>
//#include<sys/stat.h>
#include<stdlib.h>
int main()
{
	int /*i,r,*/j,k,l,p1,p2,fd[2];
	char buf[50],s[50], buf_send[50];
	pipe(fd);
	while((p1=fork())==-1);
	if(p1==0)
	{
		printf("Child process P1! \n");
		j=getpid();
		k=getppid();
		printf("P1 %d is wakeup. My parent process ID is %d.\n",j,k);
		if(read(fd[0],s,50)==-1)
			printf("Can't read pipe. \n");
		else
			printf("Child %d: %s \n",j,s);
		lockf(fd[1],1,0);
		sprintf(buf,"Child process P1 is sending messages! \n");
		write(fd[1],buf,50);
		lockf(fd[1],0,0);
		exit(0);
	}
	else
	{
		while((p2=fork())==-1);
		if(p2==0)
		{
			sleep(5);
			printf("Child process P2! \n");
			j=getpid();
			k=getppid();
			printf("P2 %d is wakeup. My parent process ID is %d.\n",j,k);
			if(read(fd[0],s,50)==-1)
				printf("Can't read pipe. \n");
			else
				printf("Child %d: %s \n",j,s);
			lockf(fd[1],1,0);
			sprintf(buf,"Child process P2 is sending messages! \n");
			write(fd[1],buf,50);
			lockf(fd[1],0,0);
//			sleep(5);
			exit(0);
		}
		else
		{
			l=getpid();
			lockf(fd[1],1,0);
			sprintf(buf_send,"Parent process %d is sending message to P1! \n", l);
			write(fd[1],buf_send,50);
			lockf(fd[1],0,0);
			wait(0);
			if(read(fd[0],s,50)==-1)
				printf("Can't read pipe. \n");
			else
				printf("Parent %d: %s \n",l,s);
			sleep(5);
			lockf(fd[1],1,0);
			sprintf(buf_send,"Parent process %d is sending message to P2! \n", l);
			write(fd[1],buf_send,50);
			lockf(fd[1],0,0);
			wait(0);
			if(read(fd[0],s,50)==-1)
				printf("Can't read pipe. \n");
			else
				printf("Parent %d: %s \n",l,s);
			exit(0);
		}
	}
}

/*
思考 1：
管道是连接读写进程的一个特殊文件，允许进程按先进先出传送数据，也能使进程同步执行操作。
父进程创建管道，得到两个文件描述符指向管道的两端；父进程使用 fork 创建子进程，子进程也有两个文件描述符指向同一个管道。此时，可以是父进程往管道里写，子进程从管道里面读；也可以是子进程往管道里写，父进程从管道里面读。这两条通路都是可选的，但是不能都选。

思考 2：
通过调整 sleep() 函数的位置，可以控制子进程 1、2 发送信息的顺序。这是通过 sleep() 函数挂起某一进程，延缓进程执行写入管道实现的。如果 sleep()使用不当，会使进程发送、接受信息混乱，甚至由于挂起错过读取管道内信息。

思考 3：
加锁、解锁确保了同一时刻只有一个进程能使用管道的写或堵操作，如果不使用 lockf() 函数，可能引发管道使用的冲突。
*/