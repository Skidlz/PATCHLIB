/* patched.c patch edit routines for patchlib.c */

#include <stdio.h>		/* compiler library module header */
#include <ctype.h>
#include <conio.h>

#include "standard.h"	/* header files for patchlib.c */
#include "writscrn.h"
#include "patchlib.h"
#include "patched.h"
#include "chain.h"

#include "edstruct.h"
#include "io401.h"
#include "bioscall.h"


edpatch(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM],
		struct strchain *chain[])	/* edit patch parameters */
{
	int pick;
	pick = 0;

	while (1) {
		clearsc();
		while (kbhit()) getch();				/* clear any stray keypress */
		dispchain(chain[1]);					/* display screen */

		decode(patchno, param, name,tonebyte);	/* get patch data */
		writword(RVC,name,68,0);				/* put patch name in upper left */

		pick = movescrn(ajuno2,pick,7);
		switch (pick){
		case (0): edval(NPARAMS3,ajuno3,chain[2],param,name); break;
		case (1):
		case (2): edval(NPARAMS5,ajuno5,chain[4],param,name); break;
		case (3):
		case (4): edval(NPARAMS6,ajuno6,chain[5],param,name); break;
		case (5): edval(NPARAMS4,ajuno4,chain[3],param,name); break;
		case (6): edval(NPARAMS7,ajuno7,chain[6],param,name); break;
		case (-2):
		case (7): return(1);
		default:
			writerr("Esc to exit, ret to select.");
			pick = 0;
		}
		encode(patchno, param, name, tonebyte);	/* put data back in tonebyte */
	}
}




edval(int numel, struct selement *scrn,
		struct strchain *chain, int param[], char name[])
{
	int key, n, val, xpos, ypos, pick;
	char sval[6];

	clearsc();
	dispchain(chain);				/* put screen image on crt */

	writword(RVC,name,68,0);		/* put patch name in upper left*/

	for (n = 0; n < numel -1; n++){		/* put all current values on */
		key = scrn[n].key;
		val = param[key];
		xpos = ajscrn[key].xpos;
		ypos = ajscrn[key].ypos;
		itoa(val,sval,10);
		writword(BWC,sval,xpos,ypos);
	}

	pick = 0;
	while (1){
		pick = movescrn(scrn,pick,numel -1);
		if (pick == -2 || pick == numel -1)
			return(1);
		else if (pick == -3){
			writerr("Pick selection using arrow keys, then hit return");
			clearcsr(numel,scrn);
			pick = 0;
		} else if (pick == -1){
			writerr("Unexpected input, try again.");
			clearcsr(numel,scrn);
			pick = 0;
		} else {
			writword(BWC,"Enter value: ",0,SCRNTALL -2);
			gets(sval);

			if (*sval != '\0'){
				val = atoi(sval);
				key = scrn[pick].key;

				if (val < 0 || val > ajscrn[key].max)
					writerr("Value entered is out of range.");
				else{
					param[key] = val;
					xpos = ajscrn[key].xpos;
					ypos = ajscrn[key].ypos;
					itoa(val,sval,10);
					writword(BWC,"     ",xpos,ypos);
					writword(BWC,sval,xpos,ypos);
				}
			}
			writword(BWC,"                       ",0,SCRNTALL-2);
		}
	}
}





clearcsr(int numel,struct selement *scrn)	/* clear curser areas following error recovery */
{
	int n;

	for (n = 0; n< numel; n++){
		writword(BWC,scrn[n].content,scrn[n].xpos,scrn[n].ypos);
	}
}



clearval(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM])	/* sets all patch values to zero */
{
	int n;

	for (n = 0; n <= 35; n++){
		param[n] = 0;
	}
	strcpy(name,"         ");
	encode(patchno, param, name, tonebyte);
}



namepatch(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM])	/* name patch being edited */
{
	char newname[12];

	decode(patchno, param, name, tonebyte);
	writword(BWC,"Current patch name is: ",0,SCRNTALL - 4);
	puts(name);
	while (kbhit()) getch();			/* clear any stray keypress */

	writword(BWC,"Enter new name (ret to quit) -> ",0,SCRNTALL - 3);
	fgets(newname,11,stdin);

	if (*newname != '\n'){
		if (isupper(*newname) || islower(*newname) || isdigit(*newname)){
			strcpy(name,"          ");
			strcpy(name,newname);
			encode(patchno, param, name, tonebyte);
		} else {
			writerr("Not a valid name.");
		}
	}
}

