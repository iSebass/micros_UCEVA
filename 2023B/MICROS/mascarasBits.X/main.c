#include <xc.h>
#include "config.h"

void main(void){
    TRISD = 0x00;
    LATD  = 0xFF; 
    
    LATD  &= ~( (1<<5) | (1<<3) | (1<<0)  ); // ~ alt+126
    
    while(1){
        
    }
    return;
}
