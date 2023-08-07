#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "myShellHeader.h"

int main(int argc, char *argv[]){
	

	if(argc<2){
		printf("Please enter command and followed by arguments\n");
		exit(0);
	}
	
	if(!strcmp(argv[1], "cat")){
		myCat(argc, argv);
	}else if(!strcmp(argv[1], "echo")){
		myEcho(argc, argv);
	}else if(!strcmp(argv[1], "getchar")){
		myGetChar(argc, argv);
	}else if(!(strcmp(argv[1], "cp"))){
		myCopyByte(argc, argv);
	}else if(!(strcmp(argv[1], "head"))){
		myHead(argc, argv);
	}else if(!(strcmp(argv[1], "tail"))){
		myTail(argc, argv);
	}

	printf("\nFinished");

}
