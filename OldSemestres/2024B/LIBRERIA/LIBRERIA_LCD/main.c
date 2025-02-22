/*
 * LIBRERIA_LCD.c
 *
 * Created: 11/09/2024 06:25:35 p. m.
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "LCD/LCD_LIB.h"
#include "ADC/ADC_LIB.h"

float temp=49.5;
int conver=0;

char customChar[] = {
	0b01010,
	0b01010,
	0b00000,
	0b10101,
	0b10001,
	0b10001,
	0b11111,
	0b00000
};


int main(void)
{
   
	
	lcd_init();
	
	lcd_disable_blink();
	lcd_disable_cursor();
	
	ADC_init();
	
	
	
    while (1) 
    {
		conver = ADC_read(A6);
		lcd_set_cursor(1,1);
		lcd_printf("Conver: %04d", conver);
		_delay_ms(50);
    }
}

