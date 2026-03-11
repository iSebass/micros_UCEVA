#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

/*
	DDRX  -> CONFIGURAR
	PORTX -> ESCRIBIR
	PINX  -> LEER
*/
int main(void)
{
    //CONFIGURACIONES
	DDRA = 0xFF;  // HEXAD
	//DDRA = 255;   // DECIMAL
	//DDRA = 0377;  // OCTAL
	//DDRA = 0b11111111;  // BINARIO
	
	
	
	//LOOP
    while(1){
		PORTA = 0b10101010;  //0xAA;
		_delay_ms(500);
		PORTA = 0b01010101;  //0xAA;
		_delay_ms(500);
    }
}

