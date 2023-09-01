#include <xc.h>
#include "config.h"
#include "DISPLAY_7_SEG.h"

char contador=0;

void main(void){
    ANSELB = 0x00;
    display_init();
    
    
    
    while(1){
        display_cc(0);
        contador++;
        __delay_ms(500);
        if(contador>9)
            contador=0;
        
    }
    return;
}
