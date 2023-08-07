#include<stdio.h>
#include<unistd.h>


int main(){
	pid_t pid;
	printf("PID Before fork : %d\n",getpid());
	
	pid = fork();
	printf("PID After fork1 creation : %d \n",getpid());
	
	if(pid)
		printf("Parent process of fork1 \n");
	else
		printf("Child process of fork1 \n");

	printf("Program ends here");
} 	
