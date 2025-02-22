#include "DS18B20_LIB.h"
#include <util/delay.h>

void ds18b20_init(void) {
	DS18B20_DDR |= (1 << DS18B20_DQ); // Configura el pin como salida;
	DS18B20_PORT |= (1 << DS18B20_DQ); // Establece el pin en alto;
}

void ds18b20_reset(void) {
	DS18B20_DDR |= (1 << DS18B20_DQ); // Configura como salida;
	DS18B20_PORT &= ~(1 << DS18B20_DQ); // Pulso de reset (bajo);
	_delay_us(480);
	DS18B20_PORT |= (1 << DS18B20_DQ); // Liberar la línea de datos;
	DS18B20_DDR &= ~(1 << DS18B20_DQ); // Configura como entrada;
	_delay_us(60);
	
	// Espera del pulso de presencia;
	while (DS18B20_PIN & (1 << DS18B20_DQ));
	_delay_us(480);
}

void ds18b20_write_bit(uint8_t bit) {
	DS18B20_DDR |= (1 << DS18B20_DQ); // Configura como salida;
	DS18B20_PORT &= ~(1 << DS18B20_DQ); // Baja la línea de datos;
	_delay_us(1); // Tiempo mínimo para establecer el bit;

	if (bit) {
		DS18B20_PORT |= (1 << DS18B20_DQ); // Si es 1, subir la línea;
	}
	_delay_us(60); // Completar el ciclo de escritura;
	DS18B20_PORT |= (1 << DS18B20_DQ); // Asegura la línea en alto;
}

uint8_t ds18b20_read_bit(void) {
	uint8_t bit = 0;
	DS18B20_DDR |= (1 << DS18B20_DQ); // Configura como salida;
	DS18B20_PORT &= ~(1 << DS18B20_DQ); // Baja la línea de datos;
	_delay_us(1);
	DS18B20_DDR &= ~(1 << DS18B20_DQ); // Configura como entrada;
	_delay_us(14);

	if (DS18B20_PIN & (1 << DS18B20_DQ)) {
		bit = 1;
	}
	_delay_us(45);
	return bit;
}

void ds18b20_write(uint8_t data) {
	for (uint8_t i = 0; i < 8; i++) {
		ds18b20_write_bit(data & 0x01);
		data >>= 1;
	}
}

uint8_t ds18b20_read(void) {
	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; i++) {
		data >>= 1;
		if (ds18b20_read_bit()) {
			data |= 0x80;
		}
	}
	return data;
}

float ds18b20_get_temperature(void) {
	uint8_t temp_lsb, temp_msb;
	int16_t temp;

	ds18b20_reset();
	ds18b20_write(0xCC); // Skip ROM command;
	ds18b20_write(0x44); // Start temperature conversion;

	_delay_ms(750); // Tiempo máximo de conversión;

	ds18b20_reset();
	ds18b20_write(0xCC); // Skip ROM command;
	ds18b20_write(0xBE); // Read Scratchpad;

	temp_lsb = ds18b20_read(); // Leer LSB de temperatura;
	temp_msb = ds18b20_read(); // Leer MSB de temperatura;

	temp = (temp_msb << 8) | temp_lsb; // Combinar LSB y MSB;
	return temp * 0.0625; // Convertir a grados Celsius;
}
