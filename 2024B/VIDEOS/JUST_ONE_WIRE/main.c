#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ONE_WIRE/ONE_Wire.h"
#include "UART/UART_LIB.h"

void PrintROM(unsigned char rom[8]) {
	UART1_Transmit_Printf("ROM: ");
	for (int i = 0; i < 8; i++) {
		UART1_Transmit_Printf("%02X ", rom[i]);  // Imprimir en formato hexadecimal.
	}
	UART1_Transmit_Printf("\r\n");
}

int main(void) {
	UART1_Init(9600);  // Inicializar UART para salida serial

	// Mensaje inicial
	UART1_Transmit_Printf("Buscando dispositivos en el bus 1-Wire...\r\n");

	

	// Ciclo para buscar todos los dispositivos en el bus 1-Wire
	while (OWSearch()) {
		// Imprimir la ROM del dispositivo encontrado
		PrintROM(all_ROMs[device_count - 1]);  // Se imprime la última ROM encontrada
	}

	// Finalización de la búsqueda
	UART1_Transmit_Printf("Búsqueda finalizada.\r\n");

	// Imprimir el número total de dispositivos encontrados
	UART1_Transmit_Printf("Se encontraron %d dispositivos.\r\n", device_count);

	while (1) {
		// Espera indefinida o realizar otras operaciones
		_delay_ms(1000);
	}

	return 0;
}
