/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Sarah Emil
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */


/* though defined in header file they refuse to be declared here??? */



void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose an internal reference voltage 2.56 v
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 * ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125 Khz --> ADC must operate in range 50-200Khz
	 */
	switch(Config_Ptr->ref_volt)
	{
	case AREF:
		ADMUX = 0;
		break;
	case AVCC:
		SET_BIT(ADMUX,REFS0);
		break;
	case Internal:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}

	switch(Config_Ptr->prescaler)
	{
	case FCLK_0:
	case FCLK_2:
		SET_BIT(ADCSRA,ADPS0);
		break;
	case FCLK_4:
		SET_BIT(ADCSRA,ADPS1);
		break;
	case FCLK_8:
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		break;
	case FCLK_16:
		SET_BIT(ADCSRA,ADPS2);
		break;
	case FCLK_32:
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS2);
		break;
	case FCLK_64:
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
	case FCLK_128:
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;

	}

}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */

}