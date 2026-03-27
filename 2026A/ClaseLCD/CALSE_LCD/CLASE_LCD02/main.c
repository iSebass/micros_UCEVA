#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LIBS/LCD_LIB.h"

//MAPA DE CONEXIONES
#define BTNUP_PIN     0
#define BTNDOWN_PIN   1
#define BTNSELECT_PIN 2
#define LED_PIN       3
#define RELAY_PIN     4
#define MA1_PIN       2
#define MA2_PIN       3

//ACCIONES DEL MOTOR
void MotoroDerecha();
void MotorIzquierda();
void MotorParar();

//ACCIONES DEL LED
void LedOn();
void LedOff();

//ACCIONES DEL RELAY
void RelayOn();
void RelayOff();


int main(void)
{
	//CONFIGURAMOS LOS PINES DEL MOTOR DE SALIDA
	GPIO_PIN_MODE_PORTA(MA1_PIN, OUTPUT);
	GPIO_PIN_MODE_PORTA(MA2_PIN, OUTPUT);
	
	//CONFIGURAMOS EL LED
	GPIO_PIN_MODE_PORTB(LED_PIN, OUTPUT);
	
	//CONFIGURAMOS EL RELAY
	GPIO_PIN_MODE_PORTB(RELAY_PIN, OUTPUT);
	
	//CONFIGURAMOS LOS BOTONES COMO ENTRADA
	GPIO_PIN_MODE_PORTB(BTNUP_PIN, INPUT);
	GPIO_PIN_MODE_PORTB(BTNDOWN_PIN, INPUT);
	GPIO_PIN_MODE_PORTB(BTNSELECT_PIN, INPUT);
	
	
	
    lcd_init();
	
	
	
    while (1) 
    {
		RelayOn();
		MotorIzquierda();
		LedOn();
		_delay_ms(500);
		RelayOff();
		LedOff();
		MotoroDerecha();
		_delay_ms(500);
    }
}

void MotoroDerecha(){
	GPIO_WRITE_PORTA(MA1_PIN, HIGH);
	GPIO_WRITE_PORTA(MA2_PIN, LOW);
}
void MotorIzquierda(){
	GPIO_WRITE_PORTA(MA1_PIN, LOW);
	GPIO_WRITE_PORTA(MA2_PIN, HIGH);
}
void MotorParar(){
	GPIO_WRITE_PORTA(MA1_PIN, LOW);
	GPIO_WRITE_PORTA(MA2_PIN, LOW);
}

void LedOn(){
	GPIO_WRITE_PORTB(LED_PIN, HIGH);
}
void LedOff(){
	GPIO_WRITE_PORTB(LED_PIN, LOW);
}


void RelayOn(){
	GPIO_WRITE_PORTB(RELAY_PIN, HIGH);
}
void RelayOff(){
	GPIO_WRITE_PORTB(RELAY_PIN, LOW);
}
