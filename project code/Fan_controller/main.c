/*
 * main.c
 *
 *  Created on: Oct 11, 2022
 *      Author: Sara
 */


#include "DC_Motor.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "adc.h"
#include <avr/io.h>



int main (void){
	LCD_init();
	DcMotor_init();
	ADC_ConfigType ADC_state ={Internal ,FCLK_8};
	ADC_init(&ADC_state);


	LCD_displayString("Fan is ");
	LCD_displayStringRowColumn(1,0,"Temp = ");

	while(1){
		uint8 temp = LM35_getTemperature() ;
		LCD_moveCursor(0,7);

		if (temp<30){
			DcMotor_Rotate(STOP,0);
			LCD_displayString("OFF");

		}
		else if (temp>=30 && temp <60){
			DcMotor_Rotate(CW,25);
			LCD_displayString("ON");

		}
		else if (temp>=60 && temp <90){
			DcMotor_Rotate(CW,50);
			LCD_displayString("ON");
		}
		else if (temp>=90 && temp <120){
			DcMotor_Rotate(CW,75);
			LCD_displayString("ON");
		}
		else {
			DcMotor_Rotate(CW,25);
			LCD_displayString("ON");
		}


		LCD_moveCursor(1,7);
		if (temp>=100)
		{
			LCD_intgerToString(temp);
		}
		else if(temp>=10)
		{
			LCD_intgerToString(temp);
			LCD_displayCharacter(" ");
		}
		else
		{
			LCD_intgerToString(temp);
			LCD_displayString("  ");

		}

	}

}

