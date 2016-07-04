/* writescrn.h header file for writescrn.c */

#ifndef WRITSCRN_H_
#define WRITSCRN_H_

struct selement {
	int xpos;
	int ypos;
	char content[15];
	int nup;
	int ndown;
	int nleft;
	int nright;
	int key;
};

movescrn(struct selement scrnarray[], int first, int last);

writword(int mode, char *string, int x,int y);		/* write a word on screen with selected mode */

writerr(char *s);		/* put an error message on bottom of screen */

#endif /* WRITSCRN_H_ */
