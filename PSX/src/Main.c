#include "System.h"
#include "SerCore.h"

#define     MODE  			MODE_NTSC
#define     RED             125
#define     GREEN           125
#define     BLUE            125
#define     CCAP            254
#define     SCREEN_WIDTH    320
#define     SCREEN_HEIGHT   240
#define     VERS            "0.0.3"
#define     BPS             115200
#define     BUFFSIZE        256
#define     BUFFCUT         BUFFSIZE-1

extern char *buf[BUFFSIZE];
extern char *clear;

u_long pad;
char *dbgStr = "HELLOWORLD";

void Menu();
void dbgMenu();
void clearScreen();
void initSystem();
void sync();
void syncN(int n);
void draw();
int sysExit();

int main() {

	AddSIO(BPS);

	initSystem();
	initSerCore();

	PadInit(0);

	Menu();

	return 0;
}

void Menu() {

	printf("~ Menu Loaded\n");

	clearScreen();

	FntPrint("**___________________________________**\n");
	FntPrint("** Play Station 1 PIO Device Flasher **\n");
	FntPrint("** Serial Port Based Flasher v%s  **\n", VERS);
	FntPrint("**               Menu                **\n");
	FntPrint("**                                   **\n");
	FntPrint("** (X) Continue        (O) Shutdown  **\n");
	FntFlush(0);

	while (1) {

		pad = PadRead(0);
		sync();

		if (pad & PADRright) {
			sysExit();
		}

		if (pad & PADRdown) {
			//Flash PIO Menu
			dbgMenu();
		}
	}
}

void dbgMenu() {

	printf("~ Debug Menu Loaded\n");

	clearScreen();

	FntPrint("\tTesting Serial Communication\n");

	FntPrint("\t\tFilling Buffer\n");
	if (!fillBuffer(clear, 0, BUFFSIZE)) {
		FntPrint("Failed Filling Buffer!\n");
	}
	FntPrint("Buffer Filled\n");

	FntPrint("\t\tSending Buffer Data\n");
	if (!Write(1, sizeof(dbgStr))) {
		FntPrint("Failed Writing Data!\n");
	}
	FntPrint("Wrote Buffer Data: %s \n", dbgStr);

	FntPrint("\n\n(X) Continue\t\t(O) Shutdown\n");
	FntFlush(0);

	while (1) {

		pad = PadRead(0);
		sync();

		if (pad & PADRdown) {
			Menu();
		}

		if (pad & PADRright) {
			sysExit();
		}
	}
}

void clearScreen() {

	RECT	clearRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	sync();
	ClearImage(&clearRect, RED, GREEN, BLUE);

}

void initSystem()
{

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

void sync()
{
	VSync(0);
}

void syncN(int n)
{
	VSync(n);
}

void draw()
{
    DrawSync(0);
    sync();
    GsSwapDispBuff();
	/*
	 * Sort and Draw
	 */
}

int sysExit() {
	clearScreen();
	ResetGraph(0);
	StopCallback();
	PadStop();
	printf("~ Program End\n");
	DelSIO();
	__asm__("J 0x801ECD94");

	return 0;
}
