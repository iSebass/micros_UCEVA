/*
 * Clase01.c
 *
 * Created: 10/03/2023 02:10:26 p. m.
 * Author : iProf
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "BITS_CONFIG.h"


int main(void)
{
    DDRB = 0xf0;
	
    while (1) 
    {
			if(PINBbits.P0 == 1){
				PORTBbits.B4 = 1;	
			}
			else{
				PORTBbits.B4 = 0;
			}
    }
}

