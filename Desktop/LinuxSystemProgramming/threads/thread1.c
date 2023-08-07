#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

char msg[]="Hello";
void *thread_1(void *arg);

int main(){
	int ret;
	pthread_t thread_1_Handle;
	void *retval;

	ret = pthread_create(&thread_1_Handle, NULL, thread_1, (void*) msg);
	if(ret<0){
		perror("pthread create fail:");
		exit(0);
	}
	
	ret = pthread_join(thread_1_Handle, &retval);
	if(ret<0){
		perror("pthread join fails");
		exit(0);
	}
	
	printf("return value from new thread : %s\n", (char *)retval);


	
	
	return 0;
}

void *thread_1(void *arg){
	printf("msg : %s\n", (char *)arg);
	


	sleep(5);
	pthread_exit("Exiting from thread_1");
}
