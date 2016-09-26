#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define BIN "./hello"

int main(){
   pid_t pid = 0;
   int ret;
   
   pid = getpid();
   printf("Current process id is:%d\n",pid);
   
   ret = fork();
   if(!ret)
   {
      pid = getpid();
	  printf("In child process, pid:%d parent id:%d\n", pid, getppid());
	  if(execv(BIN, NULL) == -1)
	  {
	     printf("execv fail.\n");
	  }
   }
   else if(ret != -1)
   {
       pid = getpid();
	   printf("In parent process, child pid:%d, parent id:%d\n", ret, pid);
       sleep(2);
//	   kill(ret,SIGTERM);
//	   printf("Has killed the child process.\n");
//	   wait(pid, NULL);
	   exit(0);
	   printf("parent process leave.\n");
   }
   else
   {
       printf("fork fail.\n");
   }
   


   return 0;
}
