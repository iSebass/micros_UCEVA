#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/LCD_LIB.h"
#include "DS18B20_LIB/DS18B20_LIB.h"
#include "UART/UART_LIB.h"

char mems1[8]={0x28,0x50,0xC5,0xB8,0x00,0x00,0x00,0x4D};
char mems2[8]={0x28,0x30,0xC5,0xB0,0x00,0x00,0x00,0x92};
char mems3[8]={0x28,0x35,0xC5,0xB0,0x00,0x00,0x00,0x79};
char mems4[8]={0x28,0x55,0xC5,0xB0,0x00,0x00,0x00,0xBA};
char mem[8];
	
float temp1, temp2, temp3, temp4;

int main(void)
{
	UART1_Init(9600);
	
	ds18b20_init();
	/*
	ds18b20_read_rom(mem);
	for(uint8_t i=0; i<=7; i++){
		UART1_Transmit_Printf("%X ", mem[i]);
	}
	*/	
    while (1) 
    {
		
		temp1 = ds18b20_get_temp_idx(mems1);
		temp2 = ds18b20_get_temp_idx(mems2);
		temp3 = ds18b20_get_temp_idx(mems3);
		temp4 = ds18b20_get_temp_idx(mems4);
		
		UART1_Transmit_Printf("TEMP1: %5.1f \r\n", temp1);
		UART1_Transmit_Printf("TEMP2: %5.1f \r\n", temp2);
		UART1_Transmit_Printf("TEMP3: %5.1f \r\n", temp3);
		UART1_Transmit_Printf("TEMP4: %5.1f \r\n", temp4);
		UART1_Transmit_Text("______________________________________");
		UART1_Transmit_Text("\r\n");
		
		_delay_ms(500);
    }
}

