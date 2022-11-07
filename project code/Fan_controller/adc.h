 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for ADC driver
 *
 * Author: Sarah Emil
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*definitions for ADC configurations */

 typedef enum
 {
  	AREF,AVCC,Internal=3
 }ADC_ReferenceVolatge;

 typedef enum
 {
  	FCLK_0,FCLK_2,FCLK_4,FCLK_8,FCLK_16,FCLK_32,
 	FCLK_64,FCLK_128
 }ADC_Prescaler;

typedef struct{
	 ADC_ReferenceVolatge ref_volt  ;
	 ADC_Prescaler prescaler;

}ADC_ConfigType;

/*
  * Description :
  * Function responsible for initialize the ADC driver.
  */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
