#include <pic16f1939.h>
#include "UART.h"



void UART_Init(){
    TX_Dir = 0;
    RX_Dir = 1;
    
    //SPBRG = (unsigned int)( (_XTAL_FREQ/(64.0*baudrate))-1 ); //LOW SPEED
    SPBRG = 129; //HIGH SPEED
    
    TXSTAbits.SYNC = 0; // Asincrono
    TXSTAbits.BRGH = 1; // HIGH SPEED
    
    TXSTAbits.TXEN = 1; // HABILITAMOS EL ENVIO TX
    RCSTAbits.SPEN = 1; // HABILITAMOS SERIAL PORT
    RCSTAbits.CREN = 1; // HABILITAMOS LA RECEPCION RX 
    
}
void UART_Write(char c){
    while(!TXIF);
    TXREG = c;
}

void UART_Write_Text(char *c){
    while(*c){
        UART_Write(*c);
        c++;
    }
}
char UART_Read(void){
    while(!RCIF);
    return RCREG;
}
