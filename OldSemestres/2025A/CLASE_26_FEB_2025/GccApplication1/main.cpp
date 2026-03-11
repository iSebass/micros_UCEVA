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

int main(void){
    DisplaySevengSegInit();
	DISPLAY_DDR = 0x0F;
	DISPLAY_CONTROL = 0xF;
	
    while (1) 
    {
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
		
		contador_seg++;
		if(contador_seg == 25){
			contador_seg=0;
			contador++;
			if( contador > 9999) contador=0;
		}
		
    }
}

