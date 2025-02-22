#ifndef TWI_LIB_H_
#define TWI_LIB_H_

#include <stdint.h>
#include <avr/io.h>

#define F_CPU 16000000UL
#define SCL_CLOCK 100000UL

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8_t data);
void TWI_Repeat_Start(void);
uint8_t TWI_ReadAck(void);
uint8_t TWI_ReadNack(void);



#endif /* TWI_LIB_H_ */