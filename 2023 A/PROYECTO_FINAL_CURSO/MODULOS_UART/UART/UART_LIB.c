#include "UART_LIB.h"

void uart_init(){
	uint16_t ubrr = F_CPU / 16 / BAUD_RATE - 1;

	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;

	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}


void uart_write_chr(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));

	UDR0 = data;
}


uint8_t uart_read() {
	while (!(UCSR0A & (1 << RXC0)));

	return UDR0;
}

void uart_write_text(char *text){
	while(*text){
		uart_write_chr(*text);
		text++;
	}
}