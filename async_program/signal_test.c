#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void signal_handle(int signo)
{
	printf("Receive the signal number: %d\n", signo);
}

int main()
{
	printf("current process id is:%d\n", getpid());
	
	signal(SIGINT, signal_handle);
	signal(SIGHUP, signal_handle);
	signal(SIGQUIT, signal_handle);
	getchar();
	return 0;	
}
