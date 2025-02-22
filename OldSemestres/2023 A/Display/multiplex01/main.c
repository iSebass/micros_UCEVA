/*
 * multiplex01.c
 *
 * Created: 01/03/2023 02:28:34 p. m.
 * Author : iProf
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DISPLAY7SEG/PERREA.h"

#define DP1_ON  0b1110
#define DP2_ON  0b1101
#define DP3_ON  0b1011
#define DP4_ON  0b0111

int numerito = 5736, residuo;
int u_mil, cent, dec, unidad;
const int tmultiplex=10;

int main(void)
{
	
    decoInit();
	DDRB |= (1<<DDRB0)|(1<<DDRB1)|(1<<DDRB2)|(1<<DDRB3);
    while (1) 
    {
		u_mil   = numerito/1000;
		residuo = numerito % 1000;
		
		cent    = residuo/100;
		residuo = residuo%100;
		
		dec     = residuo/10;
		unidad  = residuo%10;
	
		
		PORTB = DP1_ON;
		decoCC(u_mil);
		_delay_ms(tmultiplex);
		
		PORTB = DP2_ON;
		decoCC(cent);
		_delay_ms(tmultiplex);
		
		PORTB = DP3_ON;
		decoCC(dec);
		_delay_ms(tmultiplex);
		
		PORTB = DP4_ON;
		decoCC(unidad);
		_delay_ms(tmultiplex);
    }
}

