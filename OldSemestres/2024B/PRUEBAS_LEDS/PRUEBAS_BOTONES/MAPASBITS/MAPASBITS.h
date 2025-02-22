/*
 * MAPASBITS.h
 *
 * Created: 02/10/2024 04:26:49 p. m.
 *  Author: USER
 */ 


#ifndef MAPASBITS_H_
#define MAPASBITS_H_


#include "MAPASBITS.h"

typedef unsigned char byte;

typedef struct plantilla_8bits_t{
	union{
		byte B0: 1;
		byte B1: 1;
		byte B2: 1;
		byte B3: 1;
		byte B4: 1;
		byte B5: 1;
		byte B6: 1;
		byte B7: 1;	
	};	
	
	union{
		byte NIBBLEL: 4;
		byte NIBBLEH: 4;
	};
	
}plantilla_8bits;

typedef struct plantilla_4bits_t{
	union{
		byte B0: 1;
		byte B1: 1;
		byte B2: 1;
		byte B3: 1;
		byte :  4;
	};
	
	union{
		byte NIBBLEL: 4;
		byte : 4;
	};
	
}plantilla_4bits;


#define MACRO_MAPEO(STRUCT, SFR) ( *(volatile STRUCT *)_SFR_MEM_ADDR(SFR) )

//DEFINICION DE PUERTOS
#define PORTDbits MACRO_MAPEO(plantilla_8bits, PORTD)
#define PORTBbits MACRO_MAPEO(plantilla_8bits, PORTB)
#define PORTCbits MACRO_MAPEO(plantilla_8bits, PORTC)
#define PORTEbits MACRO_MAPEO(plantilla_4bits, PORTE)


//DEFINICION DE DDR
#define DDRDbits MACRO_MAPEO(plantilla_8bits, DDRD)
#define DDRBbits MACRO_MAPEO(plantilla_8bits, DDRB)
#define DDRCbits MACRO_MAPEO(plantilla_8bits, DDRC)
#define DDREbits MACRO_MAPEO(plantilla_4bits, DDRE)

//DEFINICION DE PIN
#define PINDbits MACRO_MAPEO(plantilla_8bits, PIND)
#define PINBbits MACRO_MAPEO(plantilla_8bits, PINB)
#define PINCbits MACRO_MAPEO(plantilla_8bits, PINC)
#define PINEbits MACRO_MAPEO(plantilla_4bits, PINE)


#endif /* MAPASBITS_H_ */