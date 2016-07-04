/* chain.h header file for chain.c */

#ifndef CHAIN_H_
#define CHAIN_H_

struct strchain {
	char *line;
	struct strchain *next;
};

struct strchain *inpchain(), *chain(), *chainalloc();
char *strsave();

dechain(struct strchain *p);	/* free all memory reserved for chain pointed to by p */
dispchain(struct strchain *p);	/* write all lines of list to stdout */

#endif /* CHAIN_H_ */
