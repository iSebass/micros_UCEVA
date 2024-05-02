#include <xc.h>
#include "config.h"
#include "I2C_LIB.h"


char contador;

void main(void){
    
    ClockInit();
    I2C1_Initialize();
    PinInit();
    
    
    while(1){
        I2C1_Write(0x27,contador);
        contador++;
        contador = contador > 15 ? 0 : contador;
        LED_Toggle();
        __delay_ms(200);
    }
    
    return;
}
