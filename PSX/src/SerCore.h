#ifndef SERCORE_HEADER
#define SERCORE_HEADER

#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <kernel.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>
#include <libapi.h>
#include <libsio.h>
#include <libpress.h>
#include <libetc.h>
#include <libmath.h>
#include <libcomb.h>
#include <libtap.h>
#include <libgs.h>
#include <libsn.h>
#include <string.h>
#include <strings.h>
#include <setjmp.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void initSerCore();
void clearBuffer();

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar);
long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func);
unsigned long cbTransmit(unsigned int spec, unsigned int startLoc, unsigned int countBit);

void resetRC();
void OPENP();
void CLOSEP(int e);
void syncSC(int e);
int Write(int cbStart, int cbStop);
int fillBuffer(char str[], int startBit, int endBit);

#endif
