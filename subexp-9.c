#include<unistd.h>
#include<stdio.h>
//#include<sys/types.h>
//#include<sys/stat.h>
#include<stdlib.h>
#include<signal.h>

void * func()
{
	int m;
	m=getpid();
	printf("I am Process %d: It is signal 18 processing function.\n",m);
}


int main() {
	int i,j,k;
	signal(18,func());
	while((i=fork())==-1);
	if(i==0)
	{
//		sleep(1000);
		printf("Child %d: A signal from my parent is received.\n",getpid());
	}
	else
	{
		j=kill(i,18);
		printf("Parent: signal 18 has been sent to child %d,returned %d.\n",i,j);
		k=waitpid(i,NULL,WNOHANG);
		printf("After wait %d,Parent %d: finished.\n",k,getpid());
		exit(0);
	}
}

/*
思考：
软中断是执行中断指令产生的，而硬中断是由外设引发的；硬中断的中断号是由中断控制器提供的，软中断的中断号由指令直接指出，无需使用中断控制器；硬中断是可屏蔽的，软中断不可屏蔽；硬中断处理程序要确保它能快速地完成任务，这样程序执行时才不会等待较长时间，称为上半部；软中断处理硬中断未完成的工作，是一种推后执行的机制，属于下半部。
*/
