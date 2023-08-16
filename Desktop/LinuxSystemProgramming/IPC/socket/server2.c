#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>	//This is for UNIX family
#include <netinet/in.h> //This is for IP family
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int serverSocketfd;
	int clientSocketfd;
	int clientLen;
	struct sockaddr_in serverAddr = {	//this is for IP family
		.sin_family	  = AF_INET,
		.sin_addr.s_addr  = inet_addr("127.0.0.1"),
		.sin_port	  = 9734,
	};
	struct sockaddr_un clientAddr;
	
	
	/* creating unnamed socket */
	serverSocketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocketfd<0){
		perror("error during socket creation");
		return -1;
	}

	/*  Name the socket and Socket binding */
	bind(serverSocketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	/* create a connection queue and wait for client */
	listen(serverSocketfd, 5);
	while(1){
		char ch;
		printf("Server waiting \n");
		clientLen = sizeof(clientAddr);
		/*accept the connection */
		clientSocketfd = accept( serverSocketfd,		
					 (struct sockaddr*)&clientAddr,
					 &clientLen);
	
		/* we can now read/write to client on client socketfd */
		read(clientSocketfd, &ch,1);
		ch++;
		write(clientSocketfd, &ch, 1);
		close(clientSocketfd);
	}
}
