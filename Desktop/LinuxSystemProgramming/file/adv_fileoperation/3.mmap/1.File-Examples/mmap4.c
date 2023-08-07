#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	char *addr;
	int fd,i;
	struct stat sb;







	fd = open(argv[1],O_RDWR);
	
	addr =(char *)mmap(NULL, 6, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	for(i=0;i<4;i++,addr++){
		*(addr+i)=(char)(i+65);
	}
	if(fstat(fd,&sb)==-1)
		perror("fstat");
	
	printf("PAGE SIZE : %lx\n",sysconf(_SC_PAGE_SIZE));

	printf("file size : %lx\n",sb.st_size);

}
