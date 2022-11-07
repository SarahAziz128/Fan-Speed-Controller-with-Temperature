/*
 * PWM_driver.c
 *
 *  Created on: Oct 11, 2022
 *      Author: Sara
 */


#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include <avr/io.h>
#include "PWM_driver.h"
#include "gpio.h"


void Timer0_PWM_Init(unsigned char set_duty_cycle)
{
	TCNT0 = 0; // Set Timer Initial Value to 0

	/* configure the timer
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	OCR0  = set_duty_cycle;

	GPIO_setupPinDirection(PORTB, PIN3, PIN_OUTPUT); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
}
