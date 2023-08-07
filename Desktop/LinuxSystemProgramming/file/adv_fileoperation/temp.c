#include<stdio.h>
#include<stdlib.h>
#include<linux/fb.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
#include<unistd.h>

int main(){
	int fd;
	int i;
	u_int32_t *fbPtr;
	int fbSize = 800 * 600 * 32/8;
	
	fd = open("/dev/fb0", O_RDWR);
	
	fbPtr =	 mmap(0, fbSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	//memset(fbPtr, 0xFF, fbSize);
	
	//printf("%d", fbSize);
	
	for(i =0; i<fbSize/4;){
		*((u_int32_t*) fbPtr + i) = (u_int32_t)0x00FF0000;
		i++;
		//*((u_int32_t*) fbPtr +i) = (u_int32_t)0x00000000;
		//i++;
	}
	sleep(1);
	for(i = 0; i<fbSize;){
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0xff;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
	}
	sleep(1);
	for(i = 0; i<fbSize;){
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0xff;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
	}
	
	sleep(1);
	for(i = 0; i<fbSize;){
		*(fbPtr + i) = 0xff;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
	}
	sleep(1);
	for(i = 0; i<fbSize;){
		*(fbPtr + i) = 0xff;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
		*(fbPtr + i) = 0xff;
		i++;
		*(fbPtr + i) = 0x00;
		i++;
	}
	
}
