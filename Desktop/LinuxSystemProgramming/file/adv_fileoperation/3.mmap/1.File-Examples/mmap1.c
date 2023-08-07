#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>




int main(){
	int fd, i;
	unsigned char * filedata=NULL, *temp;
	fd = open("abcd.txt",O_RDWR);
	getchar();
	filedata = (unsigned char *)mmap(NULL,6,PROT_READ|PROT_WRITE, MAP_SHARED,fd,1);
	if(filedata==NULL){
		perror("Mapping failed");
		return -1;
	}
	getchar();
	
	temp = filedata;
	
	for(i=0;i<5;i++,filedata++){
		*filedata = (char)(i+65);
		printf("\n %c \n",(char)(i+65));
	}

	i=munmap(temp,6);
	getchar();
	if(i!=0){
		printf("failed to unmap\n");
	}
}
