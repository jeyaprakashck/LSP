#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void myHead(int argc, char *argv[]){
	int file;
	int i;
	char buff;
	if(argc != 5){
		printf("Please enter the correct sequence of head command");
		exit(0);
	}	

	file = open(argv[4], O_RDONLY);
	if(file<0){
		printf("No file exist\n");
		exit(0);
	}

	

/********If the option is -n******************/
	if(argv[2][1]=='n'){
		i = atoi(argv[3]);
		for(;i>0;i--){
			while(1){
				read(file, &buff, 1);
				if(buff == '\n')
					break;
				write(1, &buff, 1); 	
				//getchar();
			}
			write(1, "\n", 1);
		}
	}


/*******If the option is -c********************/
	if(argv[2][1] == 'c'){
		i =atoi(argv[3]);
		for(;i>=0;i--){
			read(file, &buff, 1);
			write(1, &buff,1);
		}
	}
}


