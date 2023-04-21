/*
 * MascarasdeBits.c
 *
 * Created: 22/02/2023 02:18:12 p. m.
 * Author : iProf
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0xFF;
	PORTB = 0x00;
	
	//Clear PINB5, PINB4
	//PORTB &=   ~ ( (1<<3) | (1<<0) );
	
	PORTB |=    ( (1<<5) | (1<<6) );
	 
    while (1) 
    {
    }
}

