#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void *threadProdFun(void *args);
void *threadConsFun(void *args);

int counter=0;
char buffer[5];

int main(){
	pthread_t threadProdHandle;
	pthread_t threadConsHandle;
	void *threadexit;
	int ret;
	
	ret = pthread_create(&threadProdHandle, NULL, threadProdFun, NULL);

	if(ret<0){
		perror("Thread Prod fails");
		exit(0);
	}

	ret = pthread_create(&threadConsHandle, NULL, threadConsFun, NULL);
	if(ret<0){
		perror("Thread Cons fails");
		exit(0);
	}

	ret = pthread_join(threadProdHandle, &threadexit);	
	if(ret<0){
		perror("Thread Join Prod fails");
		exit(0);
	}
	printf("Return value from Prod thread : %s\n",(char *)threadexit);
	
	ret = pthread_join(threadConsHandle, &threadexit);
	if(ret<0){
		perror("Thread Join Cons failes");
		exit(0);
	}
	printf("Return value from Cons thred : %s\n", (char *)threadexit);
}

void *threadProdFun(void *args){
	int i=50;
	int in=0;
	char ch ='A';
	printf("Entering to prod thread\n");
	//sleep(5);
	while(i--){
		printf("In Prod thread  - %d %c\n",counter,ch);
		while(counter==5);
		buffer[counter] = ch;
		in = (in+1)%60;
		ch++;
		if(counter == 0){
			ch = 'A';
			printf("producer : %s\n",buffer);
		}
		counter++;
		i--;
	}
	pthread_exit("exiting from prod thread\n");
}

void *threadConsFun(void *args){
	int i=50;
	int out=0;
	char readBuffer[5];
	printf("Entering to cons thread \n");
	while(i--){
		printf("In Cons thread   - %d %c \n",counter,buffer[out]);
		while(counter==0);
		readBuffer[counter] = buffer[counter];
		out = (out+1)%60;
		if(counter == 0)
			printf("consumer : %s\n", buffer);
		counter--;		
		i--;
	}
	//sleep(3);
	pthread_exit("exiting from cons thread\n");
}

	

