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
	
		
	char inData[] = "123";
	char outData[BUFSIZ+1];	
	char outData1[BUFSIZ+1];
	memset(outData, '\n', sizeof(outData));
	getchar();

	if(pipe(pipefd) == 0)
		getchar();

	else
		exit(EXIT_FAILURE);
	
	
	pid = fork();
	

	//childern process
	if(pid ==0){
		
		write(pipefd[1], inData, sizeof(inData));
		//printf(" Wrote %d bytes\n ", bytesCount);
		exit("done:");
	}
	
	//parent proces
	else{
		read(pipefd[0], outData, sizeof(outData));
		printf(" Data : %s\n", outData);
		wait(&status);	
	}
}
	
		
