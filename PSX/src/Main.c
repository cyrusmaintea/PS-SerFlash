#include <Main.h>

#define     VERS            "0.0.7"
#define     BPS             115200
#define     BUFFSIZE        256
#define     BUFFCUT         BUFFSIZE-1
#define 	SIZE(x)			sizeof(x)

extern char *ser[BUFFSIZE];
extern char *buf[BUFFSIZE];
extern char *clear;
extern char *dev;

u_long pad;
int done = 0;
char *dbgStr = "HELLO WORLD";

int main() {

	initGfx();

	dev = "tty";
	initSerCore(*dev, BPS);
	openPort();

	PadInit(0);

	Menu();

	while(!done) {
		if(done) {
			break;
		}
		continue;
	}

	return 0;
}

void Menu() {

	printf("~ Menu Loaded\n");

	clearScreen();

	FntPrint("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	FntPrint("~~ Play Station 1 PIO Device Flasher ~~\n");
	FntPrint("~~ Serial Port Based Flasher v%s  ~~\n", VERS);
	FntPrint("~~               Menu                ~~\n");
	FntPrint("~~                                   ~~\n");
	FntPrint("~~ (X) Continue        (O) Shutdown  ~~\n");
	FntPrint("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	FntFlush(0);

	while(1) {
		pad = PadRead(0);
		sync();

		if (pad & PADRright) {
			Exit();
		}

		if (pad & PADRdown) {
			dbgMenu();
		}
	}
}

void dbgMenu() {

	printf("~ Debug Menu Loaded\n");

	clearScreen();

	FntPrint("Begin Serial Communication\n");
	printf("~ Begin Serial Communication\n");
	syncN(1);
	FntPrint("Filling Buffer\n");
	printf("~ Filling Buffer\n");
	syncN(3);

	if (!fillBuffer(clear, 0, BUFFSIZE)) {
		printf("* Failed Filling Buffer!\n");
	}
	syncN(1);

	FntPrint("Buffer Filled\n");
	printf("~ Buffer Filled\n");
	syncN(1);

	/*
	FntPrint("\t\tSending Buffer Data\n");
	printf("~ Sending Buffer Data\n");
	syncN(3);

	if (!Write(SIZE(dbgStr))) {
		printf("* Failed Writing Data!\n");
	}
	syncN(1);

	printf("Wrote Buffer Data: %s \n", dbgStr);
	FntPrint("Wrote Buffer Data: %s \n", dbgStr);
	*/

	FntPrint("\n\n(X) Continue\t\t(O) Shutdown\n");
	FntFlush(0);

	while(1) {
		pad = PadRead(0);
		sync();

		if (pad & PADRdown) {
			Menu();
		}

		if (pad & PADRright) {
			Exit();
		}
	}
}

void Exit() {

	closePort();
	PadStop();
	printf("~ Program End\n");

	done = 1;
	__asm__("J 0x801ECD94");
}
