#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART/UART_LIB.h"
#include "ONE_WIRE/ONE_Wire.h"


int ndevices;


int main(void){
    
	UART1_Init(9600);
	
	ndevices=OWSearch();
	
	UART1_Transmit_Text("ROMS ENCONTRADOS: \r\n");
	
	for(uint8_t j=0; j<MAX_DEVICES; j++){
	
		for(uint8_t i=0; i<=7; i++){
			UART1_Transmit_Printf("%02X ", ROM_NO[j][i]);
		}
		UART1_Transmit_Text("\r\n");
	}
	
    while (1) 
    {
    }
}

