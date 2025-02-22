#ifndef UART_LIB_H_
#define UART_LIB_H_


#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL


#define BAUD_RATE 9600

void uart_init();
void uart_write_chr(uint8_t data);
uint8_t uart_read();
void uart_write_text(char *text);

#endif /* UART_LIB_H_ */