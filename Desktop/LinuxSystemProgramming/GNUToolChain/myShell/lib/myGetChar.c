#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>


void myGetChar(int argc, char *argv[]){
	char buff;
	char temp[4096];
	int ret;
	int i = 0;
	
	if(argc>2){
		printf("No argument needed...Exiting\n");
		exit(0);
	}

	printf("Please enter the char \n");

	while(1){
		ret = read(0, temp, sizeof(temp));
		while(i<4096){
			if(temp[i++]=='\n')
				break;
		}
		if(ret || temp[i-1]=='\n')
			break;	
	}
	printf("The entered char is : %c\n", temp[0]);
}
