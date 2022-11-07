/*
 * DC_Motor.c
 *
 *  Created on: Oct 11, 2022
 *      Author: Sara
 */
#include "DC_Motor.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>
#include "PWM_driver.h"

/*typedef enum
{
	STOP,CW,A_CW  CW indicates the clockwise direction, while A_CW indicates the antio-clockwise direction
}DcMotor_State;*/


/*description :
 * void function that initializes the DC motor
 * INT1 of the driver is connected to PB0
 * INT2 of the driver is connected to PB1
 * EN of the driver is connected to PB3
 */

void DcMotor_init (void){
	GPIO_setupPortDirection(PORTB, PORT_OUTPUT); /* Set port direction as output */
	GPIO_writePort(PORTB,0xFC);                 /*stop the motor at the beginning*/
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch (speed) {
	case 25:
		Timer0_PWM_Init(64);
		break;
	case 50:
		Timer0_PWM_Init(128);
		break;
	case 75:
		Timer0_PWM_Init(192);
		break;
	case 100:
		Timer0_PWM_Init(255);
		break;

	}
	switch (state) {
	case STOP :
		GPIO_writePin(PORTB, PIN0, LOGIC_LOW);
		GPIO_writePin(PORTB, PIN1, LOGIC_LOW);
		break;

	case CW :
		GPIO_writePin(PORTB, PIN0, LOGIC_LOW);
		GPIO_writePin(PORTB, PIN1, LOGIC_HIGH);
		break;

	case A_CW :
		GPIO_writePin(PORTB, PIN0, LOGIC_HIGH);
		GPIO_writePin(PORTB, PIN1, LOGIC_LOW);
		break;
	}
}
