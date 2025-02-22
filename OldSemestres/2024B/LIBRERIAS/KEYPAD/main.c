#include "CONFIG.h"

int main(void){
	
	DDRDbits.NIBBLE_L = 0xF;
	DDRDbits.NIBBLE_H = 0x0;
	
	
    while(1){
		
		PORTDbits.D0 = PINDbits.D4;
		PORTDbits.D1 = PINDbits.D5;
		PORTDbits.D2 = PINDbits.D6;
		PORTDbits.D3 = PINDbits.D7;
		
		_delay_ms(50);
	}
	
}

