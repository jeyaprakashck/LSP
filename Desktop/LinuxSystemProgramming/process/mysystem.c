#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>


int main(int argc, char *argv[]) {
	
	int ret, status;
	pid_t pid;
	pid = fork();


	if(pid==0){

		ret = execl("/bin/sh", "sh", "-c", argv[1], NULL);
		if(ret<0){
			perror("execl fails");
			exit(1);
		}

	}
	else{
		
		wait(&status);
	}
	return 0;
}
