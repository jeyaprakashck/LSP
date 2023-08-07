#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

char getChar();

int main(){
	char buff;
	printf("Please enter the char \n");
	buff = getChar();
	printf("The entered char is : %c\n",buff);
}

char getChar(){
	char temp[4096];
	int ret;
	int i = 0;

	while(1){
		ret = read(0, temp, sizeof(temp));
		while(i<4096){
			if(temp[i++]=='\n')
				break;
		}
		if(ret || temp[i-1]=='\n')
			break;	
	}
	return temp[0];
}
