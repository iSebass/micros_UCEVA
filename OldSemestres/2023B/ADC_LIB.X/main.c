#include <xc.h>
#include "config.h"
#include "ADC.h"

int conver;

void main(void){
    OSCCON  = 0x72;
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA0 = 1;
    
    ANSELD = 0x00;
    TRISD  = 0x00;
    TRISC = 0xF0;
    
    ADC_Init();
    
    while(1){
        int conver = ADC_Get_Value(0);
        LATD = conver&0x0FF;
        LATC = (conver&0x300)>>8;
        __delay_ms(20);
    }
    
    return;
}
