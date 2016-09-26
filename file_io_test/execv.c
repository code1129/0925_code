#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#define BIN "./hello"

int main(){
   pid_t pid = 0;
   int ret;
   pid = getpid();
   printf("Current process id is:%d\n",pid);

   ret =  execv(BIN, NULL);
   if(ret == -1)
   {
       printf("execv fail, %s\n",strerror(errno));
   }
   
   printf("After execv pid:%d\n", getpid());
   return 0;
}
