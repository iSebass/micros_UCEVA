

#include "mcc_generated_files/mcc.h"
#include "LCD_LIB.h"
#include <stdio.h>


float temp, pot, ekg;

char strText[20]=" ";

void main(void)
{

    SYSTEM_Initialize();
    LCD_Init();
    LCD_Cmd(_LCD_CURSOR_OFF);

    while (1)
    {
        temp = ADC_GetConversion(0);
        __delay_ms(20);
        pot  = ADC_GetConversion(1);
        __delay_ms(20);
        ekg  = ADC_GetConversion(2);
        __delay_ms(20);
        
        temp = (150.0/308.0)*temp;
        
        sprintf(strText,"temp: %6.1f", temp);
        LCD_Write_Text(1, 1,  strText);
        __delay_ms(200);
    }
}
/**
 End of File
*/