#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


sem_t oddSem;
sem_t evenSem;

int value=1;

void *oddThreadFun(void *arg);
void *evenThreadFun(void *arg);

int main(){
	pthread_t oddThreadHandle;
	pthread_t evenThreadHandle;
	
	void *oddThreadRet;
	void *evenThreadRet;

	sem_init(&oddSem, 0, 1);
	sem_init(&evenSem, 0, 0);

	int ret;

	ret = pthread_create(&oddThreadHandle, NULL, oddThreadFun, NULL);
	if(ret<0){
		perror("odd thread create fails");
		exit(0);
	}

	ret = pthread_create(&evenThreadHandle, NULL, evenThreadFun, NULL);
	if(ret<0){
		perror("even thread create fails");
		exit(0);
	}

	ret = pthread_join(oddThreadHandle, &oddThreadRet);
	if(ret<0){
		perror("odd thread join fails");
		exit(0);
	}
	
	ret = pthread_join(evenThreadHandle, &evenThreadRet);
	if(ret<0){
		perror("even thread join fails");
		exit(0);
	}
	
	printf("Exiting from main");
}


void *oddThreadFun(void *arg){
	while(1){
		sem_wait(&oddSem);
		printf("odd : %d\n", value++);
		sem_post(&evenSem);
	}
}

void *evenThreadFun(void *arg){
	while(1){
		sem_wait(&evenSem);
		printf("\t\t even : %d\n", value++);
		sem_post(&oddSem);
	}
}	
