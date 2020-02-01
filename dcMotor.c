/*
 * dcMotor.c
 *
 *  Created on: Jan 26, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "dcMotor.h"
#include "dcMotorConfig.h"
#include "timers.h"

/*- LOCAL MACROS -------------------------------------------*/

#define MOTOR_FREQUENCY 200

/*- APIs IMPLEMENTATION ------------------------------------*/

void MotorDC_Init(En_motorType_t en_motor_number)
{
	switch(en_motor_number)
	{
		case MOT_1:
			gpioPinDirection(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, OUTPUT);
			gpioPinDirection(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, OUTPUT);
			gpioPinDirection(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, OUTPUT);
			gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
			break;
		case MOT_2:
			gpioPinDirection(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, OUTPUT);
			gpioPinDirection(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, OUTPUT);
			gpioPinDirection(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, OUTPUT);
			gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, HIGH);
			break;
	}
}

void MotorDC_Dir(En_motorType_t en_motor_number, En_motorDir_t en_motor_dir)
{
	uint8_t motorGpio = 0;
	uint8_t motorBitA = 0;
	uint8_t motorBitB = 0;
	
	switch(en_motor_number)
	{
		case MOT_1:
			motorGpio = MOTOR_OUT_1A_GPIO;
			motorBitA = MOTOR_OUT_1A_BIT;
			motorBitB = MOTOR_OUT_1B_BIT;
			break;
		case MOT_2:
			motorGpio = MOTOR_OUT_2A_GPIO;
			motorBitA = MOTOR_OUT_2A_BIT;
			motorBitB = MOTOR_OUT_2B_BIT;
			break;
	}
	
	switch(en_motor_dir)
	{
		case STOP:
		gpioPinWrite(motorGpio, motorBitA, LOW);
		gpioPinWrite(motorGpio, motorBitB, LOW);
		switch(en_motor_number)
		{
			case MOT_1:
				gpioPinWrite(motorGpio, MOTOR_EN_1_BIT, LOW);
				break;
			case MOT_2:
				gpioPinWrite(motorGpio, MOTOR_EN_2_BIT, LOW);
				break;
		}
		break;
		
		case FORWARD:
		gpioPinWrite(motorGpio, motorBitA, LOW);
		gpioPinWrite(motorGpio, motorBitB, HIGH);
		break;
		
		case BACKWARD:
		gpioPinWrite(motorGpio, motorBitA, HIGH);
		gpioPinWrite(motorGpio, motorBitB, LOW);
		break;
	}
}

void MotorDC_Speed_PollingWithT0(uint8_t u8_motor_speed)
{
	timer0SwPWM(u8_motor_speed, MOTOR_FREQUENCY);
}

void MotorDC_Speed_HwPWM(uint8_t u8_motor_speed)
{
	
}