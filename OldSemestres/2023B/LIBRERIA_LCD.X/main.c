#include <xc.h>
#include "config.h"
#include "LCD_LIB.h"

void main(void){
    
    LCD_Init();
    
    LCD_Write_Text_Cp("01234567890123456789");
    __delay_ms(500);
    
    LCD_Cmd(_LCD_CURSOR_OFF);
    __delay_ms(500);
    LCD_Cmd(_LCD_TURN_OFF);
    __delay_ms(500);
    LCD_Cmd(_LCD_TURN_ON);
   


    
    
    
    while(1){
    
        
    }
    return;
}
