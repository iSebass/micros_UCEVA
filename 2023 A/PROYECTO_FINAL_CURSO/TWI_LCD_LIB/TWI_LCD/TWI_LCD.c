#include "TWI_LCD.h"
#define LED_LCD_ON    0b00001000
#define LED_LCD_OFF   0b00000000

static uint8_t statusLED = LED_LCD_ON;
static uint8_t paramsLCD;

void PCF_Wr(uint8_t dato){
	//TWI_Start(DIR_PCF, 0, dato|statusLED );
	TWI_Start();
	TWI_Write(DIR_LCD|0);
	TWI_Write(dato|statusLED);
	TWI_Stop();
	
}

void loadPCF(uint8_t dato, uint8_t mode){
	
	switch(mode){
		case _DATA_   : dato |=  (1<<LCD_RS); break;
		case _COMMAND_: dato &= ~(1<<LCD_RS); break;
	}
	
	
	PCF_Wr(dato);
	dato |=  (1<<LCD_E);
	PCF_Wr(dato);
	dato &=  ~(1<<LCD_E);
	PCF_Wr(dato);
	
	_delay_us(30);
	
}
void sendDATA(uint8_t dato){
	uint8_t NibbleH, NibbleL;
	NibbleH = (dato & 0xF0);
	NibbleL = (dato & 0x0F)<<4;
	loadPCF(NibbleH,_DATA_);
	loadPCF(NibbleL,_DATA_);
}
void sendCMD(uint8_t cmd){
	uint8_t NibbleH, NibbleL;
	NibbleH =  cmd & 0xF0;
	NibbleL = (cmd & 0x0F)<<4;
	loadPCF(NibbleH,_COMMAND_);
	loadPCF(NibbleL,_COMMAND_);
}

void TWI_LCD_Init(void){
	
	PCF_Wr(0x00);
	_delay_ms(15);
	sendCMD(0x03);
	_delay_us(4100);
	sendCMD(0x03);
	_delay_us(100);
	sendCMD(0x03);
	sendCMD(0x02);
	
	sendCMD(_LCD_FUNTIONSET | _LCD_4BITMODE | _LCD_2LINE | _LCD_5x8DOTS);
	_delay_us(37);
	
	paramsLCD = _LCD_DISPLAY_ON | _LCD_CURSOR_ON | _LCD_BLINK_ON;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
	
	sendCMD(_LCD_CLEARDISPLAY);
	_delay_ms(2);
}
void TWI_LCD_Write(uint8_t letra){
	sendDATA(letra);
}
void TWI_LCD_Command(uint8_t cmd){
	sendCMD(cmd);
}

void TWI_LCD_Puts(char *str){
	
	while(*str){
		sendDATA(*str);
		str++;
	}
	
}
void TWI_LCD_Set_Cursor(uint8_t row, uint8_t col){
	static uint8_t local_mem[4]={0x00,0x40,0x14,0x54};
	sendCMD(_LCD_SET_DDRAM_ADDR | (local_mem[row-1]+(col-1) ) );
}

/*FUNCIONES DE LA LCD*/


void TWI_LCD_Backlight_On(void){
	statusLED=LED_LCD_ON;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	
}
void TWI_LCD_Backlight_Off(void){
	statusLED=LED_LCD_OFF;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	
}


void TWI_LCD_Clear(void){
	sendCMD(_LCD_CLEARDISPLAY);
	_delay_ms(2);
}

void TWI_LCD_Return_Home(void){
	sendCMD(_LCD_RETURNHOME);
	_delay_ms(2);
}

void TWI_LCD_Enable_Blink(void){
	paramsLCD |= _LCD_BLINK_ON;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
}
void TWI_LCD_Disable_Blink(void){
	paramsLCD &= ~_LCD_BLINK_ON;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
}

void TWI_LCD_Enable_Cursor(void){
	paramsLCD |= _LCD_CURSOR_ON;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
}
void TWI_LCD_Disable_Cursor(void){
	paramsLCD &= ~_LCD_CURSOR_ON;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
}

void TWI_LCD_On(void){
	paramsLCD |= _LCD_DISPLAY_ON ;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
}
void TWI_LCD_Off(void){
	paramsLCD &= ~_LCD_DISPLAY_ON ;
	sendCMD(_LCD_DISPLAYCONTROL | paramsLCD);
	_delay_us(37);
}

void TWI_LCD_Scroll_Left(void){
	sendCMD(_LCD_CURSORDISPLAYSHIFT | _LCD_DISPLAY_SHIFT | _LCD_MOVELEFT);
	_delay_us(37);
}
void TWI_LCD_Scroll_Right(void){
	sendCMD(_LCD_CURSORDISPLAYSHIFT | _LCD_DISPLAY_SHIFT | _LCD_MOVERIGHT);
	_delay_us(37);
}

void TWI_LCD_Custom_Char(uint8_t mem, uint8_t *charmap){
	sendCMD(_LCD_SET_CGRAM_ADDR | ( (mem&0b111)<<3) ) ;
	for(int i=0; i<=7; i++){
		sendDATA(charmap[i]);
	}
	sendCMD(_LCD_SET_DDRAM_ADDR);
	_delay_us(37);
}