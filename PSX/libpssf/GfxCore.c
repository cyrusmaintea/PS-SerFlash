#include <GfxCore.h>

#define     MODE  			MODE_NTSC
#define     RED             125
#define     GREEN           125
#define     BLUE            125
#define     SCREEN_WIDTH    320
#define     SCREEN_HEIGHT   240

void initGfx() {
	DISPENV	disp;
	DRAWENV draw;

	ResetGraph(0);
	SetDefDispEnv(&disp, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	disp.isinter = 0;
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
	ClearImage(&clearRect, RED, GREEN, BLUE);
}

void sync() {
	VSync(0);
}

void syncN(int n) {
	VSync(n);
}
