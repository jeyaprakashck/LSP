#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int shmid;
	char *msg;

	shmid = shmget(10, 1024,0);
	if(shmid<0){
		perror("shmget");
		exit(0);
	}
	
	msg = shmat(shmid, 0, 0);
	printf("Reading the data from the shared memory : %s\n",msg);
	getchar();
	shmdt(msg);
	return 0;
}
