#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    
	int count = 0;
	printf("hello, welcome to enter the program. pid is:%d, parent's id:%d \n",getpid(), getppid());
	while(1)
	{
	    printf("Count is:%d\n",count);
		count++;
		sleep(count);
		if(count >5)
		{
		    printf("End of the program.\n");
			break;
		}

	}
	return 0;
}
