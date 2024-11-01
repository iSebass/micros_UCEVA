/*
 * ONE_Wire.h
 *
 * Created: 25/09/2024 06:56:46 a. m.
 *  Author: USER
 */ 


#ifndef ONE_WIRE_H_
#define ONE_WIRE_H_


//DEFINIR EL PUERTO Y EL PIN DEL SENSOR
#define OW_PORT  PORTB
#define OW_DDR   DDRB
#define OW_PIN   PINB
#define OW_DQ    PINB0

#define PORT_MODE_OUTPUT	OW_DDR  |=   (1<<OW_DQ)
#define PORT_MODE_INPUT		OW_DDR  &=  ~(1<<OW_DQ)

#define SET_BUS_HIGH		OW_PORT |=  (1<<OW_DQ)
#define SET_BUS_LOW			OW_PORT &= ~(1<<OW_DQ)

#define READ_BUS_STATUS		OW_PIN & (1<<OW_DQ)

// Definiciones básicas;
#define FALSE 0
#define TRUE  1

// Declaraciones de funciones;
int OWReset(void);                           // Resetea el bus 1-Wire y detecta presencia de dispositivos;
void OWWriteByte(unsigned char byte_value);  // Envía un byte al bus 1-Wire;
void OWWriteBit(unsigned char bit_value);    // Envía un bit al bus 1-Wire;
unsigned char OWReadByte(void);              // Lee un byte del bus 1-Wire;
unsigned char OWReadBit(void);               // Lee un bit del bus 1-Wire;
int OWFirst(void);                           // Inicia la búsqueda del primer dispositivo en el bus;
int OWNext(void);                            // Continua la búsqueda del siguiente dispositivo en el bus;
int OWSearch(void);                          // Ejecuta el algoritmo de búsqueda 1-Wire;
unsigned char docrc8(unsigned char value);   // Calcula el CRC8 de los datos leídos o enviados;




#endif /* ONE_WIRE_H_ */