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

	VSync(0);
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
	VSync(0);
	ClearImage(&clearRect, 0, 0, 0);
}

void clearColor(int r, int g, int b) {
	RECT	clearRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	VSync(0);
	ClearImage(&clearRect, r, g, b);
}
