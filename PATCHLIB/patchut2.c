/* patchut2.c	second bank of utility routines for patchlib.c */

#define TURBOC	1	/* comment out if using Microsoft compiler */

#include <stdio.h>		/* compiler library module headers */
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef TURBOC
	#include <dir.h>		/* Turbo C version */
#else
	#include <direct.h>			/* Microsoft C version */
#endif

#include "standard.h"	/* header and data files for patchlib.c */
#include "writscrn.h"
#include "patchlib.h"

#include "patchut2.h"
#include "bioscall.h"


selpatch(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM])	/* choose a patch to edit */
{
	int patch;
	static char innum[4];

	innum[0] = '\0';
	clearsc();
	fputs("Patch number is the synth bank (1-8) followed by number (1-).\n\n"
			,stdout);

	dispnames(tonebyte);
	while (kbhit()) getch();					/* clear stray inputs */
	patch = getpatno(SCRNTALL - 2,
			"Enter the patch number to edit (ret to exit) ->");
	if (patch >= 0){
		decode(patch, param, name, tonebyte);
		return(patch);
	} else {
		return(patchno);
	}
}




movepatch(int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM])		/* move a patch to a new location */
{
	int sorsno, destno;

	while (1){
			clearsc();
			fputs("Current patch locations are as follows:\n\n",stdout);

			dispnames(tonebyte);
			sorsno = getpatno(SCRNTALL -4,
					"Enter source patch number (ret to exit) ->");
			if (sorsno == -1)
				return(1);

			destno = getpatno(SCRNTALL -4,
					"Enter destination patch (ret to exit, overwrites old patch) ->");
			if (sorsno == -1)
				return(1);

			decode(sorsno, param, name, tonebyte);
			decode(destno, param, name, tonebyte);
	}
}



import(char patdir[], char prodir[],
		unsigned char tonebyte[NPATCH][NCODPARAM])	/* bring a patch in from another library */
{
	static char seclib[14];
	static unsigned char sectone[NPATCH][NCODPARAM];
	int i, status, inpatno, savpatno;

	status = picklib(seclib, patdir, prodir, sectone,
			"Enter the nme of the second library you wish to access ->");
	if (status == -1)
		return(-1);

	clearsc();
	fputs("Patches available in import file:",stdout);
	fputs(seclib,stdout); fputs("\n\n",stdout);
	dispnames(sectone);
	inpatno = getpatno(SCRNTALL-4,
			"Enter the patch number you wish to import (ret to exit)->");
	if (inpatno == -1)
		return(-1);

	clearsc();
	fputs("Patches currently in memory:",stdout);
	fputs("\n\n",stdout);
	dispnames(tonebyte);
	writword(BWC,"*** The patch at the destination number will be deeted ***",
			0, SCRNTALL - 4);
	savpatno = getpatno(SCRNTALL-3,
			"Enter the destination patch number for the import patch->");
	if (savpatno == -1)
		return(-1);

	for (i = 0; i < NCODPARAM; i++){
		tonebyte[savpatno][i] = sectone[inpatno][i];
	}
	return(savpatno);
}



getpatno(int line, char string[])			/* prompt for patch number selected */
{
	int patch;
	static char innum[4];

	while (1){
		csrplot(0,line);				/* clear the prompt line */
		writbw(' ',79);
		while (kbhit()) getch();			/* clear any stray keypress */
		writword(BWC,string,0,line);
		gets(innum);
										/* return -1 if no selection */
		if (innum[0] == '\n' || innum[0] == '\0' || innum[0] == ESC)
			return(-1);
										/* map 11 to 0, 88 to 63 */
		if (isdigit(innum[0]) &&  isdigit(innum[1])){
			patch = ((innum[0] - '0' - 1) * 8) + (innum[1] - '0' - 1);
			if (patch >= 0 && patch <= NPATCH - 1)
				return(patch);
			else
				writerr("Patch number must be between 11 and 88");
		} else {
			writerr("Patch number must be two digits, 11 to 88");
		}
	}
}




dispnames(unsigned char tonebyte[NPATCH][NCODPARAM])		/* list patch names and numbers on screen */
{
	int n, m, patch, bank, number;
	static int param[NPARAM];
	char bchr, nchr;
	static char name[11];

	for (n = 0; n < NPATCH/4; n++){
		for (m = 0; m < 4; m++){
			patch = (n * 4) + m;
			bank = (patch/8) + 1;
			number = (patch % 8) + 1;
			bchr = bank + '0';
				fputc(bchr, stdout);
			nchr = number + '0';
				fputc(nchr, stdout);
			fputs(") ",stdout);
			decode(patch, param, name, tonebyte);
			name[10] = '\0';
			fputs(name, stdout);
			fputs("  ",stdout);
		}
		fputc('\n', stdout);
	}
}

