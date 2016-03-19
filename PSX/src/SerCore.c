#include "System.h"
#include "SerCore.h"

int baudrate = 115200;

long rc,n;
int i,j,k;
int bsize = 256;

char *ser[256];
char *buf[256];
char *dev;
char *clear = 0x00;
char eol = '\n';

unsigned int start;
unsigned int count;

void initSerCore() {
	
	dev = "sio";
	AddCOMB();
	//OPENP();
	
	clearBuffer();
	
	/*
	buf[1] = "A";
	
	if (write(*dev, buf[1], 1)) {
		printf("Wrote: %c \n", buf[1]);
	} else {
		printf("Failed Write\n");
	}
	*/
	
	printf("SerCore Initialized\n");
	
	//CLOSEP(1);
}

void clearBuffer() {
	//clear the buffer :D
	for (j = 0; j <= 256; j++) {
		buf[j] = clear;
	}
}

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar) {
	_sio_control(cmd, arg, cbVar);
}

long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func) {
	_comb_control(cmd, arg, func);
}

unsigned long cbTransmit(unsigned int spec, unsigned int startLoc, unsigned int countBit) {
	
	StartRCnt(rc);
	
	start = startLoc;
	count = countBit;
	
	OPENP();
	
	if (spec) {
		//read
		for (i = start; i <= count; i++) {
			read(*dev, ser[i], 1);
			syncSC(0);
			printf(" %hhX ", ser[i]);			
		}
		
		if (i >= 1) {
			i = 0;
		}
		
		printf("Read Complete\n");
	} else if (spec == 2) {
		//write
		for (i = start; i <= count; i++) {
			write(*dev, buf[i], 1);
			syncSC(0);
			printf(" %hhX ", buf[i]);
		}
		
		if (i >= 1) {
			i = 0;
		}

		printf("Write Complete\n");
	}	
	
	CLOSEP(1);
	StopRCnt(rc);
	
}

void resetRC() {
	ResetRCnt(rc);
}

int Write(int cbStart, int cbStop) {	
	if(cmdCOM(1, 4, cbTransmit(2, cbStart, cbStop))) {
		printf("wrote data - complete\n");
		printf("Root Counter Value: %l \n", rc);
		return 1;
	}
	return 0;
}

void OPENP() {
	open(dev, O_RDWR);
}

void CLOSEP(int e) {
	if (e) {
		close(1);
	}
	if (!e) {
		close(0);
	}
}

void syncSC(int e) {
	//1
	if (e) {
		resetRC();
		clearBuffer();
	}
	//0
	if (!e) {
		CLOSEP(e);
		OPENP();
	}
}

int fillBuffer(char str[], int startBit) {
	int strCnt = sizeof(str);
	char stopBit = 0xEF;
	
	if (!(strCnt <= 255))
		return 0;
		
	
	for (k = 0; k <= strCnt; k++) {
		*buf[k] = str[k];
		
	}
	
	*buf[256] = stopBit;
	
	return 1;
}