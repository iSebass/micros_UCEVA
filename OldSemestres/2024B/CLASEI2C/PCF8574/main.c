#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "TWI/TWI_LIB.h"
#include "TWI_LCD/TWI_LCD_LIB.h"
#include "EEPROM_LC/EEPROM_24LC256.h"

#define DIR_MEM 0x50

int data;

int main(void)
{
    TWI_Init();
	
	i2c_lcd_init();
	i2c_lcd_puts("Hola Amigos!");
	
	
	
	DDRD  = 0xFF;
	PORTD = EEPROM_24LC256_Rd(105);
	
    while (1) 
    {
		
		
		
		_delay_ms(10);
		
    }
}

