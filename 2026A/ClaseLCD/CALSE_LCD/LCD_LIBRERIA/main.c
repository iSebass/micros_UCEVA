#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "LCD/LCD_LIB.h"

char Javier[] = {
	0b00100,
	0b00100,
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b00000
};

char char02[] = {
	0b10001,
	0b01110,
	0b00100,
	0b00100,
	0b01110,
	0b10001,
	0b10001,
	0b00000
};


int contador=25, val=56;

int main(void)
{
    lcd_init();
	
	//MAPEANDO EL EL CARACTER EN LA MEMORIA 0, 1
	lcd_custom_char(0, Javier);
	lcd_custom_char(1, char02);
	
	lcd_set_cursor(1,7); lcd_puts("Javier ");
	lcd_write(0);
	lcd_write(1);
	
    while (1) 
    {
    }
}

