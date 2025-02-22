#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "UART/UART_LIB.h"
#include "DS18B20_LIB/DS18B20_LIB.h"


float temp;
char memos1[8], memos2[8], memos3[8];

int main(void){
    UART1_Init(9600);
	
	ds18b20_init();
	ds18b20_search_rom();
	
	getRooms(memos1,0);
	getRooms(memos2,1);
	getRooms(memos3,1);
	
	memos3[1]= 0x44;
	memos3[7]= 0xCA;


	UART1_Transmit_Printf("%X %X %X %X %X %X %X %X \r\n", memos1[7],memos1[6],memos1[5],memos1[4],memos1[3],memos1[2],memos1[1],memos1[0]);
	UART1_Transmit_Printf("%X %X %X %X %X %X %X %X \r\n", memos2[7],memos2[6],memos2[5],memos2[4],memos2[3],memos2[2],memos2[1],memos2[0]);
	UART1_Transmit_Printf("%X %X %X %X %X %X %X %X \r\n", memos3[7],memos3[6],memos3[5],memos3[4],memos3[3],memos3[2],memos3[1],memos3[0]);
	
	UART1_Transmit_Printf("__________________________________________________________ ");
	UART1_Transmit_Printf("\r\n");
	_delay_ms(2000);
	
    while(1){
		
		temp = ds18b20_get_temp_idx(memos1);
		UART1_Transmit_Printf("temp: %5.1f \r\n", temp);
		
		
		temp = ds18b20_get_temp_idx(memos2);
		UART1_Transmit_Printf("temp: %5.1f \r\n", temp);
		
		temp = ds18b20_get_temp_idx(memos3);
		UART1_Transmit_Printf("temp: %5.1f \r\n", temp);
		
		UART1_Transmit_Printf("__________________________________________________________ ");
		UART1_Transmit_Printf("\r\n");
		_delay_ms(2000);
    }
}

