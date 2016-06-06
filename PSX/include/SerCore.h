#ifndef SERCORE_HEADER
#define SERCORE_HEADER

#include <PSSFCore.h>

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar);
long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func);
unsigned long cbTransmit(unsigned int spec, unsigned int countBit, char *dev, char *buf[]);

void clearBuffer(char *buf[]);
void syncPort();
/*
int Write(int cbCount, char *dev, char *buf[]);
int prepPacketChar(char str[], char *dev, char *buf[]);
int buildPacket(char str_data[]);
*/
#endif
