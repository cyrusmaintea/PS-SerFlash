set PATH=C:\psx\psyq\bin
set PSYQ_PATH=C:\psx\psyq\bin

set prog=Main
set bootfn=PSX
set S=.\src\
set B=.\bin\

ccpsx -Xo$80010000 -O3 %S%%prog%.c %S%SerCore.c -o %B%%bootfn%.cpe,%B%%prog%.sym,%B%%prog%.map
cpe2x %B%%bootfn%.cpe
IF EXIST bin\PSX.exe (
	echo $null >> SUCCESS
) ELSE (
	pause	
	echo $null >> FAILED
)

