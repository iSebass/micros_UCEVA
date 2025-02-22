#include <xc.h>
#include "config.h"

char decoCC[10]={191,134,219,207,230,237,253,135,255,231};
char decoAC[10]={64,121,36,48,25,18,2,120,0,24};

int numer=62, unidad, decena;
void main(void){
    TRISD = 0x00;
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    while(1){
        decena = numer / 10;
        unidad = numer % 10;
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 0;
        LATD = decoCC[unidad];
        __delay_ms(30);
        LATBbits.LATB0 = 0;
        LATBbits.LATB1 = 1;
        LATD = decoCC[decena];
        __delay_ms(30);
    }
    
    return;
}
