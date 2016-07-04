/* writescrn.c */
/* uses IBM bios calls in bioscall.asm */

#include <stdio.h>
#include <conio.h>
#include "standard.h"
#include "writscrn.h"


/* movescrn move highlighted block based on key input */
/* returns element not selected */
/* returns -2 for esc, -3 for help (?), -1 on error */
/* assumes existence of globally defined array (in writscrn.h) */
/* of selemnt structures hat been initialized */

movescrn(struct selement scrnarray[], int first, int last)
{
	int c, k, oldk;
	k = first;

	writword(RVC,scrnarray[k].content,scrnarray[k].xpos,scrnarray[k].ypos);
		while (1) {
			oldk = k;
			while (!kbhit()) ;		/* wait for keypress */
			c = getch();
			if (!c) c = getch();	/* delete null chars and get next */
			switch (c) {
			case KUP:
				k = scrnarray[k].nup;
				break;
			case KDOWN:
				k = scrnarray[k].ndown;
				break;
			case KLEFT:
			case BACKSP:
				k = scrnarray[k].nleft;
				break;
			case KRIGHT:
			case TAB:
				k = scrnarray[k].nright;
				break;
			case KHOME:
			case KPGUP:
				k = 0;
				break;
			case KEND:
			case KPGDN:
				k = last;
				break;
			case ESC:
				return(-2);
			case CR:
			case KPLUS:
				return(k);
			case '?':
				return(-3);
			default:
				return(-1);
			}
			writword(BWC,scrnarray[oldk].content,scrnarray[oldk].xpos,
					scrnarray[oldk].ypos);
			writword(RVC,scrnarray[k].content,scrnarray[k].xpos,
					scrnarray[k].ypos);
		}
}



writword(int mode, char *string, int x,int y)		/* write a word on screen with selected mode */
{
	char c;

	csrplot(x,y);
	while((c = *string++) != '\0'){
		switch (mode){
		case (SAMEC):		/* no change in attribute */
			writchr(c,1);
			break;
		case (BWC):			/* normal b/w mode */
			writbw(c,1);
			break;
		case (ULC):			/* underline */
			writul(c,1);
			break;
		case (RVC):			/* reverse video */
			writrv(c,1);
			break;
		case (BRVC):		/* blinking reverse video */
			writblr(c,1);
			break;
		default:
			writchr(c,1);
		}
	}
}



writerr(char *s)		/* put an error message on bottom of screen */
{
	while (kbhit()) getch();	/* clear any stray keypress */
	csrplot(0,SCRNTALL-1);
	fputs(s,stderr);
	fputs(" [Hit a key]",stderr);

	while (!kbhit()) ;			/* wait for keypress */
	getch();
	csrplot(0,SCRNTALL-1);
	writchr(' ',79);
	return(1);
}
