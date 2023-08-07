#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

char *const ls_argv[] = {"ls", "-l", 0};

int main(){
	int ret;
	printf("starting line\n");
	getchar();
	
	ret = execve("/bin/ls", ls_argv, NULL);
	if(ret<0){
		perror("execve fails");
		exit(1);
	}
	
	printf("Last line\n");
	return 0;
}
