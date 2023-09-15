#include<unistd.h>
#include<stdio.h>
#include<errno.h>
//#include<sys/types.h>
//#include<sys/stat.h>
#include<fcntl.h>

int main(){
	char buff[50]={0};
	int fd, ret;
	fd = open("abc.txt", O_RDONLY | O_CREAT, 0666);
	printf("fd:%d\n",fd);
	

	
	ret = read(fd, buff,10);
	printf("ret:%d\n",ret);
	

	printf("after read buff:%s\n",buff);
	close(fd);
	return 0;
}
