/*
 * DS18B20_LIB.h
 *
 * Created: 18/09/2024 03:08:27 a. m.
 *  Author: USER
 */ 

#ifndef DS18B20_H
#define DS18B20_H

#define F_CPU 8000000UL
#include <avr/io.h>

// Define el puerto y pin donde está conectado el DS18B20;
#define DS18B20_PORT PORTB
#define DS18B20_DDR  DDRB
#define DS18B20_PIN  PINB
#define DS18B20_DQ   PB0

// Prototipos de funciones;
void ds18b20_init(void);
void ds18b20_write(uint8_t data);
uint8_t ds18b20_read(void);
float ds18b20_get_temperature(void);

#endif