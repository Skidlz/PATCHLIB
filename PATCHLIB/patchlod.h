/*
 * patchlod.h
 *
 *  Created on: Jul 2, 2016
 *      Author: Zack
 */

#ifndef PATCHLOD_H_
#define PATCHLOD_H_

#include "patchlib.h"

#define EXCL	0xF0	/* midi hex codes */
#define ENDEXCL	0xF7
#define ROLID	0x41	/* Roland ID */
#define AJUNOF	0x23
#define MIDWSF	0x40
#define MIDRQF	0x41
#define MIDDAT	0x42
#define MIDACK	0x43
#define MIDEOF	0x45
#define MIDERR	0x4E
#define MIDRJC	0x4F
#define MIDAPR	0x35

						/* MPU-401 op codes */
#define SYSRESET	0xFF	/* resets 401 out of art mode */
#define UART	0x3F	/* uart mode (simple com through 401 to synth */

download(int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);		/* put patch data from synth->tonebyte */

gettones(unsigned char tonebyte[NPATCH][NCODPARAM]);		/* get all compressed patches */

upload(unsigned char tonebyte[NPATCH][NCODPARAM]);		/* send sets of patch data to synth */

sendtones(unsigned char tonebyte[NPATCH][NCODPARAM]);		/* send all compressed patches */

getexcl(void);

sendexcl(unsigned int code);			/* send midi exclusive message */

getbits(unsigned x, int p,int n);			/* get n bits right of p in x */

roltoa(int n);			/* convert ajuno's letter  odes to ascii */

atorol(int n);		/* convert ascii to ajuno's letter codes */

decode(int num, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* convert tonebyte to int params/ name */

encode(int num, int param[], char name[],
		unsigned char tonebyte[NPATCH][NCODPARAM]);	/* convert params and name to tonebyte[n] */


#endif /* PATCHLOD_H_ */
