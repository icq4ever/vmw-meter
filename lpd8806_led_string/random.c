#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/spi/spidev.h>

#include "spi_lib.h"

#define MAX_BRIGHTNESS 64

int main(int argc, char **argv) {

	int spi_fd,i,j;
	unsigned char zeros[128],data[128];
	int result;

	/* Open the SPI device */

	spi_fd=spi_open("/dev/spidev0.0", SPI_MODE_0, 100000, 8);
	if (spi_fd<0) {
		exit(-1);
	}

	/* Zero out our framebuffer */
	for(i=0;i<128;i++) zeros[i]=0;

	/* Set data to all black */
	for(i=0;i<128;i++) data[i]=128;

	/* Set display to black */
	for(i=0;i<128;i++) {
		result=write(spi_fd,&zeros[i],1);
		if (result<1) {
			printf("error!\n");
			exit(-1);
		}
	}


	while(1) {

		for(i=0;i<32;i++) {
			data[(i*3)]=128+random()%MAX_BRIGHTNESS;
			data[(i*3)+1]=128+random()%MAX_BRIGHTNESS;
			data[(i*3)+2]=128+random()%MAX_BRIGHTNESS;

		}

		for(i=0;i<128;i++) {
			result=write(spi_fd,&data[i],1);
			if (result<1) {
				printf("error!\n");
				exit(-1);
			}
		}

		for(i=0;i<128;i++) {
			result=write(spi_fd,&zeros[i],1);
			if (result<1) {
				printf("error!\n");
				exit(-1);
			}
		}
		usleep(200000);

	}

	spi_close(spi_fd);

	return 0;
}
