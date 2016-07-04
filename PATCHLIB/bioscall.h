/*
 * bioscall.h
 *
 *  Created on: Jun 25, 2016
 *      Author: Zack
 */

#ifndef BIOSCALL_H_
#define BIOSCALL_H_

extern void clearsc();
extern void home();
extern void csrplot(int, int);
extern void writchr(int, int);
extern void writbw(int, int);
extern void writul(int, int);
extern void writrv(int, int);
extern void writblr(int, int);

#endif /* BIOSCALL_H_ */
