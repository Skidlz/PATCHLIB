/*
 * edstructs.h
 *
 *  Created on: Jul 4, 2016
 *      Author: Zack
 */

#ifndef EDSTRUCT_H_
#define EDSTRUCT_H_
#include "patchlib.h"
#include "chain.h"

struct location {		/* structure for screen location of displayed data */
	int max;			/* maximum value (min assumed to be 0) */
	int xpos;			/* x and y pos to display on screen - assumed to */
	int ypos; };		/* only to be displayed on one screen */

struct location ajscrn[36] = {
		{3,		15,	9 },			/* 0 */
		{3,		16,	13 },
		{3,		15,	10 },
		{3,		15,	12 },
		{5,		15,	13 },
		{5,		15,	14 },			/* 5 */
		{3,		15,	6 },
		{3,		15,	15 },
		{3,		15,	16 },
		{3,		16,	8 },
		{1,		15,	12 },			/* 10 */
		{127,	15,	7 },
		{127,	15,	8 },
		{15,	15,	10 },
		{127,	15,	17 },
		{127,	15,	18 },			/* 15 */
		{127,	16,	9 },
		{127,	16,	11 },
		{127,	16,	14 },
		{127,	16,	12 },
		{15,	16,	15 },			/* 20 */
		{15,	16,	16 },
		{127,	15,	9 },
		{15,	15,	11 },
		{127,	12,	9 },
		{127,	12,	10 },			/* 25 */
		{127,	5,	14 },
		{127,	22,	14 },
		{127,	5,	15 },
		{127,	22,	15 },
		{127,	5,	16 },			/* 30 */
		{127,	22,	16 },
		{127,	5,	17 },
		{15,	22,	18 },
		{127,	15,	13 },
		{12,	15,	11 },			/* 35 */
};


/* the following define the screen curser locations using the */
/* structure conventions from writscrn.c + writscrn.h */


struct selement ajuno2[NPARAMS2] = {
		{4,		4,	"DCO",			7,	5,	4,	1,	0 },
		{18,	4,	"HPF",			1,	5,	0,	2,	1 },
		{33,	4,	"VCF",			2,	7,	1,	3,	2 },
		{47,	4,	"VCA",			3,	6,	2,	4,	3 },
		{60,	4,	"CHORUS",		4,	6,	3,	0,	4 },
		{2,		12,	"LFO",			0,	7,	6,	6,	5 },
		{53,	13,	"ENV",			3,	6,	7,	6,	6 },
		{4,		17,	"RETURN",		5,	7,	5,	6,	7 }
};

struct selement ajuno3[NPARAMS3] = {
		{0,	6,	"DCO RNG",			13,	1,	0,	0,	6 },
		{0,	7,	"DCO LFO LEVEL",	0,	2,	1,	1,	11 },
		{0,	8,	"DCO ENV LEVL",		1,	3,	2,	2,	12 },
		{0,	9,	"DCO ENV MODE",		2,	4,	3,	3,	0 },
		{0,	10,	"DCO AFTR",			3,	5,	4,	4,	13 },
		{0,	11,	"DCO BEND",			4,	6,	5,	5,	35 },
		{0,	12,	"PULSE",			5,	7,	6,	6,	3 },
		{0,	13,	"SAWTOOTH",			6,	8,	7,	7,	4 },
		{0,	14,	"SUB WAVE",			7,	9,	8,	8,	5 },
		{0,	15,	"SUB LEVEL",		8,	10,	9,	9,	7 },
		{0,	16,	"NOIS LEVL",		9,	11,	10,	10,	8 },
		{0,	17,	"PW/PWM",			10,	12,	11,	11,	14 },
		{0,	18,	"PWM RATE",			11,	13,	12,	12,	15 },
		{0,	20,	"RETURN",			12,	0,	13,	13,	-1 }
};


struct selement ajuno4[NPARAMS4] = {
		{0,	9,	"LFO RATE",			2,	1,	0,	0,	24 },
		{0,	10,	"LFO DELAY",		0,	2,	1,	1,	25 },
		{0,	12,	"RETURN",			1,	0,	2,	2	-1}
};


struct selement ajuno5[NPARAMS5] = {
		{0,	8,	"HPF FREQUENCY",	8,	1,	0,	0,	9 },
		{0,	9,	"VCF FREQUENCY",	0,	2,	1,	1,	16 },
		{0,	11,	"VCF RESONANCE",	1,	3,	2,	2,	17 },
		{0,	12,	"VCF ENV LEVEL",	2,	4,	3,	3,	19 },
		{0,	13,	"VCF ENV MODE",		3,	5,	4,	4,	1 },
		{0,	14,	"VCF LFO",			4,	6,	5,	5,	18 },
		{0,	15,	"VCF KEYBOARD",		5,	7,	6,	6,	20 },
		{0,	16,	"VCF AFTER",		6,	8,	7,	7,	21 },
		{0,	18,	"RETURN",			7,	0,	8,	8,	-1 }
};

struct selement ajuno6[NPARAMS6] = {
		{0,	9,	"VCA LEVEL",		5,	1,	0,	0,	22 },
		{0,	10,	"VCA ENV MODE",		0,	2,	1,	1,	2 },
		{0,	11,	"VCA AFTER",		1,	3,	2,	2,	23 },
		{0,	12,	"CHORUS",			2,	4,	3,	3,	10 },
		{0,	13,	"CHORUS RATE",		3,	5,	4,	4,	34 },
		{0,	15,	"RETURN",			4,	0,	5,	5,	-1 }
};



struct selement ajuno7[NPARAMS7] = {
		{0,	14,	"T1",				8,	1,	0,	4,	26 },
		{0,	15,	"T2",				0,	2,	1,	5,	28 },
		{0,	16,	"T3",				1,	3,	2,	6,	30 },
		{0,	17,	"T4",				2,	4,	3,	3,	32 },
		{17,14,	"L1",				3,	5,	0,	4,	27 },
		{17,15,	"L2",				4,	6,	1,	5,	29 },
		{17,16,	"L3",				5,	7,	2,	6,	31 },
		{0,	18,	"ENVELOPE KEY",		6,	8,	7,	7,	33 },
		{0,	19,	"RETURN",			7,	0,	8,	8,	-1 }
};


#endif /* EDSTRUCT_H_ */
