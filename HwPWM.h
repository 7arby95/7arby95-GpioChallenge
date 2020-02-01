/*
 * HwPWM.h
 *
 *  Created on: Oct 28, 2019
 *      Author: Think
 */

#ifndef HWPWM_H_
#define HWPWM_H_

/*- INCLUDES ------------------------------------------------*/

#include "timers.h"

/*- FUNCTION DECLARATIONS -----------------------------------*/

/**
 * Description: Initializes the PWM module using timer1
 */
void HwPWMInit(void);

/**
 * Description: Selects the duty cycle and the frequency for generated PWM wave
 */
void HwPWMSetDuty(uint8_t a_u8_duty, uint32_t a_u32_frequency);

#endif /* HWPWM_H_ */
