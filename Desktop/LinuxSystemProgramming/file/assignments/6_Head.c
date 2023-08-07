#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void head(int argc, char *argv[]){
	int file;
	int i;
	char buff;
	if(argc != 4){
		printf("Please enter the correct sequence of head command");
		exit(0);
	}	

	file = open(argv[3], O_RDONLY);
	if(file<0){
		printf("No file exist\n");
		exit(0);
	}

	

/********If the option is -n******************/
	if(argv[1][1]=='n'){
		i = (argv[2][0])-'0';
		for(;i>=0;i--){
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
	if(argv[1][1] == 'c'){
		i =atoi(argv[2]);
		for(;i>=0;i--){
			read(file, &buff, 1);
			write(1, &buff,1);
		}
	}
}


int main(int argc, char *argv[]){
	head(argc, argv);
}
