#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
 
int main(){
        int fd,nread,nwrite;
        char buff[100];
        fd = open("abc.txt",O_RDWR);

        nwrite = lseek(fd,10,SEEK_CUR);
        printf("Lseek return value : %d\n",nwrite);
        nwrite = write(fd,"Jeya",4);
 	printf("write return value: %d\n",nwrite);

	lseek(fd,5,SEEK_SET);	

	nwrite = write(fd,"Prakash",7);
 	printf("write return value : %d\n",nwrite);
	close(fd);
}
