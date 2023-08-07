#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

void head(int argc, char *argv[]){
	int file;
	int i;
	char buff;
	int length;
	int current;
	int noLines=0;
	struct stat sb;
	long long fileSize;
	int positionFromLast = -1;

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
		i =atoi(argv[2]);
	//Finding the \n from last byte of the file
		if(stat(argv[3], &sb)==-1){
			printf("Error in Stat\n");
			exit(0);
		}
		fileSize =(long long) sb.st_size;

		lseek(file, -1, SEEK_END);

		while(read(file, &buff, 1)>0){
			if(buff == '\n'){
				printf("noLines : %d\n",noLines);
				noLines++;
				if(noLines == i+1)					
					break;
			}
			positionFromLast--;
			lseek(file, positionFromLast, SEEK_END);
		}
	

		while(read(file,&buff, 1)>0){
			write(1, &buff, 1); 	
				//getchar();
		}
	}


/*******If the option is -c********************/
	if(argv[1][1] == 'c'){
		i =atoi(argv[2]);
		length = lseek(file, 0, SEEK_END);
		current = length - i;
		lseek(file, current, SEEK_SET);
 		while(read(file, &buff, 1)>0){
			write(1, &buff,1);
		}
	}
}


int main(int argc, char *argv[]){
	head(argc, argv);
}
