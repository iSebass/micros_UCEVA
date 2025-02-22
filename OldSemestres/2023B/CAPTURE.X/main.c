#include <xc.h>


int main(void){
    
    OSCCON  = 0x38;
    OSCTUNE = 0x00;
    BORCON  = 0x00;
    
    // MODO CAPTURE
    CCP4CONbits.CCP4M3 = 0; 
    CCP4CONbits.CCP4M2 = 1; 
    CCP4CONbits.CCP4M1 = 1; 
    CCP4CONbits.CCP4M0 = 1; 
    
    while(1){
        
        
        
    }
    
    return;
}
