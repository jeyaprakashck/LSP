#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

sem_t *semProd;
sem_t *semCons;
pid_t pid;
int status;
char *msg;
int i;
int j;
int shmid;

void terminate(int sig){
	printf(" Ctrl C received\n");
	sem_unlink("semProd1");
	sem_unlink("semCons1");
	signal(SIGINT, SIG_DFL);
}

int main(){
	signal(SIGINT, terminate);
	//sem_open(name, oflag, permission, initalValue)
	semProd = sem_open("semProd1", O_CREAT, 0666, 1); //Sem Prod is unlocked 
	if(semProd == NULL){
		perror("Semaphore1");
		exit(0);
	}
	
	semCons = sem_open("semCons1", O_CREAT, 0666, 0); //Sem cons is locked
	if(semProd == NULL){
		perror("Semaphore1");
		exit(0);
	}

	pid = fork();
	if(pid == 0){
		sem_wait(semCons);
		shmid = shmget(555, 5, 0);
		msg = shmat(shmid, 0, 0);
		for(i = 0; i<5; i++)
			printf("Read value %c  ",*(msg+i));
		printf("\n");
		shmdt(msg);
		sem_post(semProd);
		exit(0);
	}
	else{
		sem_wait(semProd);
		shmid = shmget(555, 5, 0666 | IPC_CREAT);
		msg = shmat(shmid, 0, 0);
		printf("Writing 'A', 'B', ...'D'to shared memory\n");
		for(i=0;i<5;i++)
			*msg++ = 'A'+i;
		printf("data is written successfully\n");
		shmdt(msg);
		sem_post(semCons);
		wait(&status);
	}	
}
