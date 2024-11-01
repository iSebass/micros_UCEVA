#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/LCD_LIB.h"
#include "ADC/ADC_LIB.h"
#include "DHT22/DHT22_LIB.h"

float temp, RH;
char statusDHT22;


int main(void){
    
	lcd_init();
	
    while(1){
		
		statusDHT22 = DHT22_ReadData(&temp, &RH);
		switch(statusDHT22){
			
			case SUCESS: lcd_set_cursor(1,1);
						 lcd_printf("temp: %5.1f", temp);
						 lcd_set_cursor(2,1);
						 lcd_printf("hum: %5.1f", RH);
						 break;
		}
		_delay_ms(500);
    }
}

