#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


void myEcho(int argc, char *argv[]){
	int i;
	
	if(argc<3){
		printf("Usage <echo><value1><value2>....\n");
		exit(0);
	}
	
	for(int i = 2; i<argc; i++){
		write(1, argv[i], strlen(argv[i]));
		write(1, "\n",1);
	}

}		
