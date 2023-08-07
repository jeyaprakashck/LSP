#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	
	int i;
	int inFile;
	int outFile;
	int ret;
	char buff;	

	if(argc != 3){
		printf("Source and destination file name should be provided\n");
		exit(0);
	}
/******************************using System Call**************************************
	inFile = open(argv[1], O_RDONLY);
	if(inFile < 0){
		printf("Soure file : Errorno : %d\n", errno);
		exit(0);
	}

	outFile = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if(outFile<0){
		printf("Destination File : Errorno : %d\n", errno);
		exit(0);
	}
	
	while((read(inFile, &buff, 1)>0)){
		write(outFile, &buff, 1);
	}
****************************using Standard Library*************************************/

	FILE *inFileStd;
	FILE *outFileStd;
	char c;

	inFileStd = fopen(argv[1], "r");
	outFileStd = fopen(argv[2], "w");
	
	while((c = fgetc(inFileStd)) != EOF)
		fputc(c, outFileStd);
	
	exit(0);
}



