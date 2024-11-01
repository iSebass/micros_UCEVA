#include "DS18B20_LIB.h"
#include "../ONE_WIRE/ONE_Wire.h"

uint8_t found_ROMs[MAX_DEVICES][8];  // Almacenar las ROMs encontradas;

float ds18b20_get_temp(void){
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;
	
	// Resetear el bus y verificar si hay un dispositivo presente;
	if (!OWReset()) {
		return -999.0;  // Valor de error si no se detecta el sensor;
	}
	OWWriteByte(SKIP_ROM); //SKIP ROOM
	OWWriteByte(CONVER_T); //START CONVER
	
	_delay_ms(750);
	
	OWReset();
	OWWriteByte(SKIP_ROM);
	OWWriteByte(READ_SCRATCHPAD);  //LEER LA MEMORIA
	
	temp_lsb = OWReadByte();
	temp_msb = OWReadByte();
	
	temp = (temp_msb << 8) | temp_lsb;
	
	return temp*0.0625;
}

// Método para buscar y almacenar las ROMs de los sensores conectados;
int ds18b20_search_devices(void) {
	int num_devices = 0;
	if (!OWReset()) {
		return -1;  // No se detectó ningún dispositivo;
	}

	OWWriteByte(0xF0);  // Iniciar búsqueda de ROM;

	// Buscar dispositivos en el bus;
	while (num_devices < MAX_DEVICES && OWSearch()) {
		// Almacenar la ROM del dispositivo encontrado;
		for (int i = 0; i < 8; i++) {
			found_ROMs[num_devices][i] = ROM_NO[i];
		}
		num_devices++;
	}

	return num_devices;  // Retorna el número de dispositivos encontrados;
}

// Método para leer la temperatura de un sensor específico usando su ROM;
float ds18b20_get_temp_by_rom(char id) {
	
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;

	// Resetear el bus y verificar si hay un dispositivo presente;
	if (!OWReset()) {
		return -999.0;  // Error si no se detecta el sensor;
	}

	OWWriteByte(MATCH_ROM);  // Seleccionar un sensor específico usando MATCH_ROM;

	// Enviar la ROM del sensor;
	for (int i = 0; i < 8; i++) {
		OWWriteByte(found_ROMs[id]);
	}

	OWWriteByte(CONVER_T);   // Iniciar la conversión de temperatura;
	_delay_ms(750);          // Espera para la conversión;

	// Reiniciar el bus y leer los datos de temperatura desde el scratchpad;
	if (!OWReset()) {
		return -999.0;  // Error si no se detecta el sensor;
	}

	OWWriteByte(MATCH_ROM);  // Seleccionar el sensor nuevamente;
	for (int i = 0; i < 8; i++) {
		OWWriteByte(found_ROMs[id]);
	}

	OWWriteByte(READ_SCRATCHPAD);  // Leer el scratchpad;

	temp_lsb = OWReadByte();  // Leer LSB de la temperatura;
	temp_msb = OWReadByte();  // Leer MSB de la temperatura;

	temp = (temp_msb << 8) | temp_lsb;  // Combinar los bytes de temperatura;

	return temp * 0.0625;  // Convertir a grados Celsius;
}

