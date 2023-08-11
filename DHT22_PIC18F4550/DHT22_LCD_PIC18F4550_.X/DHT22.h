


#define TRIS_DHT TRISCbits.TRISC2
#define PORT_DHT PORTCbits.RC2
#define LAT_DHT LATCbits.LATC2

void DHT22_init(void){
    TRIS_DHT = 0;       //Pin como salida
    LAT_DHT = 1;        //Nivel alto
}

uint8_t DHT22_read(float *dht_temperatura, float *dht_humedad){

    uint8_t bits[5];
	uint8_t i,j=0;
     
    LAT_DHT = 0;        //Nivel bajo
    __delay_ms(18);  
    
    LAT_DHT = 1;        //Nivel alto 
    __delay_us(40);
    
    TRIS_DHT = 1;       //Pin como entrada
    
    if(PORT_DHT){
        TRIS_DHT = 0;       //Pin como salida
        PORT_DHT = 1;       //Nivel alto  
        return 0;
    }    
    __delay_us(80);
    
    if(!PORT_DHT){
        TRIS_DHT = 0;       //Pin como salida
        PORT_DHT = 1;       //Nivel alto  
        return 0;
    }
    __delay_us(80);
    
     for (j=0; j<5; j++)
	{
	uint8_t result=0;
		for (i=0; i<8; i++)
		{
			while (!PORT_DHT);
				__delay_us(35);

			if (PORT_DHT)
				result |= (1<<(7-i));
					
			while(PORT_DHT);
		}
		bits[j] = result;
	}
    
    TRIS_DHT = 0;       //Pin como salida
    PORT_DHT = 1;       //Nivel alto  
    
  
    if ((uint8_t) (bits[0] + bits[1] + bits[2] +bits[3]) == bits[4])		//Pregunta por el chekin
	{
                
		uint16_t rawhumidity = bits[0]<<8 | bits[1];
		uint16_t rawtemperature = bits[2] <<8 | bits[3];
        
		if (rawtemperature & 0x8000){
			*dht_temperatura = (float)((rawtemperature & 0x7fff) / 10.0)* -1.0;
		}else{
			*dht_temperatura = (float)(rawtemperature)/10.0;
		}

		*dht_humedad = (float)((rawhumidity)/10.0);
        return 1;  	
	}
    return 0;
}
