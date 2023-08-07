#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int bytesCount;
	int pipefd[2];
	char inData[] = "123";
	char outData[BUFSIZ+1];
	
	memset(outData, '\n', sizeof(outData));
	getchar();

	if(pipe(pipefd) == 0){
		getchar();
		bytesCount = write(pipefd[1], inData, sizeof(inData));
		printf(" Wrote %d bytes\n ", bytesCount);
		
		bytesCount = read(pipefd[0], outData, sizeof(outData));
		printf(" Read %d bytes, Data : %s\n", bytesCount, outData);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
