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

//DECLARAMOS LOS METODOS DEL MENU
void MenuPpal();
void MenuLed();
void MenuMotor();
void MenuRelay();

enum{
	menu_ppl,
	menu_led,
	menu_motor,
	menu_relay
};


//FUNCIONES DEL MENU
char menuPPL[3][6]={"Led  ","Motor","Relay"};
char menuLED[3][5]={"on  ","Off ","Back"};
char menuMotor[4][6]={"T.Der","T.Izq","Stop ","Back "};
char menuRelay[3][5]={"on  ","Off ","Back"};
	
enum{
	led,
	motor,
	relay,
	onled,
	offled,
	backled,
	tder,
	tiz,
	stop,
	backmotor,
	onrelay,
	offrelay,
	backrelay
};

int op=led, op_menu=menu_ppl;

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
	lcd_disable_cursor();
	lcd_disable_blink();
	
	
	
	
    while (1) 
    {
		switch(op_menu){
			case menu_ppl: MenuPpal(); break;
			case menu_led: MenuLed(); break;
			case menu_motor: MenuMotor(); break;
			case menu_relay: MenuRelay(); break;
		}
		
    }
}

void MenuPpal(){

	lcd_set_cursor(1,1);
	lcd_puts("    MENU PPAL    ");
	lcd_set_cursor(2,1);
	lcd_puts( menuPPL[op] );
	if( GPIO_READ_PORTB(BTNUP_PIN) == HIGH ){
		while(GPIO_READ_PORTB(BTNUP_PIN) == HIGH );
		op++;
		if(op>relay) op=led;
		
	}
	if( GPIO_READ_PORTB(BTNDOWN_PIN) == HIGH  ){
		while(GPIO_READ_PORTB(BTNDOWN_PIN) == HIGH );
		op--;
		if(op<led) op=relay;
		
	}
	if( GPIO_READ_PORTB(BTNSELECT_PIN) ){
		while(GPIO_READ_PORTB(BTNSELECT_PIN) == HIGH );
		switch(op){
			case led:   lcd_clear();
						op=onled; 
						op_menu=menu_led;
						break;
			case motor: lcd_clear();
						op=tder;
						op_menu=menu_motor;
						break;
			case relay: lcd_clear();
						op=onrelay;
						op_menu=menu_relay;
						break;
		}
		
	}
}

void MenuLed(){
	lcd_set_cursor(1,1);
	lcd_puts("    MENU LED    ");
	lcd_set_cursor(2,1);
	lcd_puts( menuLED[op-(relay+1)] );
	
	if( GPIO_READ_PORTB(BTNUP_PIN) == HIGH ){
		while(GPIO_READ_PORTB(BTNUP_PIN) == HIGH );
		op++;
		if(op>backled) op=onled;
		
	}
	if( GPIO_READ_PORTB(BTNDOWN_PIN) == HIGH  ){
		while(GPIO_READ_PORTB(BTNDOWN_PIN) == HIGH );
		op--;
		if(op<onled) op=backled;
		
	}
	if( GPIO_READ_PORTB(BTNSELECT_PIN) ){
		while(GPIO_READ_PORTB(BTNSELECT_PIN) == HIGH );
		switch(op){
			case onled:   LedOn(); break;
			case offled:  LedOff();break;
			case backled: lcd_clear();
						  op=led;
						  op_menu=menu_ppl;
			              break;
		}
	}
	
}
void MenuMotor(){
	lcd_set_cursor(1,1);
	lcd_puts("    MENU MOTOR    ");
}
void MenuRelay(){
	lcd_set_cursor(1,1);
	lcd_puts("    MENU RELAY    ");
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
