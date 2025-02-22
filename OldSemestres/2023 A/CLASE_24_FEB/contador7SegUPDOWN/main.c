#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DECO7SEG/PERREA.h"

#define get_BtnUP()    ( PINB & (1<<PORTB0) )
#define get_BtnDOWN()  ( PINB & (1<<PORTB1) )

int contador=0;
int main(void)
{	
    decoInit();
	
	DDRB &= ~( (1<<0)|(1<<1) );
	
    while (1) 
    {
		decoCC(contador);
		
		if( get_BtnDOWN() != 0){
			while(get_BtnDOWN() != 0);
			contador++;
			if(contador>9) contador=0;
		}
		if(get_BtnUP() == 0){
			while(get_BtnUP() == 0);
			contador--;
			if(contador<0) contador=9;
		}
		
		_delay_ms(20);
    }
}

