#include <stdio.h>
#include <unistd.h>


int gpio_enable(int gpio) {

	FILE *fff;

	printf("Enabling GPIO%d for export\n",gpio);
	fff=fopen("/sys/class/gpio/export","w");
	if (fff==NULL) {
		fprintf(stderr,"\tError enablibg GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"%d\n",gpio);
	fclose(fff);

	return 0;

}

int gpio_set_write(int gpio) {

	FILE *fff;
	char string[BUFSIZ];

	printf("Setting GPIO%d for output\n",gpio);

	sprintf(string,"/sys/class/gpio/gpio%d/direction",gpio);

	fff=fopen(string,"w");
	if (fff==NULL) {
		fprintf(stderr,"\tError setting direction of GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"out\n");
	fclose(fff);

	return 0;
}


int gpio_set_read(int gpio) {

	FILE *fff;
	char string[BUFSIZ];

	printf("Setting GPIO%d for input\n",gpio);

	sprintf(string,"/sys/class/gpio/gpio%d/direction",gpio);

	fff=fopen(string,"w");
	if (fff==NULL) {
		fprintf(stderr,"\tError setting direction of GPIO%d!\n",gpio);
		return -1;
	}
	fprintf(fff,"in\n");
	fclose(fff);

	return 0;
}


int gpio_read(int gpio) {

	FILE *fff;
	char string[BUFSIZ];
	int value;

	sprintf(string,"/sys/class/gpio/gpio%d/value",gpio);

	fff=fopen(string,"r");
	if (fff==NULL) {
		fprintf(stderr,"\tError getting value!\n");
		return -1;
	}
	fscanf(fff,"%d",&value);
//	printf("\tCurrent value: %d\n",value);
	fclose(fff);

	return value;

}


int gpio_write(int gpio, int value) {

	FILE *fff;
	char string[BUFSIZ];

	sprintf(string,"/sys/class/gpio/gpio%d/value",gpio);

	fff=fopen(string,"w");
	if (fff==NULL) {
		fprintf(stderr,"\tError setting value!\n");
		return -1;
	}
	fprintf(fff,"%d\n",value);
	fclose(fff);

	return 0;

}
