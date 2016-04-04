#ifndef SERCORE_HEADER
#define SERCORE_HEADER

#include <PSSFCore.h>

#define     BUFFSIZE        256

char *ser[BUFFSIZE];
char *buf[BUFFSIZE];
char *dev;
char *clear;

int initSerCore(char *device, int bits);

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar);
long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func);
unsigned long cbTransmit(unsigned int spec, unsigned int countBit);

void clearBuffer();
void syncPort();
int openPort();
int closePort();
int Write(int cbCount);
int fillBuffer(char str[], int startBit, int endBit);
//int sendPacketChar(char str[]);

#endif
