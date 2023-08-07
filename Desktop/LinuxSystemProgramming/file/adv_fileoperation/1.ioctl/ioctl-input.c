#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/input.h>

int main(int argc, char *argv[]){
	
	int fd;
	int ret;
	char name[256] = "Unknown";

	fd = open(argv[1], O_RDONLY);
	if(fd<0){
		printf("Open fails\n");
		exit(0);
	}
	
	ret = ioctl(fd, EVIOCGNAME(sizeof(name)), name);
	if(ret<0){
		printf("ioctl fails");
		exit(0);
	}
	
	printf("Input device name is : %s", name);
}
