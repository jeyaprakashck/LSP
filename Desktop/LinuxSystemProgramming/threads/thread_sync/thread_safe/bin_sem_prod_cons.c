#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
	
char buffer[5];

sem_t Prod;
sem_t Cons;

int main(){
	pthread_t ProdThreadHandle;
	pthread_t ConsThreadHandle;
	
	void *ProdThreadFun(void *arg);
	void *ConsThreadFun(void *arg);
	
	void *ProdThreadRet;
	void *ConsThreadRet;

	int ret;

	sem_init(&Prod, 0, 1);
	sem_init(&Cons, 0, 0);
		
	ret = pthread_create(&ProdThreadHandle, NULL, ProdThreadFun, NULL);
	if(ret<0){
		perror("Prod thread fail");
		exit(0);
	}

	ret = pthread_create(&ConsThreadHandle, NULL, ConsThreadFun, NULL);
	if(ret<0){
		perror("Cons thread fails");
		exit(0);
	}

	ret = pthread_join(ProdThreadHandle, &ProdThreadRet);
	if(ret<0){
		perror("Prod thread joinfails");
		exit(0);
	}

	ret = pthread_join(ConsThreadHandle, &ConsThreadRet);
	if(ret<0){
		perror("Cons thread join  fails");
		exit(0);
	}
	
	printf("Leaving from main thread\n");
}

void *ProdThreadFun(void *arg){
	int i;
	char ch = 'A';
	
	while(1){

		sem_wait(&Prod);

		for(i=0;i<5;i++){
			buffer[i] = ch;
			ch++;
		}
		//sleep(2);	
		ch = 'A';
		printf("Prod %s\n",buffer);
		
		sem_post(&Cons);
	}
	
	pthread_exit("Exiting from Prod thread");
}

void *ConsThreadFun(void *arg){
	int i;
	char data[5];
	while(1){
		sem_wait(&Cons);
		
		for(i=0;i<5;i++)
			data[i] = buffer[i];
		
		printf("Cons %s\n",data);
		sem_post(&Prod);

	}
}

