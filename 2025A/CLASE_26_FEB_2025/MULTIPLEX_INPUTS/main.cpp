#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SEVEN_SEG/SEVEN_SEG_LIB.h"


//   5268

#define DISPLAY_CONTROL PORTA
#define DISPLAY_DDR     DDRA

#define SET_DISPLAY_1()  DISPLAY_CONTROL =  0b1000
#define SET_DISPLAY_2()  DISPLAY_CONTROL =  0b0100
#define SET_DISPLAY_3()  DISPLAY_CONTROL =  0b0010
#define SET_DISPLAY_4()  DISPLAY_CONTROL =  0b0001

const int te=10;

int contador=5268, contador_seg=0, unidad, decena, centena, miles, aux;


void MultiplexClase(void){
	miles = contador / 1000;
	aux = contador % 1000;
	
	centena = aux / 100;
	aux = aux % 100;
	
	decena = aux / 10;
	unidad = aux % 10;
	
	SET_DISPLAY_1();
	DisplaySevenSegCA(unidad);
	_delay_ms(te);
	
	SET_DISPLAY_2();
	DisplaySevenSegCA(decena);
	_delay_ms(te);
	
	SET_DISPLAY_3();
	DisplaySevenSegCA(centena);
	_delay_ms(te);
	
	SET_DISPLAY_4();
	DisplaySevenSegCA(miles);
	_delay_ms(te);
}

#define getBTN()  (PINB & (1<<0) ) 

int main(void){
	DisplaySevengSegInit();
	DISPLAY_DDR = 0x0F;
	DISPLAY_CONTROL = 0xF;
	
	DDRB &= ~(1<<0);
	
	while (1)
	{
		if( getBTN() == 0 ){
			while( getBTN() == 0 ){
				MultiplexClase();
			}
			contador++;
		}
		MultiplexClase();

		
		
	}
}

