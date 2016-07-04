/*
 * patchut1.h
 *
 *  Created on: Jul 2, 2016
 *      Author: Zack
 */

#ifndef PATCHUT1_H_
#define PATCHUT1_H_

#include "patchlib.h"

pickdriv(char patdir[], char prodir[]);		/* change drive or dir name */

picklib(char libname[], char patdir[], char prodir[],
		unsigned char tonebyte[NPATCH][NCODPARAM], char prompt[]);	/* load a library file */

displib(char dir[]);						/* display list of library files */

savepatch(char lib[], char patdir[], char prodir[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);			/* store patches to disk */

#endif /* PATCHUT1_H_ */
