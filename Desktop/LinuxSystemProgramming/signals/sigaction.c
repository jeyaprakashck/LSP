#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static int signalVal = 0;

void signalFun(int sig){
	if(sig == 2){
		signalVal = 1;
		printf("inside the signal function \n");
	}
}

int main(){
	printf("The PID is %d\n", getpid());
	
	struct sigaction act;
	
	act.sa_handler = &signalFun;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	
	if(sigaction(SIGINT, &act, NULL) == -1){
		perror("sigaction fails");
		exit(0);
	}

	printf("kill this process manually\n");
	
	while(1){
		if(signalVal){
			signalVal = 0;
			printf("SIGINT signal occurred \n");
		}
	}
}
