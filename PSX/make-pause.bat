set PATH=C:\psx\psyq\bin
set PSYQ_PATH=C:\psx\psyq\bin

set prog=Main
set bootfn=PSSF
set S=.\src\
set B=.\bin\
set INC=.\include
set LIBSRC=.\libpssf\
set DBG=.\debug\

ccpsx -I%INC% -Xo$80010000 -O3 %S%%prog%.c %LIBSRC%SerCore.c %LIBSRC%GfxCore.c -o %B%%bootfn%.cpe
cpe2x %B%%bootfn%.cpe

IF EXIST %B%%bootfn%.exe (
	echo $null >> SUCCESS
) ELSE (
	echo $null >> FAILED
)
pause