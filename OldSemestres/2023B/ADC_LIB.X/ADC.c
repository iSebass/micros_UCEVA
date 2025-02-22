#include "ADC.h"

void ADC_Init(){
    ADCON1bits.ADFM   = 1; // Justificamos a la derecha
    ADCON1bits.ADCS   = 0b110; // Fosc/64
    ADCON1bits.ADNREF = 0;
    ADCON1bits.ADPREF = 0b00;
    ADCON0bits.ADON   = 1;
}
int ADC_Get_Value(char ch){
    ADCON0bits.CHS      =  ch & 0x1F;
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE == 1);
    return ( (ADRESH<<8) | ADRESL );
}
