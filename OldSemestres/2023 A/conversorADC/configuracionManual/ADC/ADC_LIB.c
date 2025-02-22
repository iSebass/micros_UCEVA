#include "ADC_LIB.h"

void ADC_Init(){
	// Justificamos el resultado a la derecha;
	ADMUX &= ~(1<<ADLAR);
	
	// Configuramos la VREF de la conversion AVCC;
	ADMUX |=  (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	// Configuramos un preescaler de 128;
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	// Desactivamos el Autodisparo;
	ADCSRA &=~(1<<ADATE);
	
	//Activar modulo ADC;
	ADCSRA |= (1<<ADEN);
}
int ADC_Read(char ch){
	
	DIDR0 |= (1<<ch);
	
	//Seleccionamos el canal donde vamos a convertir;
	ADMUX  = ADMUX & 0xF0;
	ADMUX |= ch & 0b111;
	
	//comenzar la conversion;
	ADCSRA |= (1<<ADSC);
	
	//esperar a que termine la conversion;
	while( (ADCSRA&(1<<ADSC)) != 0 );
	
	DIDR0 &= ~(1<<ch);
	
	return ADC;
}

float mapeo(int conv, float x1, float y1, float x2, float y2){
	
	float m;
	
	m = (y2-y1)/(x2-x1);
	
	return (m*conv-m*x1+y1);
	
}
