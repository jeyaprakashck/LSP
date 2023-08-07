#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
#include<stdint.h>
#include<inttypes.h>

int main(int argc, char *argv[]){

	int i;
	int j;
	
	int fbFD, bmpFD;
	unsigned int *bmp_ptr;
	unsigned int *fb_ptr;
	unsigned int temp;
	unsigned int fbSize;
	unsigned int lineLength;
	
	typedef struct __attribute__((packed)){
		uint16_t fileType;
		uint32_t sizeOfBMP;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t offset;
	}bmpHeader;
	
	typedef struct __attribute__((packed)){
		uint32_t sizeOfDIBHeader;
		uint32_t width_px;
		uint32_t height_px;
		uint16_t numberOfPlanes;
		uint16_t bitsPerPixel;
		uint32_t compression;
		uint32_t sizeOfRawData;
		uint32_t xres;
		uint32_t yres;
		uint32_t importantColors;
	}dibHeader;	
	
	bmpHeader kmLogoBMPHeader;
	dibHeader kmLogoDIBHeader;
	struct fb_fix_screeninfo fix_info;
	struct fb_var_screeninfo var_info;
	struct stat info;
	
	typedef struct{
		char bits_per_pixels;
		char xres;
		char yres;
	}bmp_info;
	


//step1: 
	fbFD = open("/dev/fb0", O_RDWR);
	
	if(fbFD<0){
		perror("Open fails\n:");
		exit(0);
	}

	if(ioctl(fbFD, FBIOGET_FSCREENINFO, &fix_info)){
		printf("Error while fetching Fix screen info");
		exit(1);
	}

	if(ioctl(fbFD, FBIOGET_VSCREENINFO, &var_info)){
		printf("Error while fetching var screen info");
		exit(2);
	}

	printf("Line length:%d\n", fix_info.line_length);
	printf("xres : %d, yres : %d, bpp : %d\n",var_info.xres, var_info.yres, var_info.bits_per_pixel);

	
//step 2:
	
	bmpFD = open("KM_LOGO_800x600_32.bmp",O_RDWR);
	i = read(bmpFD, &kmLogoBMPHeader, sizeof(bmpHeader));
	if(i<0){
		printf("Error during read");
		exit(0);
	}
	
	
	i = read(bmpFD, &kmLogoDIBHeader, sizeof(dibHeader));
	if(i<0){
		printf("Error during read");
		exit(0);
	}
	//BMP Header
	printf("%hd\n", kmLogoBMPHeader.fileType);
	printf("%d\n", kmLogoBMPHeader.sizeOfBMP);
	printf("%hd\n", kmLogoBMPHeader.reserved1);
	printf("%hd\n", kmLogoBMPHeader.reserved2);
	printf("%d\n", kmLogoBMPHeader.offset);

	//DIB Header
	printf("%d\n", kmLogoDIBHeader.sizeOfDIBHeader);
	printf("%d\n", kmLogoDIBHeader.width_px);
	printf("%d\n", kmLogoDIBHeader.height_px);
	printf("%hd\n", kmLogoDIBHeader.numberOfPlanes);
	printf("%hd\n", kmLogoDIBHeader.bitsPerPixel);
	printf("%d\n", kmLogoDIBHeader.compression);
	printf("%d\n", kmLogoDIBHeader.sizeOfRawData);
	printf("%d\n", kmLogoDIBHeader.xres);
	printf("%d\n", kmLogoDIBHeader.yres);

//step 3:(Comparing BMP resolution with framebuffer resolution)
	if((var_info.xres <= kmLogoDIBHeader.xres) && \
	   (var_info.yres <= kmLogoDIBHeader.yres) && \
	   (var_info.bits_per_pixel <= kmLogoDIBHeader.bitsPerPixel)){
		printf("Resolutions matching\n");
	}
		
	
//step 4 :

	//fbSize = var_info.xres * var_info.yres * var_info.bits_per_pixel/8;
	fbSize =(fix_info.line_length)* (var_info.yres);
	printf("fbSize : %d", fbSize);
	fb_ptr = mmap(NULL, fbSize, PROT_READ | PROT_WRITE, MAP_SHARED, fbFD, 0);
	if(((void *)fb_ptr) < 0){
		printf("Mapping failed");
		exit(0);
	}
	

//step 5 :

	lseek(bmpFD, kmLogoBMPHeader.offset, SEEK_SET);
	lineLength = (fix_info.line_length)/4;
	printf("Line Length : %d \n", lineLength);
	
//step 6 :
	
	for(i = 0; i < kmLogoDIBHeader.height_px-1; i++){
		for(j = 0; j<kmLogoDIBHeader.width_px; j++){
			if(read(bmpFD, &temp, 4)<0){
				printf("Error during read from bmpFD");
				exit(0);
			}
			
		//	fb_ptr[i * lineLength + j] = (temp);
		}
	}
	
	munmap(fb_ptr, fbSize);

	close(bmpFD);
	close(fbFD);
}
