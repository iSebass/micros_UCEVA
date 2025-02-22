#include <xc.h>
#include "config.h"

//#define ANSEL_ ANSELC
#define TRIS_  TRISC
#define LAT_   LATC
#define PORT_  PORTC

void main(void){
    OSCCONbits.IRCF = 0b1110;
    OSCCONbits.SCS = 0b10;
    //ANSEL_ = 0x00;
    TRIS_ = 0x00;
    LAT_ = 0x00;
    
    while(1){
        for(char i=0; i<=7; i++){
            LAT_ |= (1<<i);
            __delay_ms(50);
        }
        LAT_ = 0;
        __delay_ms(50);
    }
   
    return;
}
