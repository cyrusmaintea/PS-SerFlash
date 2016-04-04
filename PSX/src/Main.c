#include <Main.h>

#define     VERS            "0.0.5"
#define     BPS             115200
#define     BUFFSIZE        256
#define     BUFFCUT         BUFFSIZE-1
#define 	SIZE(x)			sizeof(x)

extern char *ser[BUFFSIZE];
extern char *buf[BUFFSIZE];
extern char *clear;

u_long pad;
int done = 0;
char *dbgStr = "HELLO WORLD";

int main() {

	AddSIO(BPS);
	initGfx();
	initSerCore();
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

	FntPrint("**___________________________________**\n");
	FntPrint("** Play Station 1 PIO Device Flasher **\n");
	FntPrint("** Serial Port Based Flasher v%s  **\n", VERS);
	FntPrint("**               Menu                **\n");
	FntPrint("**                                   **\n");
	FntPrint("** (X) Continue        (O) Shutdown  **\n");
	FntPrint("**___________________________________**\n");
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

	printf("~ Testing Serial Communication\n");

	FntPrint("Filling Buffer\n");
	printf("~ Filling Buffer\n");
	if (!fillBuffer(clear, 0, BUFFSIZE)) {
		printf("* Failed Filling Buffer!\n");
	}
	FntPrint("Buffer Filled\n");
	printf("~ Buffer Filled\n");

	FntPrint("\t\tSending Buffer Data\n");
	if (!Write(SIZE(dbgStr))) {
		printf("* Failed Writing Data!\n");
	}
	FntPrint("Wrote Buffer Data: %s \n", dbgStr);

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
	ResetGraph(0);
	StopCallback();
	PadStop();
	printf("~ Program End\n");
	DelSIO();
	done = 1;
	__asm__("J 0x801ECD94");
}
