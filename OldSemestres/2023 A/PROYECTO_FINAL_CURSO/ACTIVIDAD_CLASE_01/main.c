/*
 * ACTIVIDAD_CLASE_01.c
 *
 * Created: 21/04/2023 04:12:50 p. m.
 * Author : iProf
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART/UART_LIB.h"

#define getstatusBtnA()  (PINB & (1<<0))

char oldtsatusA = 0, currentStatus;

int main(void)
{
	uart_init();
    DDRB &= ~(1<<0);
    while (1) 
    {
		currentStatus = getstatusBtnA() == 0 ? 0:1;
		if( currentStatus != oldtsatusA){
			switch(currentStatus){
				case 0: uart_write_text("LedOff#"); break;
				case 1: uart_write_text("LedOn#");break;
			}
			oldtsatusA = currentStatus;
		}
		
		_delay_ms(100);
		
    }
}

