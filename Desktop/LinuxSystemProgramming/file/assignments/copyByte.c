#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

void echo(int argc, char *argv[]);

int main(int argc, char *argv[]){
	echo(argc, argv);
	return 0;
}

void echo(int argc, char *argv[]){
	int i;

	for(int i = 1; i<argc; i++){
		write(1, argv[i], strlen(argv[i]));
		write(1, "\n",1);
	}

}		
