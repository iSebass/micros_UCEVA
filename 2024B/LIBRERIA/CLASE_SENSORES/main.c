/*
 * CLASE_SENSORES.c
 *
 * Created: 18/09/2024 06:26:41 p. m.
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "ADC/ADC_LIB.h"
#include "LCD/LCD_LIB.h"
#include "HCSR04/HCSR04_LIB.h"
#include "DHT22/DHT22_LIB.h"

float temp=10.3, mcp, pot;
int dist;
int conver;
char strLCD[20]= " ";

float dhtHum, dhtTemp;

int main(void)
{
    lcd_init();
	lcd_disable_blink();
	lcd_disable_cursor();
	
	ADC_init();
	
	HCSR04_init();
	
	
    while (1) 
    {	
		switch( DHT22_ReadData(&dhtTemp, &dhtHum)  ){
			case SUCESS: sprintf(strLCD,"Hum: %4.1f", dhtHum);
						 lcd_out(4,11,strLCD);
						 sprintf(strLCD,"T: %4.1f", dhtTemp);
						 lcd_out(1,13,strLCD);
						 break;
		}
		
		dist = HCSR04_readDistance();
		sprintf(strLCD,"Dist: %3d", dist);
		lcd_out(4,1,strLCD);
		
		conver = ADC_read(0);
		temp = ADC_Map(conver,0,306.9,0,150.0);
		
		
		conver = ADC_read(1);
		mcp = (165.0/337.59)*conver -40.0 - 10.0;
		
		conver = ADC_read(2);
		pot = (5.0/1023.0)*conver;
		
		sprintf(strLCD,"Temp: %5.1f", temp);
		lcd_out(1,1,strLCD);
		
		lcd_set_cursor(2,1);
		lcd_printf("mcp: %5.1f", mcp);
		lcd_set_cursor(3,1);
		lcd_printf("volt: %5.1f", pot);
		
		
    }
}

