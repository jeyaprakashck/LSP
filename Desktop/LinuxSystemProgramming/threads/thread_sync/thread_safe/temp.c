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
	printf("odd thread : %s\n", (char*)oddThreadRet);
	
	ret = pthread_join(evenThreadHandle, &evenThreadRet);
	if(ret<0){
		perror("even thread join fails");
		exit(0);
	}
	printf("even thread : %s\n", (char*)evenThreadRet);

	printf("Exiting from main");
}


void *oddThreadFun(void *arg){
	int i=100;
	while(i--){
		sem_wait(&oddSem);
		printf("odd : %d\n", value++);
		usleep(50000);
		sem_post(&evenSem);
	}
	pthread_exit("Odd thread exit\n");
}

void *evenThreadFun(void *arg){
	int i=100;
	while(i--){
		sem_wait(&evenSem);
		printf("\t\t even : %d\n", value++);
		usleep(50000);
		sem_post(&oddSem);
	}
	pthread_exit("Even thread exit\n");
}

	
