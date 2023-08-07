#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
	
char buffer[26];

sem_t empty;
sem_t full;

int main(){
	pthread_t ProdThreadHandle;
	pthread_t ConsThreadHandle;
	
	void *ProdThreadFun(void *arg);
	void *ConsThreadFun(void *arg);
	
	void *ProdThreadRet;
	void *ConsThreadRet;

	int ret;

	sem_init(&empty, 0, 26);
	sem_init(&full, 0, 0);
		
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
	int in=0;
	int value;
	char ch = 'A';
	
	while(1){

		sem_wait(&empty);

		buffer[in] = ch;
		ch++;
		in=(in + 1)%26;
		sem_getvalue(&empty, &value);
		printf("Empty semphore value : %d\n", value);
		if(in ==0){
			printf("Prod %s\n",buffer);
			ch = 'A';
		}
	
		sem_post(&full);
	}
	
	pthread_exit("Exiting from Prod thread");
}

void *ConsThreadFun(void *arg){
	int out;
	int value;
	char data[26];
	while(1){
		sem_wait(&full);
	
		sem_getvalue(&full, &value);
		printf("Full semphore value : %d\n", value);
		
		data[out] = buffer[out];
		out = (out + 1)%26;
		if(out == 0)
			printf("Cons %s\n",data);
		
		sem_post(&empty);
	}
}

