#include <xc.h>
#include "config.h"

void __interrupt() IOC_Int(){
    
    if(INTCONbits.IOCIF == 1){
        if(IOCBFbits.IOCBF0 == 1){
            LATDbits.LATD0 ^=1;
        }
        if(IOCBFbits.IOCBF1 == 1){
            LATDbits.LATD1 ^=1;
        }
        
        IOCBF = 0x00;
        INTCONbits.IOCIF = 0;
    }
    
}

void main(void){
    OSCCON  = 0x38;
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    
    ANSELDbits.ANSD0 = 0;
    TRISDbits.TRISD0 = 0;
    
    ANSELDbits.ANSD1 = 0;
    TRISDbits.TRISD1 = 0;
    
    LATD = 0x00;
    
    INTCONbits.IOCIF = 0;
    INTCONbits.IOCIE = 1;
    INTCONbits.PEIE  = 1;
    INTCONbits.GIE   = 1;
    
    IOCBPbits.IOCBP0 = 1;
    IOCBNbits.IOCBN0 = 0;
    
    IOCBPbits.IOCBP1 = 1;
    IOCBNbits.IOCBN1 = 0;
    
    while(1){
        __delay_ms(30);
    }
    
    return;
}
