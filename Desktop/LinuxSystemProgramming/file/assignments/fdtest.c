#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>



int main(int argc, char *argv[]){
	int i=5;	
	int file1;
	int file2;
	int ret;
	char buff[4096];
	pid_t pid;
	
	file1 = open("inFile", O_RDWR);
	file2 = open("inFile", O_RDWR);
	
	if((file1<0)&&(file2<0)){
		printf("Error during file open\n");
		exit(0);
	}
	
	pid = fork();

	if(pid==0){	
		while(i--){
		ret = read(file1, buff, 1);
		write(file2, "hello", sizeof("hello"));
		write(1, buff, ret);
	}
	}
	else{	
		while(i--){
		ret = read(file1, buff, 1);
		lseek(file2, 0, SEEK_END);
		write(file2, "world", sizeof("world"));
		write(1, buff, ret);
	}
	}
}
	
	
