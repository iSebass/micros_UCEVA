/*
 * configuracionManual.c
 *
 * Created: 22/03/2023 01:38:13 p. m.
 * Author : iProf
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCD/LCD_LIB.h"
#include "ADC/ADC_LIB.h"

int conver;

int main(void)
{
	ADC_Init();
	lcd_init();
	lcd_disable_blink();
	lcd_disable_cursor();
	lcd_puts("Hola");
    // Confuguramos los registros para el modulo ADC
	
    while (1) 
    {
		conver = ADC_Read(0);
		lcd_set_cursor(1,1);
		lcd_printf("Conver: %4d", conver);
		
		conver = ADC_Read(1);
		lcd_set_cursor(2,1);
		lcd_printf("LM35: %4d", conver);
		
		_delay_ms(20);
    }
}

