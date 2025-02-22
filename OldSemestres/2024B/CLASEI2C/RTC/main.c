#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "TWI/TWI_LIB.h"
#include "TWI_LCD/TWI_LCD_LIB.h"
#include "DS1307/DS1307_LIB.h"

#define DIR_DS1307 0xD0

int main(void)
{
	TWI_Init();
	
	i2c_lcd_init();
	i2c_lcd_puts("Hola Amigos!");
	
	DS1307_Set_Seg_Value(0x58);
	DS1307_Set_Min_Value(0x59);
	//DS1307_Set_Hour24_Value(0x23);
	DS1307_Set_Hour12_Value(0x11, _AM);
	DS1307_Set_Week_Day_Value(0x03);
	DS1307_Set_Date_Day_Value(0x06);
	DS1307_Set_Month_Value(0x11);
	DS1307_Set_Year_Value(0x24);


	while (1)
	{
		

		
		_delay_ms(10);
		
	}
}

