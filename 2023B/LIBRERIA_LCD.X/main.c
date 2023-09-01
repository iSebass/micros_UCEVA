#include <xc.h>
#include "config.h"
#include "LCD_LIB.h"

void main(void){
    
    LCD_Init();
    
    LCD_Write_Text_Cp("01234567890123456789");
    LCD_Set_Cursor(2,6);
   


    
    
    
    while(1){
    
        
    }
    return;
}
