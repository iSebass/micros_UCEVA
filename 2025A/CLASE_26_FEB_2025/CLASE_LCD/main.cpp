/*
 * CLASE_LCD.cpp
 *
 * Created: 26/02/2025 08:25:46 p. m.
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "LCD/LCD_LIB.h"


int contador=0, contador2=99;

int main(void)
{
    lcd_init();
	
	lcd_set_cursor(2,3);
	lcd_printf("Oliiii");
	
    while (1) 
    {
    }
}

