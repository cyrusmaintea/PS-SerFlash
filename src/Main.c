#include "System.h"

#define BPS 115200

#define RED   125
#define GREEN 125
#define BLUE  125
#define CCAP  254

#define MODE  			MODE_NTSC
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240

u_long pad;
char *version = "0.0.2";

extern char *ser[256];
extern char *buf[256];

char dbgStr[] = "HELLOWORLD";

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
	FntPrint("** Serial Port Based Flasher v%s  **\n", version);
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
	if (fillBuffer(dbgStr, 1)) {
		FntPrint("Buffer Filled\n");
	}
	
	FntPrint("\t\tSending Buffer Data\n");
	if (Write(1, sizeof(dbgStr))) {
		FntPrint("Wrote Buffer Data: %c \n", dbgStr);
	}
	
	FntPrint("\n\n(X) Continue\n");
	FntFlush(0);
	
	while (1) {
		pad = PadRead(0);
		sync();
		
		if (pad & PADRdown) {
			Menu();
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
	PadStop();
	ResetGraph(0);
	StopCallback();
	
	printf("~ Program End\n");
	DelSIO();
	DelCOMB();
	__asm__("J 0x801ECD94");
	
	return 0;
}