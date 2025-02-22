#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DISPLAY7SEG/PERREA.h"

char numero = 0;

int main(void)
{
    decoInit();
	
    while (1) 
    {
		decoCC(numero);
		numero += 1;
		_delay_ms(500);
		if(numero>9)
			numero = 0;
    }
}

