#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<sys/types.h>

#define TIMEOUT 5
#define BUF_LEN 1024

int main()
{
    struct timeval tv;
	fd_set readfds;
	int ret;
	char buf[BUF_LEN] = {0};
	int len = 0;

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
    
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	ret = select(STDIN_FILENO+1, &readfds, NULL, NULL, &tv);
	if(-1 == ret)
	{
	     printf("select error, %s\n",strerror(errno));
		 return -1;
	}
	else if(0 == ret)
	{
	    printf("Timeout.\n");
		return -1;
	}
    
	if(FD_ISSET(STDIN_FILENO, &readfds))
	{
	    len = read(STDIN_FILENO, buf, BUF_LEN);
		if(-1 == len)
		{
		    printf("read contents from STDIN fail.\n");
			return -1;
		}
		if(len)
		{
		    buf[len] = '\0';
			printf("read contents is:%s\n",buf);
		}
	}
    return 0;
}
