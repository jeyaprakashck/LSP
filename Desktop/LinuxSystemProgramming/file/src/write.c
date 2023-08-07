#include<stdio.h>
#include<errno.h>
#include<unistd.h>
int main(){
	int ret;
	ret = write(1,"Hello\n",9);
	printf("ret : %d\n",ret);
	if(ret<0){
		printf("error no : %d\n",errno);
	}
	return 0;
}
