#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "UART.h"
#include "ADC_LIB.h"

int conver;
float pot1,pot2;
char bufferTx[50]=" ";

void main(void){
    
    OSCCON = 0x38;
    OSCTUNE = 0x00;
    BORCON = 0x00;
    
    ANSELAbits.ANSA0 = 1;
    ADC_Init();
    UART_Init();
   
    
    while(1){
        conver = ADC_Read(0);
        pot1 = 5.0*conver/1023.0;
        
        conver = ADC_Read(1);
        pot2 = 5.0*conver/1023.0;
        
        sprintf(bufferTx,"#%7.5f/%3.1f*\r\n",pot1, pot2);
        UART_Write_Text(bufferTx);
        
        __delay_ms(20);
        
        
        
    }
    return;
}
