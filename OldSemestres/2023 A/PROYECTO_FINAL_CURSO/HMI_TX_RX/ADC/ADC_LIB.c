#include "ADC_LIB.h"



void ADC_Init(void){
	//Justificacion a la derecha ADLAR EN 0;
	ADMUX &=  ~(1<<ADLAR);
	//DESHABILITAR AUTODISPARO;
	ADCSRA &= ~(1<<ADATE);
	//SELECCIONAR V DE REF;
	ADMUX &= ~(1<<REFS1);
	ADMUX |=  (1<<REFS0);
	//DESHABILITAR CONVERSOR;
	ADCSRA &= ~(1<<ADEN);
	//AJUSTAR PRE ESCALADOR;
	//16M/128 = 125KHz;
	ADCSRA = ADCSRA & 0xF8;
	ADCSRA = ADCSRA | _PRE_;
	//CONFIGURAR BITS COMO DIG;
	DIDR0 = 0xFF;
}
uint16_t ADC_Read(uint8_t ch){
	//SELECCIONAR CANAR A COMVERTIR;
	ADMUX = (ADMUX & 0xF0);
	ADMUX |= ch;
	//HABILITAR ADC
	ADCSRA |= (1<<ADEN)|(1<<ADSC);
	while( (ADCSRA & (1<<ADSC)) !=0 );
	//Deshabilitar conversor;
	ADCSRA &= ~(1<<ADEN);
	//Leer conversor;
	return ADC;
}
float ADC_Map(int conv1, float conv_min, float conv_max, float sal_min, float sal_max){
	
	float m;
	
	m = (sal_max-sal_min)/(conv_max-conv_min);
	
	return (m*conv1-m*conv_min+sal_min);
	
}