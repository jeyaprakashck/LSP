#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int shmid;
	char *msg;

	shmid = shmget(555, 1024, 0);
	if(shmid<0){
		perror("shmget");
		exit(0);
	}
	
//	printf(" %d", shmid);
	shmid = shmctl(shmid, IPC_RMID, 0);
	if(shmid<0){
		perror("shmCtl");
		exit(0);
	}	

	return 0;
}
