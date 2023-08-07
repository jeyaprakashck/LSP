#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int shmid;
	char *msg;

	shmid = shmget(10, 1024, 0666 | IPC_CREAT);
	if(shmid<0){
		perror("shmget");
		exit(0);
	}
	
	msg = shmat(shmid, 0, 0);
	printf("Enter the data you want to write into shared mem\n");
	fgets(msg, 1024, stdin);
	
	getchar();
	shmdt(msg);
	return 0;
}
