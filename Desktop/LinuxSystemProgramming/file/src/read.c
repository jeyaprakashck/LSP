#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int main(){
	char buff[10]={0};
	int ret;
	ret = read(0,buff,6);
	printf("ret:%d\n",ret);
	if(ret<0){
		printf("error no:%d\n",errno);
		perror("readFAIL");
	}
	printf("%s",buff);
	return 0;
}
