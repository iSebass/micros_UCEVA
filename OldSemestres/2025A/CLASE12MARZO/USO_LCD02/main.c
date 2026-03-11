#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

//AGREGAMOS LIBRERIAS PROPIAS
#include "LCD/LCD_LIB.h"
#include "KEYPAD/KEYPAD_LIB.h"

char customMsg[] = {
	0b00100,
	0b00100,
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b00000
};

char customPacMan[] = {
	0b00110,
	0b01101,
	0b11111,
	0b11111,
	0b11100,
	0b11111,
	0b01111,
	0b00111
};


char tecla;

int main(void)
{
	KeyPad_Init();
	lcd_init();
	
	lcd_disable_blink();
	lcd_disable_cursor();
	
	//lcd_custom_char(0, customMsg);
	//lcd_custom_char(1, customPacMan);
	while (1)
	{
		/*
		lcd_set_cursor(1,5);
		lcd_write(0);
		lcd_set_cursor(2,3);
		lcd_write(1);	
		lcd_set_cursor(3,1);
		lcd_write(' ');
		_delay_ms(2000);
		*/
		tecla = KeyPad_KeyClick();
		
		lcd_set_cursor(1,1);
		lcd_printf("tecla: %c", tecla);
		
		_delay_ms(50);
		
		
	}
}

