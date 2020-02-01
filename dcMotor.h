/*
 * MotorDC.h
 *
 *  Created on: Oct 26, 2019
 *      Author: Sprints
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

/*- INCLUDES ------------------------------------------------*/

#include "timers.h"

/*- ENUMS ---------------------------------------------------*/

typedef enum En_motorType_t{
	MOT_1,
	MOT_2
}En_motorType_t;

typedef enum En_motorDir_t{
	STOP,
	FORWARD,
	BACKWARD
}En_motorDir_t;

/*- FUNCTION DECLARATIONS -----------------------------------*/

/**
 * Description: A function to initialize the selected motor
 * @param en_motor_number: selects which motor to initialize
 */
void MotorDC_Init(En_motorType_t en_motor_number);

/**
 * Description: A function to select the direction for the selected motor
 * @param en_motor_number: selects which motor to control its direction
 * @param en_motor_dir: selects the suitable motor direction
 */
void MotorDC_Dir(En_motorType_t en_motor_number, En_motorDir_t en_motor_dir);

/**
 * Description: A function to control the speed of the motor
 * @param u8_motor_speed: sets the percentage of speed at which the motor will operate
 */
void MotorDC_Speed_PollingWithT0(uint8_t u8_motor_speed);

/**
 * Description: set the port value (which is PORT register)
 * @param 
 */
void MotorDC_Speed_HwPWM(uint8_t u8_motor_speed);

#endif /* MOTORDC_H_ */
