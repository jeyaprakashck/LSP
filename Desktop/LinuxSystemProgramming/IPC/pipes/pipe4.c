#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int bytesCount;
	int pipeReadfd;
	char outData[BUFSIZ+1];

	//sscanf(argv[1], "%d", &pipeReadfd);
	
	memset(outData, '\n', sizeof(outData));
	getchar();
		
	bytesCount = read(3, outData, sizeof(outData));
	printf(" Read %d bytes, Data : %s\n", bytesCount, outData);
	exit(EXIT_SUCCESS);
	
	
}
