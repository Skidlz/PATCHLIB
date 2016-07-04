/* chain.c - screen file storage and display */
/* uses linked lists with each node defined as a struct strchain */

#define TURBOC 1 /* this line is only needed for Turbo C */
#ifdef TURBOC
	#include <alloc.h> 	/* Turbo C library file name */
#else
	#include <malloc.c> /* Microsoft C library file name */
#endif

#include <stdio.h>
#include "standard.h"
#include "chain.h"


struct strchain *inpchain(char *file, int maxlen)		/* read file into chain */
{
	FILE *stream;
	struct strchain *p, *root, *oldp;
	char *strbuf;

	strbuf = (char *) malloc(maxlen + 1);	/* set aside input buffer */

	stream = fopen(file, "r");

	p = root = chainalloc();
	while (fgets(strbuf, maxlen, stream) != NULL) {
		p->line = strsave(strbuf);
		p->next = chainalloc();
		oldp = p;
		p = p->next;
	}
	oldp->next = NULL;		/* NULL marks chain end */
	free(p);				/* free unused end node */
	fclose(stream);
	free(strbuf);			/* free buff for other use */
	return(root);
}


dechain(struct strchain *p)	/* free all memory reserved for chain pointed to by p */
{
	struct strchain *q;
	while (p != NULL) {
		q = p->next;
		free(p->line);
		free(p);
		p = q;
	}
}


dispchain(struct strchain *p)			/* write all lines of list to stdout */
{/* standard console output version */
	while (p != NULL) {
		fputs(p->line, stdout);
		p = p->next;
	}
}



struct strchain *chainalloc()	/* save memory space for next link */
{
	return((struct strchain *) malloc(sizeof(struct strchain)));
}



char *strsave(char *s)	/* save string a somewhere, K&R p 103 */
{
	char *p;
	if ((p = (char *) malloc(strlen(s) + 1)) != NULL)
		strcpy(p,s);
	return(p);
}
