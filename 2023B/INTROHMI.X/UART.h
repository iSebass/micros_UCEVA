/* 
 * File:   UART.h
 * Author: iProf
 *
 * Created on October 18, 2023, 11:20 AM
 */

#ifndef UART_H
#define	UART_H

#include <xc.h>
#include "config.h"

#define TX_Dir  TRISCbits.TRISC6
#define RX_Dir  TRISCbits.TRISC7


void UART_Init();
void UART_Write(char c);
void UART_Write_Text(char *c);
char UART_Read(void);


#endif	/* UART_H */

