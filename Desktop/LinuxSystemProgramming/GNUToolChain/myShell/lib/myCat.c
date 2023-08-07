#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

void myCat(int argc, char *argv[]){	
	
	if(argc > 4){
		//printf("Please enter only one file\n");
		//exit(0);
	}

	printf("Hello");
	int file;
	int ret;
	char buff[4096];
	printf("%s : \n", argv[2]);
	file = open(argv[2], O_RDONLY);
	if(file<0){
		printf("Error during file open dddddddddd\n");
		exit(0);
	}
	
	while(ret = read(file, buff, sizeof(buff)))
		write(1, buff, ret);
}
	
	
