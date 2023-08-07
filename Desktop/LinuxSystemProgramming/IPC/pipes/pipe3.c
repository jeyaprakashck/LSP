#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int status;
	int bytesCount;
	int pipefd[2];
	pid_t pid;
	char pipeReadfd[100];
		
	char inData[] = "123";

	

	if(pipe(pipefd) == 0)
		getchar();

	else
		exit(EXIT_FAILURE);
	
	
	sprintf(pipeReadfd, "%d", pipefd[0]);	



	pid = fork();
	
	

	//childern process
	if(pid ==0){
		
		(void)execl("pipe4", "pipe4", pipeReadfd, (char *)0);
	
		exit("done:");
	}
	
	//parent proces
	else{
		write(pipefd[1], inData, sizeof(inData));
		printf(" Wrote \n");
		wait(&status);	
	}
}
	
		
