#ifndef SERCORE_HEADER
#define SERCORE_HEADER

#include <PSSFCore.h>

void initSerCore();
void clearBuffer();

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar);
long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func);
unsigned long cbTransmit(unsigned int spec, unsigned int countBit);

void resetRC();
void syncSC();
void syncPort();
int OPENP();
int CLOSEP();
int Write(int cbCount);
int fillBuffer(char str[], int startBit, int endBit);
int sendPacketChar(char str[]);

#endif
