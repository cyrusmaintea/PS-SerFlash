
int baudrate;
int bsize;

long rc,n;

char *ser[256];
char *buf[256];
char *dev;
char eol;

void initSerCore();
void clearBuffer();

long cmdSIO(unsigned long cmd, unsigned long arg, unsigned long cbVar);
long cmdCOM(unsigned long cmd, unsigned long arg, unsigned long func);
unsigned long cbTransmit(unsigned int spec, unsigned int startLoc, unsigned int countBit);

int Write(int cbStart, int cbStop);
void resetRC();
void OPENP();
void CLOSEP(int e);
void syncSC(int e);
int fillBuffer(char str[], int startBit);