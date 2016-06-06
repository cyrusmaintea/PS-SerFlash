#include <SerCore.h>

#define     BUFFSIZE        256
#define     BUFFCUT         BUFFSIZE-1
#define     BPS             115200

char str_len = 0;
int i,j,k;
char *bufFile;

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar) {
	_sio_control(cmd, arg, cbVar);
}

long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func) {
	_comb_control(cmd, arg, func);
}

unsigned long cbTransmit(unsigned int spec, unsigned int countBit, char *dev, char *buf[]) {
	unsigned int count;
	count = countBit;

	if (spec) {
		//read
		for (i = 0; i <= count; i++) {
			read(*dev, buf[i], 1);
			printf(" %hhX ", buf[i]);
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

void clearBuffer(char *buf[]) {
	//clear the buffer :D
	for (j = 0; j < BUFFSIZE; j++) {
		buf[j] = "0x00";
	}
}

void syncPort(char *dev) {
	close(*dev);
	open(dev, O_RDWR);
}
/*
int Write(int cbCount, char *dev, char *buf[]) {
	if (cmdSIO(1, 4, cbTransmit(2, cbCount, dev, buf))) {
		printf("~ Wrote data - Complete\n");
		return 0;
	}
	return 1;
}

int prepPacketChar(char str[], char *dev, char *buf[]) {
	int strSize = sizeof(str);

	Write(strSize, dev, buf);

	return 1;
}

int buildPacket(char str_data[]) {

	do {
		str_len++;
	} while (str_data[str_len]);

	return sizeof(str_len);
}
*/
