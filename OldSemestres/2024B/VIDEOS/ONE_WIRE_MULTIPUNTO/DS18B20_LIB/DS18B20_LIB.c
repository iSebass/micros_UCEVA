#include "DS18B20_LIB.h"

void ds18b20_reset(void);
void ds18b20_write_bit(uint8_t bit);
uint8_t ds18b20_read_bit(void);
void mathRom(char *rom);

//DIRECCIONES PARA MULTIPLES SENSORES
char memRoms[MAX_DEVICES][8];

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
	ds18b20_write(SKIP_ROM); //SKIP ROOM
	ds18b20_write(CONVER_T); //START CONVER
	
	_delay_ms(750);
	
	ds18b20_reset();
	ds18b20_write(SKIP_ROM);
	ds18b20_write(READ_SCRATCHPAD);  //LEER LA MEMORIA
	
	temp_lsb = ds18b20_read();
	temp_msb = ds18b20_read();
	
	temp = (temp_msb << 8) | temp_lsb;
	
	return temp*0.0625;
}

//METODOS PARA MULTIPUNTO

void ds18b20_read_rom(char *mem){
	uint8_t i;
	ds18b20_reset();
	ds18b20_write(READ_ROM);
	
	for(i=0; i<=7; i++){
		*(mem+i)=ds18b20_read();
	}
	
	ds18b20_reset();
	_delay_us(500);
}


float ds18b20_get_temp_idx(char *rom) {
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;

	// Reseteo y envío de MATCH_ROM con la ROM proporcionada
	ds18b20_reset();
	ds18b20_write(MATCH_ROM); // Comando MATCH_ROM (0x55)

	// Enviar la ROM completa del sensor (pasada como parámetro)
	for (uint8_t i = 0; i < 8; i++) {
		ds18b20_write(rom[i]);
	}

	// Iniciar la conversión de temperatura
	ds18b20_write(CONVER_T); // START CONVERSION (0x44)
	_delay_ms(750); // Esperar 750ms para que la conversión de temperatura esté lista

	// Realizar un reset antes de leer el scratchpad
	ds18b20_reset();
	ds18b20_write(MATCH_ROM); // Volver a seleccionar el mismo sensor con MATCH_ROM

	// Enviar la ROM de nuevo
	for (uint8_t i = 0; i < 8; i++) {
		ds18b20_write(rom[i]);
	}

	// Leer los datos del scratchpad
	ds18b20_write(READ_SCRATCHPAD);  // Comando READ SCRATCHPAD (0xBE)
	
	// Leer los dos bytes de temperatura
	temp_lsb = ds18b20_read();
	temp_msb = ds18b20_read();

	// Combinar los bytes de temperatura en un valor de 16 bits
	temp = (temp_msb << 8) | temp_lsb;

	// Convertir a grados Celsius (cada incremento es 0.0625°C)
	return temp * 0.0625;
}

void getRooms(char *mem, char idx){
	for(uint8_t i=0; i<=7; i++){
		*(mem+i)= memRoms[idx][i];
	}
}


void ds18b20_search_rom() {
	uint8_t id_bit, cmp_id_bit;
	uint8_t rom_byte_idx = 0;
	uint8_t rom_bit_mask = 1;
	uint8_t rom[8];  // Para almacenar temporalmente el ROM encontrado
	uint8_t last_zero = 0;  // Última posición de bit 0 cuando hay una colisión
	uint8_t last_discrepancy = 0;  // Última discrepancia encontrada en la búsqueda anterior
	uint8_t search_direction;
	uint8_t roms_found = 0;  // Contador de dispositivos encontrados
	uint8_t search_completed = 0;  // Indicador para finalizar la búsqueda

	// Inicializa el array de ROMs detectados
	for (int i = 0; i < MAX_DEVICES; i++) {
		for (int j = 0; j < 8; j++) {
			memRoms[i][j] = 0x00;
		}
	}

	while (!search_completed && (roms_found < MAX_DEVICES)) {
		rom_byte_idx = 0;
		rom_bit_mask = 1;
		last_zero = 0;
		search_direction = 0;

		// Reiniciar la comunicación con el bus 1-Wire
		ds18b20_reset();
		ds18b20_write(SEARCH_ROM);  // Comando SEARCH ROM

		for (uint8_t bit_position = 1; bit_position <= 64; bit_position++) {
			// Leer el bit del dispositivo y su complemento
			id_bit = ds18b20_read_bit();
			cmp_id_bit = ds18b20_read_bit();

			if (id_bit == 1 && cmp_id_bit == 1) {
				// No hay dispositivos presentes, error en la línea o fin de la búsqueda
				search_completed = 1;
				break;
				} else if (id_bit == 0 && cmp_id_bit == 0) {
				// Colisión detectada
				if (bit_position < last_discrepancy) {
					// Si la posición está antes de la última discrepancia, seguir el mismo camino
					search_direction = (rom[rom_byte_idx] & rom_bit_mask) ? 1 : 0;
					} else if (bit_position == last_discrepancy) {
					// Si estamos en la última discrepancia, tomar el camino 1
					search_direction = 1;
					} else {
					// Si estamos después de la última discrepancia, tomar el camino 0
					search_direction = 0;
					last_zero = bit_position;  // Guardar la posición de la colisión
				}
				} else {
				// No hay colisión, seguir el valor del bit actual
				search_direction = id_bit;
			}

			// Escribir el bit seleccionado en el bus
			ds18b20_write_bit(search_direction);

			// Almacenar el bit en el ROM temporal
			if (search_direction == 1) {
				rom[rom_byte_idx] |= rom_bit_mask;
				} else {
				rom[rom_byte_idx] &= ~rom_bit_mask;
			}

			// Mover al siguiente bit
			rom_bit_mask <<= 1;
			if (rom_bit_mask == 0) {
				rom_byte_idx++;
				rom_bit_mask = 1;
			}
		}

		// Guardar el ROM encontrado en el array memRoms
		for (int i = 0; i < 8; i++) {
			memRoms[roms_found][i] = rom[i];
		}

		roms_found++;  // Incrementar el número de dispositivos encontrados

		// Actualizar la última discrepancia para la siguiente búsqueda
		if (last_zero == 0) {
			search_completed = 1;  // No hay más colisiones, finalizar la búsqueda
			} else {
			last_discrepancy = last_zero;  // Guardar la última colisión para la próxima iteración
		}
	}
}

