#include <Main.h>

#define     VERS            "0.0.9"

#define     BPS             115200
#define     BUFFSIZE        128
#define     BUFFCUT         BUFFSIZE-1
#define 	SIZE(x)			sizeof(x)

#define		Flash128			0x00020000
#define		Flash256			0x00040000
#define		Flash512			0x00080000
#define 	RAM2				0x00200000
#define 	RAM4				0x00400000
#define 	RAM8				0x00800000
#define 	EXP					0x1F000000
#define 	CLEAR				0x00

#define		DBG					1


char *dev = "tty:";
char *clear = CLEAR;
int done;
u_long pad;
char dbgStr[] = "HELLO WORLD";
char *buf[BUFFSIZE];

int main() {

	done = 0;

	if (!DBG)
		open(dev, O_RDWR);

	if (DBG) {
		open(dev, O_RDWR);
		AddSIO(BPS);
	}

	printf("~ Program Entry\n");

	initGfx();

	PadInit(0);

	Menu();

	while (!done) {
		if (done)
			break;
	}

	printf("~ Program Exit\n");
	termSig();

	return 0;
}

void update() {

	pad = PadRead(0);
	VSync(0);

	if (pad & PADselect)
		done = 1;
	if (pad & PADRdown) {
		dbgMenu();
	}

}

void termSig() {
	close(*dev);
	clearScreen();
	PadStop();
	StopCallback();
	ResetGraph(0);
	if (DBG)
		DelSIO();
	__asm__("J 0x801ECD94");
}

void Menu() {

	printf("~ Menu Loaded\n");

	clearScreen();

	FntPrint("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	FntPrint("~~ Play Station 1 PIO Device Flasher ~~\n");
	FntPrint("~~ Serial Port Based Flasher v%s  ~~\n", VERS);
	FntPrint("~~               Menu                ~~\n");
	FntPrint("~~                                   ~~\n");
	FntPrint("~~ (X) Continue   (Select) Shutdown  ~~\n");
	FntPrint("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	FntFlush(0);
/*
	while(!done) {
		pad = PadRead(0);
		VSync(0);

		if (pad & PADRright) {
			done = 1;
		}else if (pad & PADRdown) {
			sioTestMenu();
		}
	}
*/
}

void dbgMenu() {

	printf("~ Debug Menu\n");

	clearScreen();

	FntPrint("~~ Debug Menu    |    Serial Comms  ~~\n");
	printf("~ Debug Menu | Serial Comms\n");
/*
	FntPrint("Parsing Data\n");
	printf("~ Parsing Data\n");
	printf("DEBUG STRING: %s \n", buf);

	clearBuffer(buf);
	FntPrint("Buffer Cleared\n");
	printf("~ Buffer Cleared\n");
*/
	FntPrint("~~ (X) Continue   (Select) Shutdown  ~~\n");
	FntFlush(0);
/*
	while (!done) {
		pad = PadRead(0);
		VSync(0);

		if (pad & PADRright) {
			done = 1;
		} else if (pad & PADRdown) {
			Menu();
		}
	}
*/
}
