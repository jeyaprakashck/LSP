#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int clientSocketfd;
	int connection;
	struct sockaddr_un clientAddr = {
		.sun_family = AF_UNIX,
		.sun_path   = "abcSocket",
	};
	char ch = 'A';

	/* Removing old socket and creating unnamed socket */
	clientSocketfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(clientSocketfd<0){
		perror("error during socket creation");
		return -1;
	}

	/* now connect our socket to the server's socket */
	connection = connect(clientSocketfd,
			     (struct sockaddr*)&clientAddr, 
			     sizeof(clientAddr));
	if(connection<0){
		perror("Connection error : client ");
		return -1;
	}
	/* we can read / write via client socketfd */	
	write(clientSocketfd, &ch, 1);
	read(clientSocketfd, &ch, 1);
	printf("Char from server is %c\n", ch);
	close(clientSocketfd);
	
}
