/* patched.h  data for edpatch.c */

#ifndef PATCHED_H_
#define PATCHED_H_
#include "patchlib.h"
#include "chain.h"


edpatch(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM],
		struct strchain *chain[]);	/* edit patch parameters */

edval(int numel, struct selement *scrn,
		struct strchain *chain, int param[], char name[]);

clearcsr(int numel,struct selement *scrn);	/* clear curser areas following error recovery */


clearval(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* sets all patch values to zero */


namepatch(int patchno, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* name patch being edited */


#endif /* PATCHED_H_ */
