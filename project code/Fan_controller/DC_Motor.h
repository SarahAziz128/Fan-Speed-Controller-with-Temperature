/*
 * DC_Motor.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Sara
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

typedef enum
{
	STOP , CW, A_CW  /*CW indicates the clockwise direction, while A_CW indicates the antio-clockwise direction*/

}DcMotor_State;

void DcMotor_init (void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /*DC_MOTOR_H_*/
