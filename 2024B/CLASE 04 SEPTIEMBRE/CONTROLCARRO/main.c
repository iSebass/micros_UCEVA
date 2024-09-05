#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_DDR  DDRD
#define MOTOR_PORT PORTD
#define BTN_DDR  DDRB
#define BTN_PIN  PINB

#define BTN_L 0
#define BTN_R 1
#define BTN_U 2
#define BTN_D 3

#define IN1 0
#define IN2 1
#define IN3 2
#define IN4 3

#define getBTN_Up()    ( ( BTN_PIN & (1<<BTN_U) ) != 0 ? 1:0 )
#define getBTN_Down()  ( ( BTN_PIN & (1<<BTN_D) ) != 0 ? 1:0 )
#define getBTN_Right() ( ( BTN_PIN & (1<<BTN_R) ) != 0 ? 1:0 )
#define getBTN_Left()  ( ( BTN_PIN & (1<<BTN_L) ) != 0 ? 1:0 )

void Motor_Forward(){
	MOTOR_PORT &= ~( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
	MOTOR_PORT |=  ( (1<<IN2)|(1<<IN3) );
}
void Motor_Backward(){
	MOTOR_PORT &= ~( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
	MOTOR_PORT |=  ( (1<<IN1)|(1<<IN4) );
}
void Motor_Turn_Right(){
	MOTOR_PORT &= ~( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
	MOTOR_PORT |=  ( (1<<IN2) );
}
void Motor_Turn_Left(){
	MOTOR_PORT &= ~( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
	MOTOR_PORT |=  ( (1<<IN3) );
}
void Motor_Stop(){
	MOTOR_PORT &= ~( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
}

int main(void)
{
	BTN_DDR   &= ~( (1<<BTN_L)|(1<<BTN_D)|(1<<BTN_R)|(1<<BTN_U) );
    MOTOR_DDR |= ( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
	MOTOR_PORT &= ~( (1<<IN1)|(1<<IN2)|(1<<IN3)|(1<<IN4) );
	Motor_Turn_Left();
    while (1) 
    {
		if( getBTN_Up() == 1 ){
			Motor_Forward();
		}
		else if(getBTN_Down() == 1){
			Motor_Backward();
		}
		else if(getBTN_Left()==1){
			Motor_Turn_Left();
		}
		else if(getBTN_Right() == 1){
			Motor_Turn_Right();
		}
		
		_delay_ms(50);
    }
}

