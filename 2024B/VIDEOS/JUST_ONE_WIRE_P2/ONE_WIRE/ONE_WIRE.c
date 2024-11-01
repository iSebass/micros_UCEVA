#include "ONE_Wire.h"

// Variables globales;
unsigned char ROM_NO[MAX_DEVICES][8];              // Buffer para almacenar el número de ROM;


// Tabla CRC-8 proporcionada por Dallas;
static unsigned char dscrc_table[] = {
	0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
	157,195, 33,127,252,162, 64, 30, 95, 1,227,189, 62, 96,130,220,
	35,125,159,193, 66, 28,254,160,225,191, 93, 3,128,222, 60, 98,
	190,224, 2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
	70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89, 7,
	219,133,103, 57,186,228, 6, 88, 25, 71,165,251,120, 38,196,154,
	101, 59,217,135, 4, 90,184,230,167,249, 27, 69,198,152,122, 36,
	248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91, 5,231,185,
	140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
	17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
	175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
	50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
	202,148,118, 40,171,245, 23, 73, 8, 86,180,234,105, 55,213,139,
	87, 9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
	233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
	116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
};

// Método para hacer un reset en el bus 1-Wire;
int OWReset() {
	// Implementación específica para la plataform;
	// Aquí puedes añadir la lógica de hardware necesaria para tu microcontrolador.;
	// Debe devolver TRUE si hay presencia de dispositivos en el bus;
	uint16_t timeout=0;
	PORT_MODE_OUTPUT;  //CONFIGRUAR EL PIN DQ COMO SALIDA
	SET_BUS_LOW;       //ESTABLECER EL ESTADO LOGICO EN BAJO
	_delay_us(480);
	SET_BUS_HIGH;      //ESTABLECER EL ESTADO LOGICO EN ALTO
	PORT_MODE_INPUT;   //CONFIGRUAR EL PIN DQ COMO ENTRADA
	_delay_us(60);

	while( READ_BUS_STATUS ){ //ESPERA EL PULSO DE PRESENECIA
		timeout++;
		_delay_us(1);
		if(timeout>=480){
			return FALSE;
		}
	} 
	_delay_us(480);
	
	
	return TRUE;  // Esta implementación es solo de ejemplo;
}

// Método para enviar un byte en el bus 1-Wire;
void OWWriteByte(unsigned char byte_value) {
	for (int i = 0; i < 8; i++) {
		OWWriteBit(byte_value & 0x01);  // Envía el bit menos significativo primero;
		byte_value >>= 1;
	}
}

// Método para enviar un bit en el bus 1-Wire;
void OWWriteBit(unsigned char bit_value) {
	PORT_MODE_OUTPUT; //CONFIGRUAR EL PIN DQ COMO SALIDA
	SET_BUS_LOW;      //ESTABLECER EL ESTADO LOGICO EN BAJO
	if (bit_value) {
		// Si es un 1, mantén el bus en bajo solo 1-15 microsegundos;
		_delay_us(1);   // Tiempo mínimo en bajo;
		SET_BUS_HIGH;   // Liberar el bus;
		_delay_us(60);  // Completar el tiempo del slot;
		} else {
		// Si es un 0, mantén el bus en bajo por 60 microsegundos;
		_delay_us(60);  // Tiempo total en bajo para un 0;
		SET_BUS_HIGH;   // Liberar el bus;
	}
}

// Método para leer un byte del bus 1-Wire;
unsigned char OWReadByte() {
	unsigned char byte_value = 0;
	for (int i = 0; i < 8; i++) {
		byte_value >>= 1;
		if (OWReadBit()) {
			byte_value |= 0x80;  // Coloca 1 en el bit más significativo si se leyó un 1;
		}
	}
	return byte_value;
}

// Método para leer un bit del bus 1-Wire;
unsigned char OWReadBit() {
	uint8_t bit = 0;

	PORT_MODE_OUTPUT;  // Configurar el pin DQ como salida;
	SET_BUS_LOW;       // Establecer el bus en bajo;
	_delay_us(1);      // Esperar 1 microsegundo;
	
	PORT_MODE_INPUT;   // Configurar el pin DQ como entrada para leer;
	_delay_us(14);     // Esperar ~14 microsegundos para estabilizar;

	// Leer el estado del bus;
	if (READ_BUS_STATUS) {
		bit = 1;  // Si el bus está en alto, el bit es 1;
	}
	
	_delay_us(45);     // Esperar hasta completar el slot de tiempo (~60us total);
	return bit;        // Devolver el bit leído;
}

// Método principal para el algoritmo de búsqueda;
int OWSearch() {
	static int last_discrepancy = 0;
	int pos_discrepancy = 0;
	int device_found = 0;
	int bit, nbit, bit_decision, maskbits = 0;
	int current_discrepancy = 0; // PARA ALMACENAR LA POSICIÓN DE LA DISCREPANCIA ACTUAL
	bool search_direction;       // PARA ALMACENAR LA DIRECCIÓN TOMADA EN LA BÚSQUEDA
	
	// COMENZAMOS LA BÚSQUEDA DESDE CERO O DESDE EL ÚLTIMO PUNTO DE DISCREPANCIA
	do {
		maskbits = 0;
		current_discrepancy = 0; // RESETEAR LA DISCREPANCIA ACTUAL EN CADA CICLO DE BÚSQUEDA

		// GENERAMOS RESET Y EN CASO DE NO TENER DISPOSITIVOS EN EL BUS REGRESAMOS -1
		if (!OWReset()) {
			return -1;
		}
		
		// ENVIAMOS EL COMANDO SEARCH_ROM
		OWWriteByte(SEARCH_ROM);

		// RECORREMOS LOS 64 BITS (8 BYTES) DEL CÓDIGO ROM
		for (uint8_t currentbyte = 0; currentbyte < 8; currentbyte++) {
			for (uint8_t currentbit = 0; currentbit < 8; currentbit++) {
				bit  = OWReadByte();  // LEER EL BIT ACTUAL
				nbit = OWReadByte();  // LEER EL COMPLEMENTO DEL BIT

				// SI AMBOS BITS SON 1, NO HAY MÁS DISPOSITIVOS EN EL BUS
				if (bit == 1 && nbit == 1) {
					return -1;
				}
				
				// SI BIT Y NBIT SON DIFERENTES, SEGUIMOS EL CAMINO QUE CORRESPONDA
				else if (bit != nbit) {
					search_direction = bit;  // NO HAY DISCREPANCIA EN ESTE NIVEL, TOMAMOS EL BIT QUE SE LEYÓ
				}
				// SI HAY UNA DISCREPANCIA (BIT == 0 Y NBIT == 0)
				else {
					if (current_discrepancy < last_discrepancy) {
						// SI YA EXPLORAMOS ESTE NIVEL DE DISCREPANCIA, SEGUIMOS LA MISMA RUTA QUE ANTES
						search_direction = ((ROM_NO[device_found][currentbyte] & (1 << currentbit)) != 0);
						} else if (current_discrepancy == last_discrepancy) {
						// SI ESTAMOS EN LA ÚLTIMA DISCREPANCIA CONOCIDA, TOMAMOS LA RUTA DEL 1
						search_direction = 1;
						} else {
						// SI ENCONTRAMOS UNA NUEVA DISCREPANCIA, TOMAMOS LA RUTA DEL 0 POR DEFECTO
						search_direction = 0;
						current_discrepancy = currentbyte * 8 + currentbit; // GUARDAMOS LA POSICIÓN DE LA NUEVA DISCREPANCIA
					}

					// GUARDAMOS LA DISCREPANCIA MÁS RECIENTE
					if (!search_direction) {
						pos_discrepancy = currentbyte * 8 + currentbit;
					}
				}

				// ESCRIBIMOS EL BIT DECIDIDO EN EL BUS 1-WIRE
				OWWriteByte(search_direction);

				// ALMACENAMOS EL BIT EN EL ROM
				if (search_direction) {
					maskbits |= (1 << currentbit);  // GUARDAR EL BIT '1'
					} else {
					maskbits &= ~(1 << currentbit); // GUARDAR EL BIT '0'
				}
			}
			// ALMACENAR EL BYTE EN LA ROM DEL DISPOSITIVO
			ROM_NO[device_found][currentbyte] = maskbits;
			maskbits = 0;
		}

		// ACTUALIZAMOS LA ÚLTIMA DISCREPANCIA PARA LA SIGUIENTE BÚSQUEDA
		last_discrepancy = pos_discrepancy;

		device_found++;

	} while (device_found < MAX_DEVICES && last_discrepancy != 0); // SEGUIR BUSCANDO MIENTRAS QUEDEN DISCREPANCIAS

	return device_found;
}

// Método para calcular el CRC8 de un valor;
unsigned char docrc8(unsigned char value) {
	uint8_t crc8 = dscrc_table[crc8 ^ value];  // Calcula el CRC8 basado en la tabla
	return crc8;
}