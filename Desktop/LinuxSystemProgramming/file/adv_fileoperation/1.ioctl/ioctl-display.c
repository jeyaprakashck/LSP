#include<stdio.h>
#include<linux/fb.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
	
	int fd;
	int ret;
	struct fb_var_screeninfo fix;
	
	fd = open("/dev/fb0", O_RDONLY);
	if(fd<0){
		printf("Error in file open");
		exit(0);
	}
	
	ret = ioctl(fd, FBIOGET_VSCREENINFO, &fix);
	if(ret<0){
		printf("ioctl fails");
		exit(0);
	}
	
	printf("xres : %d", fix.xres);

}
