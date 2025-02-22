/*
 * HolaMundo.c
 *
 * Created: 15/02/2023 03:08:48 p. m.
 * Author : iProf
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	// Configuraciones;
	DDRD  = 0b11111111;
	// Ciclo Infinito;
    while (1) 
    {
		PORTD = 0b10101010;
		_delay_ms(1000);
		PORTD = 0b01010101;
		_delay_ms(1000);
    }
}

