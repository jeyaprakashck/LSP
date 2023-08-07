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

int main(){

	struct msg msg;
	int msgKey;
	msgKey = msgget(555, 0666);
	if(msgKey<0){
		perror("msgget error");
		exit(0);
	}


	msgrcv(msgKey, &msg, sizeof(struct msg), 0, 3);
		
	printf("Msg type : %d\n Msg : %s\n", msg.type, msg.msg);


	
	
	
}


