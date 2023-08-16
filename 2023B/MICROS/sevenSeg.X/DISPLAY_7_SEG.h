#ifndef DISPLAY_7_SEG_H
#define	DISPLAY_7_SEG_H

#include <xc.h>

#define DIR_segA   TRISBbits.TRISB0
#define DIR_segB   TRISBbits.TRISB1
#define DIR_segC   TRISBbits.TRISB2
#define DIR_segD   TRISBbits.TRISB3
#define DIR_segE   TRISBbits.TRISB4
#define DIR_segF   TRISBbits.TRISB5
#define DIR_segG   TRISBbits.TRISB6

#define segA  LATBbits.LATB0
#define segB  LATBbits.LATB1
#define segC  LATBbits.LATB2
#define segD  LATBbits.LATB3
#define segE  LATBbits.LATB4
#define segF  LATBbits.LATB5
#define segG  LATBbits.LATB6

#define OUT 0
#define IN  1

void display_init(void);
void display_ac(char dig);
void display_cc(char dig);

#endif	/* DISPLAY_7_SEG_H */

