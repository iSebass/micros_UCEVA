#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "UART.h"
#include "ADC_LIB.h"

int conver;
float pot;
char buffer[20]=" ";

void main(void){
    
    OSCCON = 0x38;
    OSCTUNE = 0x00;
    BORCON = 0x00;
    
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA0 = 1;
    
    ADC_Init();
    UART_Init(9600);
    
    
    while(1){
//        conver = ADC_Read(0);
//        pot = conver*5.0/1023.0;
//        sprintf(buffer,"POT: %3.1f \r\n",pot);
//        UART_Write_Text(buffer);
        __delay_ms(500);
    }
    return;
}
