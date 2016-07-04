/*
 * patchprt.h
 *
 *  Created on: Jul 2, 2016
 *      Author: Zack
 */

#ifndef PATCHPRT_H_
#define PATCHPRT_H_

#define NUMACROSS		4		/* number of patches to print across page */
#define PATPERBANK		8		/* number of patches per bank on synth */
#define SELECTWID		NUMACROSS * 4	/* string width to specify patches */
#include "patchlib.h"

void printpatch(char libname[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* print patch parameters to line printer */

printval(char select[], char libname[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);		/* workhorse printing routine */

#endif /* PATCHPRT_H_ */
