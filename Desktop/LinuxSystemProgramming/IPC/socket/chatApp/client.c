#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>	//This is for UNIX family
#include <netinet/in.h> //This is for IP family
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/*thread function definitions*/
void *threadReadFunc(void *args);
void *threadWriteFunc(void *args);

/* Socket parameters */
char msg[1024];
int clientSocketfd;
int clientLen;

/* Time generation parameters */
time_t now;
struct tm *localTime;


int main(){
	int connection;
	struct sockaddr_un clientAddr = {	//this is for IP family
		.sun_family	  = AF_UNIX,
		.sun_path	  = "abcSocket",
	};
	
	/* creating unnamed socket */
	clientSocketfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(clientSocketfd<0){
		perror("error during socket creation");
		return -1;
	}

	/* now connect our socket to the server's socket */
	connection = connect(clientSocketfd,
			     (struct sockAddr*)&clientAddr, 
			     sizeof(clientAddr));
	if(connection < 0){
		perror("Connection error : client ");
		return -1;
	}
	

	/*pthread used to create two different threads, one is for reading, one is for writing*/
	int threadCreation;
	pthread_t threadReadHandler;
	pthread_t threadWriteHandler;
	void *threadExit;
	
	threadCreation = pthread_create(&threadReadHandler, NULL, threadReadFunc, NULL);
	if(threadCreation < 0){
		perror("Read thread creation fails\n");
		return -1;
	}
	
	threadCreation = pthread_create(&threadWriteHandler, NULL, threadWriteFunc, NULL);
	if(threadCreation < 0){
		perror("Write thread creation fails\n");
		return -1;
	}

	threadCreation = pthread_join(threadReadHandler, &threadExit);
	if(threadCreation < 0){
		perror("Read thread creation fails\n");
		return -1;
	}
	printf("Return value from read thread : %s\n", (char*)threadExit);
	
	threadCreation = pthread_join(threadWriteHandler, &threadExit);
	if(threadCreation < 0){
		perror("Write thread creation fails\n");
		return -1;
	}
	printf("Return value from Write thread : %s\n", (char*)threadExit);
}

void *threadReadFunc(void *args){
	printf("Please enter the message to sent\n\n");
	while(1){
		time(&now);
		localTime = localtime(&now);
		fgets(msg, 1024, stdin);
		write(clientSocketfd, msg, sizeof(msg));
		printf("\033[1A");		//Cursor movement : one line above
                //printing the timestamp
                printf("Client[%02d:%02d:%02d] : ", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);        
		printf("%s\n", msg);
	}
	pthread_exit("Exiting from read fun\n");
}

void *threadWriteFunc(void *args){
	while(1){
		time(&now);
		localTime = localtime(&now);
		read(clientSocketfd, msg, 1024);
                //printing the timestamp
                printf("Server[%02d:%02d:%02d] : ", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);        
		printf("%s\n", msg);
	}
	pthread_exit("Exiting from write fun\n");
}
