#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /*
		1) CONFIGURAR EL PUERTO A COMO SALIDA AL MENOS EN EL PIN A0
		2) MANIPULAR EL LED PARA QUE ENCIENDA
		3) MANIPUAR EL LED PARA QUE APAGUE
	*/
	//CONFIGURAR
	DDRA  = 0b00000001;
	
    while(1){
		PORTA = 0b00000001;
		_delay_ms(500);
		PORTA = 0b00000000;
		_delay_ms(500);
	
    }
}

