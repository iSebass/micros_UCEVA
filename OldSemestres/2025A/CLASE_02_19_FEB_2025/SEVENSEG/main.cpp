#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SEVENSEG_LIB/SEVENSEG_LIB.h"

#define getBTN_UP()   (PIND & (1<<0) )
#define getBTN_DOWN() (PIND & (1<<2) )


				 
signed char contador=0;

int main(void)
{
	DDRD &= ~( (1<<PIND0) | (1<<PIND2) );

	DisplaySevengSegInit();

    while(1){
		DisplaySevenSegCA(contador);
		if( getBTN_UP() != 0 ){
			while( getBTN_UP() != 0 );
			contador++;
			contador = contador > 9 ? 0 : contador;
		}
		if( getBTN_DOWN() != 0 ){
			while( getBTN_DOWN() != 0 );
			contador--;
			contador = contador < 0 ? 9 : contador;
		}
		
		
		_delay_ms(10);
    }
}

