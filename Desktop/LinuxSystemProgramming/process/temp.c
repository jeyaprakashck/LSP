#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>


int main(){

         int ret, status;
         pid_t pid;
	 char buff[20];
	 printf("$");
	 pid = fork();
	

	 scanf("%s",buff);

         if(pid==0){
    	        // printf("children\n");
                 ret = execl(buff, "ls", NULL);
      	         if(ret<0){
                         perror("execve fails");
                         exit(1);
                 }
 
         }
         else{
                // printf("parents\n");
                 wait(&status);
         }
         return 0;
}
