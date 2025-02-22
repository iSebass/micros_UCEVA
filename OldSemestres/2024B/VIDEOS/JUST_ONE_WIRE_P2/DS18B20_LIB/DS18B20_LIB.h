
#ifndef DS18B20_LIB_H_
#define DS18B20_LIB_H_


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>



//#define MAX_DEVICES 3  // Número máximo de dispositivos a manejar;

// Declarar externamente la variable found_ROMs para ser utilizada en main.c
//extern uint8_t found_ROMs[MAX_DEVICES][8];

//COMANDOS DE ROM
#define SEARCH_ROM           0xF0
#define READ_ROM             0x33
#define MATCH_ROM            0x55
#define SKIP_ROM             0xCC
#define ALARM_SEARCH_ROM     0xEC

// COMANDOS FUNCTION
#define CONVER_T             0x44
#define WRITE_SCRATCHPAD     0x4E
#define READ_SCRATCHPAD      0xBE
#define COPY_SCRATCHPAD      0x48
#define RECALL_EEPROM        0xB8
#define READ_PWR_SUPPLY      0xB4


//DEFINIR EL PUERTO Y EL PIN DEL SENSOR
#define DS18B20_PORT  PORTB
#define DS18B20_DDR   DDRB
#define DS18B20_PIN   PINB
#define DS18B20_DQ    PINB0

//DEFINIRMOS LOS PROTOTIPOS DE FUNCION
float ds18b20_get_temp(void);
int ds18b20_search_devices(void);
float ds18b20_get_temp_by_rom(char id);


#endif /* DS18B20_LIB_H_ */