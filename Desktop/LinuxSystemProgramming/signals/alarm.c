#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

static int alarm_fired = 0;

void ding(int sig){
	alarm_fired = 1;
}

int main(){
	pid_t pid;
	printf("Alarm function started\n");
	
	printf(" PID before fork %d\n", getpid());
	
	pid = fork();
	
	printf(" PID after fork %d\n", getpid());
	
	switch(pid){
		case -1 :
			perror("Fork failed");
			exit(0);
		case 0 :
			sleep(5);
			kill(getppid(), SIGINT);
			exit(0);
	}
	
	printf("Waiting for alarm to go off\n");
	(void) signal(SIGINT, ding);
	
	pause();
	if(alarm_fired)
		printf("Ding\n");
	
	printf("Done \n");
	exit(0);
}
