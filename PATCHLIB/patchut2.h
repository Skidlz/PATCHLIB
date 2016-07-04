/*
 * patchut2.h
 *
 *  Created on: Jul 2, 2016
 *      Author: Zack
 */

#ifndef PATCHUT2_H_
#define PATCHUT2_H_
#include  "patchlib.h"

selpatch(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* choose a patch to edit */

movepatch(int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);		/* move a patch to a new location */

import(char patdir[], char prodir[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* bring a patch in from another library */

getpatno(int line, char string[]);			/* prompt for patch number selected */

dispnames(unsigned char tonebyte[NPATCH][NCODPARAM]);		/* list patch names and numbers on screen */

#endif /* PATCHUT2_H_ */
