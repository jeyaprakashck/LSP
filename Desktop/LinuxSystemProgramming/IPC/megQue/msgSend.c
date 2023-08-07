#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct msg{
	long int type;
	char msg[20];
};

int main(int argc, char *argv[]){
	if(argc<2){
		printf("usage : <msgQue> <msg:type> <msg:Data>\n");
		exit(0);
	}

	struct msg msg;
	int msgKey;
	msgKey = msgget(555, 0666 | IPC_CREAT);
	if(msgKey<0){
		perror("msgget error");
		exit(0);
	}

	msg.type = atoi(argv[1]);
	strcpy(msg.msg, argv[2]);
	
	msgsnd(msgKey, &msg, sizeof(struct msg), 0);
		
	msgsnd(0, &msg, sizeof(struct msg), 0);


	
	
	
}


