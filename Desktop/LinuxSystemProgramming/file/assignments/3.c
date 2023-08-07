#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

void cat(char *argv[]);

int main(int argc, char *argv[]){
	if(argc > 2){
		printf("Please enter only one file\n");
		exit(0);
	}
	
	cat(argv);
}

void cat(char *argv[]){	
	int file;
	int ret;
	char buff[4096];

	file = open(argv[1], O_RDONLY);
	if(file<0){
		printf("Error during file open\n");
		exit(0);
	}
	
	while(ret = read(file, buff, sizeof(buff)))
		write(1, buff, ret);
}
	
	
