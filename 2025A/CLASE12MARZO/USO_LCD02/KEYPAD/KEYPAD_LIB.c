#include "KEYPAD_LIB.h"

void KeyPad_Init(){
	
	KEYPAD_DDR |= (1<<KEYPAD_F1) | (1<<KEYPAD_F2) | (1<<KEYPAD_F3) | (1<<KEYPAD_F4);
	KEYPAD_DDR &= ~( (1<<KEYPAD_C1) | (1<<KEYPAD_C2) | (1<<KEYPAD_C3) | (1<<KEYPAD_C4) );
	
}
char KeyPad_KeyPress(){
	KEYPAD_PORT = (1<<KEYPAD_F1);
	if( getStatusC1 ){
		return '1';
	}
	else if( getStatusC2 ){
		return '2';
	}
	else if( getStatusC3 ){
		return '3';
	}
	else if( getStatusC4 ){
		return 'A';
	}
	
	KEYPAD_PORT = (1<<KEYPAD_F2);
	if( getStatusC1 ){
		return 5;
	}
	else if( getStatusC2 ){
		return 6;
	}
	else if( getStatusC3 ){
		return 7;
	}
	else if( getStatusC4 ){
		return 8;
	}
	
	KEYPAD_PORT = (1<<KEYPAD_F3);
	if( getStatusC1 ){
		return 9;
	}
	else if( getStatusC2 ){
		return 10;
	}
	else if( getStatusC3 ){
		return 11;
	}
	else if( getStatusC4 ){
		return 12;
	}
	
	KEYPAD_PORT = (1<<KEYPAD_F4);
	if( getStatusC1 ){
		return 13;
	}
	else if( getStatusC2 ){
		return 14;
	}
	else if( getStatusC3 ){
		return 15;
	}
	else if( getStatusC4 ){
		return 16;
	}
	
	return 0;
	
	
}
char KeyPad_KeyClick(){
	KEYPAD_PORT = (1<<KEYPAD_F1);
	if( getStatusC1 ){
		while(getStatusC1);
		return '1';
	}
	else if( getStatusC2 ){
		while(getStatusC2);
		return '2';
	}
	else if( getStatusC3 ){
		while(getStatusC3);
		return '3';
	}
	else if( getStatusC4 ){
		while(getStatusC4);
		return 'A';
	}
	
	KEYPAD_PORT = (1<<KEYPAD_F2);
	if( getStatusC1 ){
		return 5;
	}
	else if( getStatusC2 ){
		return 6;
	}
	else if( getStatusC3 ){
		return 7;
	}
	else if( getStatusC4 ){
		return 8;
	}
	
	KEYPAD_PORT = (1<<KEYPAD_F3);
	if( getStatusC1 ){
		return 9;
	}
	else if( getStatusC2 ){
		return 10;
	}
	else if( getStatusC3 ){
		return 11;
	}
	else if( getStatusC4 ){
		return 12;
	}
	
	KEYPAD_PORT = (1<<KEYPAD_F4);
	if( getStatusC1 ){
		return 13;
	}
	else if( getStatusC2 ){
		return 14;
	}
	else if( getStatusC3 ){
		return 15;
	}
	else if( getStatusC4 ){
		return 16;
	}
	
	return 0;
}