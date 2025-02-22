/*
 * BITS_CONFIG.h
 *
 * Created: 10/03/2023 02:11:55 p. m.
 *  Author: iProf
 */ 


#ifndef BITS_CONFIG_H_
#define BITS_CONFIG_H_

#include <avr/io.h>

typedef union PBbits_t{
	struct{
			unsigned char B0     :1;
			unsigned char B1     :1;
			unsigned char B2     :1;
			unsigned char B3     :1;
			unsigned char B4     :1;
			unsigned char B5     :1;
			unsigned char B6     :1;
			unsigned char B7     :1;	
	};
	struct{
		unsigned char NibbleL    :4;
		unsigned char NibbleH    :4;
	};
}volatile *PBbits;

typedef union DDBbits_t{
	struct{
		unsigned char D0     :1;
		unsigned char D1     :1;
		unsigned char D2     :1;
		unsigned char D3     :1;
		unsigned char D4     :1;
		unsigned char D5     :1;
		unsigned char D6     :1;
		unsigned char D7     :1;
	};
	
}volatile *DDBbits;

typedef union PINNBbits_t{
	struct{
		unsigned char P0     :1;
		unsigned char P1     :1;
		unsigned char P2     :1;
		unsigned char P3     :1;
		unsigned char P4     :1;
		unsigned char P5     :1;
		unsigned char P6     :1;
		unsigned char P7     :1;
	};
	
}volatile *PINNBbits;

#define PORTBbits  (*(PBbits)_SFR_MEM_ADDR(PORTB))
#define DDRBbits   (*(DDBbits)_SFR_MEM_ADDR(DDRB))
#define PINBbits   (*(PINNBbits)_SFR_MEM_ADDR(PINB))

#endif 