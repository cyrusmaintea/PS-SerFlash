#ifndef GFXCORE_HEADER
#define GFXCORE_HEADER

#include <PSSFCore.h>

void initGfx();
void clearScreen();
void clearColor(int r, int g, int b);
void sync();
void syncN(int n);

#endif
