#include<stdio.h>
#include<stdlib.h>

int main(){
	int x = 1;
	int y;
	int *ptr = NULL;
	//y = x/0; //SIGFPE --> Floating point fault

	x = *ptr; // Dereferencing NULL pointer --> SIGSEGV - Segmenation Fault
	
	return 0;
}
