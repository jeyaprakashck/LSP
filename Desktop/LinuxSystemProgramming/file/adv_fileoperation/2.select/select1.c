#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/input.h>

int main(){
	int fd1;
	int fd2;
	fd_set readFileset;
	int ret;
	struct input_event ev;
	
	fd1 = open("/dev/input/event2", O_RDONLY);
	if(fd1<0){
		printf("File open fails");
		exit(0);
	}
	
	fd2 = open("/dev/input/event4", O_RDONLY);
	if(fd2<0){
		printf("File open fails");
		exit(0);
	}
	
	FD_ZERO(&readFileset);
	
	printf("Max no of fd's : %d\n",FD_SETSIZE);

	while(1){
		FD_SET(fd1, &readFileset);
		FD_SET(fd2, &readFileset);
		
		ret = select(FD_SETSIZE, &readFileset, NULL, NULL, 0);
		if(ret<0){
			printf("Error : select call");
			exit(0);
		}
		
		if(FD_ISSET(fd1, &readFileset)){
			printf("data is available for keyboard event\n");
			ret = read(fd1, &ev, sizeof(struct input_event));
			if(ret<0){
				printf("Error in reading keyboard event");
				exit(0);

			}
			printf("ret:%d ev.type:%d ev.code:%d ev.value:%d\n",ret,ev.type,ev.code,ev.value);
		}
		
		if(FD_ISSET(fd2, &readFileset)){
			printf("data is availale for mouse event \n");
			ret = read(fd2, &ev, sizeof(struct input_event));
			if(ret<0){
				printf("Error in reading mouse event");
				exit(0);
			}
			printf("ret:%d ev.type:%d ev.code:%d ev.value:%d\n",ret,ev.type,ev.code,ev.value);
			
		}
	}
}
			
