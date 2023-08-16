#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int serverSocketfd;
	int clientSocketfd;
	int clientLen;
	struct sockaddr_un serverAddr = {	//this is for UNIX family
		.sun_family = AF_UNIX,
		.sun_path   = "abcSocket",
	};
	struct sockaddr_un clientAddr;
	
	
	/* Removing old socket and creating unnamed socket */
	unlink("abcSocket");
	serverSocketfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(serverSocketfd<0){
		perror("error during socket creation");
		return -1;
	}

	/*  Name the socket and Socket binding */
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "abcSocket");
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
