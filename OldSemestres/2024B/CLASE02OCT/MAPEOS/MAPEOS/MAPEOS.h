/*
 * MAPEOS.h
 *
 * Created: 02/10/2024 06:30:47 p. m.
 *  Author: USER
 */ 


#ifndef MAPEOS_H_
#define MAPEOS_H_


#include <avr/io.h>

typedef unsigned char byte;

typedef struct plantilla_8bits_t{
		byte B0: 1;
		byte B1: 1;
		byte B2: 1;
		byte B3: 1;
		byte B4: 1;
		byte B5: 1;
		byte B6: 1;
		byte B7: 1;
}plantilla_8bits;

#define MACRO_MAPEO(STRUCT, SFR) ( *(volatile STRUCT *)_SFR_MEM_ADDR(SFR) )

//DEFINIMOS LOS PUERTOS
#define PORTDbits  MACRO_MAPEO(plantilla_8bits, PORTD)
#define PORTCbits  MACRO_MAPEO(plantilla_8bits, PORTC)
#define PORTBbits  MACRO_MAPEO(plantilla_8bits, PORTB)
#define PORTEbits  MACRO_MAPEO(plantilla_8bits, PORTE)

//DEFINIMOS LOS DDR
#define DDRDbits  MACRO_MAPEO(plantilla_8bits, DDRD)
#define DDRCbits  MACRO_MAPEO(plantilla_8bits, DDRC)
#define DDRBbits  MACRO_MAPEO(plantilla_8bits, DDRB)
#define DDREbits  MACRO_MAPEO(plantilla_8bits, DDRE)

//DEFINIMOS LOS PIN
#define PINDbits  MACRO_MAPEO(plantilla_8bits, PIND)
#define PINCbits  MACRO_MAPEO(plantilla_8bits, PINC)
#define PINBbits  MACRO_MAPEO(plantilla_8bits, PINB)
#define PINEbits  MACRO_MAPEO(plantilla_8bits, PINE)


#endif /* MAPEOS_H_ */