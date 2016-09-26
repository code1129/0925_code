#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define TIMEOUT 5000
#define BUF_LEN 1024

int main()
{
    struct timeval tv;
	fd_set readfds;
	int ret;
	char buf[BUF_LEN] = {0};
	int len = 0;
	int fd_1 = -1,fd_2 = -1,fd_3 = -1;
    int count =0;
    int fd_max = 0;

	fd_1 = open("file_1.txt",O_RDWR|O_CREAT, 0755);
	fd_2 = open("file_2.txt",O_RDWR|O_CREAT, 0755);
	fd_3 = open("file_3.txt",O_RDWR|O_CREAT, 0755);
    
	if(-1 == fd_1)
	{
	    goto exit_1;
	}
	if(-1 == fd_2)
	{
	    goto exit_2;
	}
	if(-1 == fd_3)
	{
	    goto exit_3;
	}
	
	printf("create files success.\n");


	FD_ZERO(&readfds);
	FD_SET(fd_1, &readfds);
	FD_SET(fd_2, &readfds);
	FD_SET(fd_3, &readfds);
    

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
    fd_max =  ( ((fd_1 > fd_2)? fd_1 :fd_2) > fd_3) ?((fd_1 > fd_2)? fd_1 :fd_2):fd_3;
    
	printf("fd1 %d, fd2 %d, fd3 %d, max one %d\n",fd_1,fd_2,fd_3,fd_max);
	ret = select(fd_max+1, &readfds, NULL, NULL, &tv);
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
    
	do{
		  sleep(2);
	if(FD_ISSET(fd_1, &readfds))
	{
	    len = read(fd_1, buf, BUF_LEN);
		if(-1 == len)
		{
		    printf("read contents from STDIN fail.\n");
		}
		if(len)
		{
		    buf[len] = '\0';
			printf("read contents is:%s\n",buf);
		}
	}
	if(FD_ISSET(fd_2, &readfds))
	{
	    len = read(fd_2, buf, BUF_LEN);
		if(-1 == len)
		{
		    printf("read contents from STDIN fail.\n");
		}
		if(len)
		{
		    buf[len] = '\0';
			printf("read contents is:%s\n",buf);
		}
	}

	if(FD_ISSET(fd_3, &readfds))
	{
	    len = read(fd_3, buf, BUF_LEN);
		if(-1 == len)
		{
		    printf("read contents from STDIN fail.\n");
		}
		if(len)
		{
		    buf[len] = '\0';
			printf("read contents is:%s\n",buf);
		}
	}
    }while(strncmp(buf,"quit",strlen("quit")));

	printf("Quit the app\n");
	close(fd_1);
	close(fd_2);
	close(fd_3);
    return 0;
exit_1:
	printf("Create file1 fail. %s\n",strerror(errno));
    return -1;
exit_2:
	close(fd_1);
	printf("Create file2 fail. %s\n", strerror(errno));
	return -1;
exit_3:
	close(fd_1);
	close(fd_2);
	printf("Create file 3 fail. %s\n", strerror(errno));
	return -1;
}
