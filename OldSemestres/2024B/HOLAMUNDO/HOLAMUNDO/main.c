/*
 * HOLAMUNDO.c
 *
 * Created: 14/08/2024 08:48:44 p. m.
 * Author : USER
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

char contador=1;

int main(void)
{
    /*CONFIGRUAR EL PUERTO DONDE SE VA A CONECTAR EL LED
		1  Para salida;
		0  Para entrada;
	*/
	DDRB = 0xFF;
    while (1) 
    {
		PORTB = 5<<contador;
		_delay_ms(100);
		contador++;
		if(contador>8)
			contador=0;
		
    }
}

