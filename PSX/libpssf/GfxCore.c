#include <GfxCore.h>

#define     MODE  			MODE_NTSC
#define     SCREEN_WIDTH    320
#define     SCREEN_HEIGHT   240

void initGfx() {
	DISPENV	disp;
	DRAWENV draw;

	ResetGraph(0);
	SetDefDispEnv(&disp, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	disp.isinter = 1;
	disp.isrgb24 = 0;
	SetDefDrawEnv(&draw, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	sync();
	PutDispEnv(&disp);
	PutDrawEnv(&draw);
	clearScreen();
	SetDispMask(1);
	printf("~ Initialized System\n");

	FntLoad(960, 0);
	FntOpen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 512);
	printf("~ Initialized Font\n");
}

void clearScreen() {
	RECT	clearRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	sync();
	ClearImage(&clearRect, 0, 0, 0);
}

void clearColor(int r, int g, int b) {
	RECT	clearRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	sync();
	ClearImage(&clearRect, r, g, b);
}

void sync() {
	VSync(0);
}

void syncN(int n) {
	VSync(n);
}
