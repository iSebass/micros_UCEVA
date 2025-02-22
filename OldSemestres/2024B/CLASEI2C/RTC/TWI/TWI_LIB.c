#include "TWI_LIB.h"

void TWI_Init(void){

	// Configuración de la velocidad de reloj TWI;
	
	// TMSR0 = 0 -> PREESCALER = 1
	// TMSR0 = 1 -> PREESCALER = 4
	// TMSR0 = 2 -> PREESCALER = 16
	// TMSR0 = 3 -> PREESCALER = 64
	TWSR = 0; 
	
	/*
		CONFIGURAMOS EL REGSITRO TWBRn PARA GARANTIZAR UNA VELOCIDAD DE 
        LA MACRO  SCL_CLOCK, TENER EN CUENTA QUE DEPENDIENDO EL VALOR DEL
        CALCULO SE DEBE AGREGAR UN PREESCALDOR. EN ESTE CASO PRE = 1

	               Fosc
		Fscl = ___________________
				16+2(TWBRn)*(PRE)	

				 
				|   Fosc      |   
		TWBRn = | ______ - 16 | / 2
				|  Fscl		  |	
                
	*/
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2; 
	
	// Habilitación del TWI;
	TWCR = (1<<TWEN);           
}

void TWI_Start(void){
	TWCR = (1<<TWINT)|	(1<<TWSTA)|(1<<TWEN); //enviamos la instruccion de start condition ofrecida por el fabricante
	while (!(TWCR &(1<<TWINT))); // Esperamos a que se genere la señal de start
}

void TWI_Stop(void){

	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}

void TWI_Write(uint8_t data){
	// Escritura de datos en el bus TWI
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	// Esperar a que se complete la operación
	while (!(TWCR & (1<<TWINT)));
}

uint8_t TWI_ReadAck(void){
	// Lectura de datos del bus TWI con ACK
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	
	// Esperar a que se complete la operación
	while (!(TWCR & (1<<TWINT)));
	
	// Retornar el valor leido
	return TWDR;
}

uint8_t TWI_ReadNack(void){
	// Lectura de datos del bus TWI sin ACK
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	// Esperar a que se complete la operación
	while (!(TWCR & (1<<TWINT)));
	
	// Retornar el valor leído
	return TWDR;
}

void TWI_Repeat_Start(void){
		TWI_Stop();
		TWI_Start();
}