#include "DS18B20_LIB.h"

void ds18b20_reset(void);
void ds18b20_write_bit(uint8_t bit);
uint8_t ds18b20_read_bit(void);

void ds18b20_init(void){
	DS18B20_DDR  |= (1<<DS18B20_DQ); //CONFIGRUAR EL PIN DQ COMO SALIDA
	DS18B20_PORT |= (1<<DS18B20_DQ); //ESTABLECER EL ESTADO LOGICO EN ALTO
}

void ds18b20_reset(void){
	DS18B20_DDR  |=  (1<<DS18B20_DQ); //CONFIGRUAR EL PIN DQ COMO SALIDA
	DS18B20_PORT &= ~(1<<DS18B20_DQ); //ESTABLECER EL ESTADO LOGICO EN BAJO
	_delay_us(480);
	DS18B20_PORT |= (1<<DS18B20_DQ); //ESTABLECER EL ESTADO LOGICO EN ALTO
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //CONFIGRUAR EL PIN DQ COMO ENTRADA
	_delay_us(60);

	while(DS18B20_PIN & (1<<DS18B20_DQ) ); //ESPERA EL PULSO DE PRESENECIA
	_delay_us(480);
}

void ds18b20_write_bit(uint8_t bit){
	DS18B20_DDR  |=  (1<<DS18B20_DQ); //CONFIGRUAR EL PIN DQ COMO SALIDA
	DS18B20_PORT &= ~(1<<DS18B20_DQ); //ESTABLECER EL ESTADO LOGICO EN BAJO
	_delay_us(1);
	if(bit){
		DS18B20_PORT |= (1<<DS18B20_DQ);
	}
	_delay_us(60);
	DS18B20_PORT |= (1<<DS18B20_DQ); //REESTABLECER EL BUS
}

uint8_t ds18b20_read_bit(void){
	uint8_t bit = 0;
	DS18B20_DDR |= (1<<DS18B20_DQ);  //CONFIGRUAR EL PIN DQ COMO SALIDA
	DS18B20_PORT &= ~(1<<DS18B20_DQ); //ESTABLECER EL ESTADO LOGICO EN BAJO
	_delay_us(1);
	
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //CONFIGRUAR EL PIN DQ COMO SALIDA
	_delay_us(14);
	
	if( DS18B20_PIN & (1<<DS18B20_DQ) ){
		bit = 1;
	}
	_delay_us(45);
	return bit;
}

void ds18b20_write(uint8_t byte){
	
	for(uint8_t i=0; i<=7; i++){
		ds18b20_write_bit(byte & 0x01);
		byte >>=1;
	}
}
uint8_t ds18b20_read(){
	uint8_t data=0;
	for(uint8_t i=0; i<=7; i++){
		data >>=1;
		if( ds18b20_read_bit() ){
			data |= 0x80;
		}
	}
	return data;
}

float ds18b20_get_temp(void){
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;
	
	ds18b20_reset();
	ds18b20_write(0xCC); //SKIP ROOM
	ds18b20_write(0x44); //START CONVER
	
	_delay_ms(750);
	
	ds18b20_reset();
	ds18b20_write(0xCC);
	ds18b20_write(0xBE);  //LEER LA MEMORIA
	
	temp_lsb = ds18b20_read();
	temp_msb = ds18b20_read();
	
	temp = (temp_msb << 8) | temp_lsb;
	
	return temp*0.0625;
	
	
}

//METODOS MULTIPUNTO

void ds18b20_read_rom(char *mem){
	
	ds18b20_reset();
	ds18b20_write(READ_ROM);
	
	for(uint8_t i=0; i<=7; i++){
		mem[i]=ds18b20_read();
	}
	
	ds18b20_reset();
	_delay_ms(500);
	
}



float ds18b20_get_temp_idx(char *mem){
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;
	
	ds18b20_reset();
	ds18b20_write(MATCH_ROM);
	
	for(uint8_t i=0; i<=7; i++){
		ds18b20_write(mem[i]);
	}
	
	ds18b20_write(CONVER_T);
	_delay_ms(750);
	
	ds18b20_reset();
	ds18b20_write(MATCH_ROM);
	
	for(uint8_t i=0; i<=7; i++){
		ds18b20_write(mem[i]);
	}
	
	ds18b20_write(READ_SCRATCHPAD);
	
	temp_lsb = ds18b20_read();
	temp_msb = ds18b20_read();
	
	temp = (temp_msb << 8) | temp_lsb;
	
	return temp*0.0625;
}

//METODO PARA ENCONTRAR EL ROM
void ds18b20_search_rom(char (*mem)[8]){
	
	int id_bit_number = 1;
	int last_zero = 0;
	int rom_byte_number = 0;
	int search_result = 0;
	unsigned char rom_byte_mask = 1;
	unsigned char id_bit, cmp_id_bit;
	unsigned char search_direction;

	// Inicializa la búsqueda
	crc8 = 0;

	if (!LastDeviceFlag) {
		if (!OWReset()) {
			LastDiscrepancy = 0;
			LastDeviceFlag = FALSE;
			LastFamilyDiscrepancy = 0;
			return FALSE;
		}

		OWWriteByte(0xF0);  // Comando de búsqueda

		// Bucle para hacer la búsqueda
		do {
			id_bit = ds18b20_read_bit();
			cmp_id_bit = ds18b20_read_bit();

			if (id_bit == 1 && cmp_id_bit == 1) {
				break;
				} else {
				if (id_bit != cmp_id_bit) {
					search_direction = id_bit;
					} else {
					if (id_bit_number < LastDiscrepancy) {
						search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
						} else {
						search_direction = (id_bit_number == LastDiscrepancy);
					}

					if (search_direction == 0) {
						last_zero = id_bit_number;

						if (last_zero < 9) {
							LastFamilyDiscrepancy = last_zero;
						}
					}
				}

				if (search_direction == 1) {
					ROM_NO[rom_byte_number] |= rom_byte_mask;
					} else {
					ROM_NO[rom_byte_number] &= ~rom_byte_mask;
				}

				OWWriteBit(search_direction);

				id_bit_number++;
				rom_byte_mask <<= 1;

				if (rom_byte_mask == 0) {
					docrc8(ROM_NO[rom_byte_number]);
					rom_byte_number++;
					rom_byte_mask = 1;
				}
			}
		} while (rom_byte_number < 8);

		if (id_bit_number < 65 && crc8 == 0) {
			LastDiscrepancy = last_zero;
			LastDeviceFlag = (LastDiscrepancy == 0);
			search_result = TRUE;
		}
	}

	if (!search_result || !ROM_NO[0]) {
		LastDiscrepancy = 0;
		LastDeviceFlag = FALSE;
		LastFamilyDiscrepancy = 0;
		search_result = FALSE;
	}

	return search_result;
	
}