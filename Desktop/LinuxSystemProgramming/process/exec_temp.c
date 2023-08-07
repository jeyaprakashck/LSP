#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int main(){
	//char *const argv[] = {"system",0};
	printf("In main\n");
	//execl("/bin/ls", "ls", "-l", NULL);
	execl("/home/km/Desktop/process/system", "system", NULL);
	printf("Ends\n");
}
