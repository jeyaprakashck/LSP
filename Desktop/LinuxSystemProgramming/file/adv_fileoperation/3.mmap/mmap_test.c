
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(){

	int fd;
	int ret;
	int i;
	char *ptr = NULL;	
	pid_t pid;
	int status;
	
	fd = open("abc.txt", O_RDWR);
	
	ptr = (char *) mmap(0, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if(ptr == MAP_FAILED){
		printf("Error during mapping");
		return 1;
	}
	
	//printf("The length of ptr : %d", sizeof(ptr));

	for(i = 0; i<6; i++){
		printf(" %d - byte : %c\n",i, ptr[i]);
	}
	
	pid = fork();

	if(!pid){
		printf("child will change the value\n");
		//ptr[0] = 'j';
		//ptr[1] = 'p';
		write(fd, "JP", 2);
		close(fd);
		ret = write(fd, "x",1);
		if(ret<0){
			printf("Write X fails");
			exit(0);
		}
		exit(0);	
	}
	
	if(pid){
		printf(" in parent \n");
		wait(&status);
		write(fd, "12",2);
		//printf(" Meg from child : %s",status);
		
		ret = munmap(ptr, 10);
	
		if(ret !=0){
			printf("Failed to unmap");
			return 1;
		}
	}	
}


	//ptr[8] = '1';
#if 0



#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

       int
       main(int argc, char *argv[])
       {
           char *addr;
           int fd,ret;
           struct stat sb;
           off_t offset, pa_offset;
           size_t length;
           ssize_t s;

           if (argc < 3 || argc > 4) {
               fprintf(stderr, "%s file length [offset]\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           fd = open(argv[1], O_RDWR);
           if (fd == -1)
               handle_error("open");

           if (fstat(fd, &sb) == -1)           /* To obtain file size */
               handle_error("fstat");
	  printf ("PAGE_SIZE:%lx\n",sysconf(_SC_PAGE_SIZE));
           offset = atoi(argv[3]);
             pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
		printf ("pa_offset:%lx\n",pa_offset);
               /* offset for mmap() must be page aligned */

	  printf ("pa_offset:%lx file size:%lx\n",pa_offset,sb.st_size);
           if (offset >= sb.st_size) {
               fprintf(stderr, "offset is past end of file\n");
               exit(EXIT_FAILURE);
           }

           if (argc == 4) {
               length = atoi(argv[2]);
               if (offset + length > sb.st_size)
                   length = sb.st_size - offset;
                       /* Can't display bytes past end of file */

           } else {    /* No length arg ==> display to end of file */
               length = sb.st_size - offset;
           }
	   printf ("length:%ld\n",length);	
           getchar();
           addr = mmap(NULL, length + offset - pa_offset, PROT_EXEC | PROT_READ | PROT_WRITE,
                       MAP_SHARED, fd, pa_offset);
           if (addr == MAP_FAILED)
               handle_error("mmap");
	printf ("addr:%p %x\n",addr,*addr);	
//		*addr = 0x41;
//	ret =	msync(NULL, length + offset - pa_offset,MS_ASYNC);
//	printf ("msync return value:%d\n",ret);
           s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
           if (s != length) {
               if (s == -1)
                   handle_error("write");

               fprintf(stderr, "partial write");
               exit(EXIT_FAILURE);
           }
	getchar();
           exit(EXIT_SUCCESS);

}

#endif
