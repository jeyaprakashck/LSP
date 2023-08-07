#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>


int main(int argc, char *argv[]) {
	
	int ret, status;
	char buff[20];
	while(1){
		//printf("$");	
		pid_t pid;
		pid = fork();
	
		if(pid ==0){
	
			printf("$");
			//scanf("%[^\n]", buff);
			gets(buff);	
			printf("\n");
		
			ret = execl("/bin/sh", "sh", "-c", buff, NULL); 
			if(ret<0){
				perror("execve fails");
				exit(1);
			}
		}

	
		else{
			//printf("parents\n");
			wait(&status);
		}

	}
	return 0;
}
