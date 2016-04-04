#include <SerCore.h>

#define     BUFFSIZE        256
#define     BUFFCUT         BUFFSIZE-1

char *ser[BUFFSIZE];
char *buf[BUFFSIZE];
char *dev;
char *clear = 0x00;
char eol = '\n';
long rc,n;
int i,j,k;

int initSerCore(char *device, int bits) {
	dev = device;
	AddSIO(bits);
	clearBuffer();

	printf("~ SerCore Initialized\n");
	return 1;
}

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar) {
	_sio_control(cmd, arg, cbVar);
}

long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func) {
	_comb_control(cmd, arg, func);
}

unsigned long cbTransmit(unsigned int spec, unsigned int countBit) {
	unsigned int count;
	count = countBit;

	if (spec) {
		//read
		for (i = 0; i <= count; i++) {
			read(*dev, ser[i], 1);
			printf(" %hhX ", ser[i]);
		}
		if (i >= 1) {
			i = 0;
		}
		printf("~ Read Complete\n");
	} else if (spec == 2) {
		//write
		for (i = 0; i <= count; i++) {
			write(*dev, buf[i], 1);
			printf(" %hhX ", buf[i]);
		}
		if (i >= 1) {
			i = 0;
		}
		printf("~ Write Complete\n");
	}
}

void clearBuffer() {
	//clear the buffer :D
	for (j = 0; j <= BUFFSIZE; j++) {
		buf[j] = clear;
	}
}

void syncPort() {
	closePort();
	openPort();
}

int openPort() {
	if(open(dev, O_RDWR) != -1)
		return 0;
	return 1;
}

int closePort() {
	if(close(*dev) != -1)
		return 0;
	return 1;
}

int Write(int cbCount) {
	if(cmdSIO(1, 4, cbTransmit(2, cbCount))) {
		printf("~ Wrote data - Complete\n");
		printf("~ Root Counter Value: %l \n", rc);
		return -1;
	}
	return 1;
}

// start & stop bit ranges = 1 - 255
int fillBuffer(char str[], int startBit, int endBit) {
	int strSize = sizeof(str);
	char stopBit = 0xEF;

	if (!(strSize <= BUFFCUT))
		return 0;

	for (k = startBit; k <= endBit; k++) {
		*buf[k] = str[k];
	}

	*buf[endBit] = stopBit;
	return 1;
}
/*
int sendPacketChar(char str[]) {
	int strSize = sizeof(str);

	if (!(strSize <= BUFFCUT))
		return 0;

	return 1;
}
*/
