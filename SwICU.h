/*
 * SwICU.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Sprints
 */

#ifndef SWICU_H_
#define SWICU_H_

/*- INCLUDES ------------------------------------------------*/

#include "interrupt.h"
#include "timers.h"
#include "softwareDelay.h"

/*- ENUMS ---------------------------------------------------*/

typedef enum EN_SwICU_Edge_t{
	SwICU_EdgeFalling = 0,
	SwICU_EdgeRising = 0x40
}EN_SwICU_Edge_t;

/*- FUNCTION DECLARATIONS -----------------------------------*/

/**
 * Description: Initializes the Software ICU module
 */
void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge);

/**
 * Description: 
 */
EN_SwICU_Edge_t SwICU_GetCfgEdge(void);

/**
 * Description: Changes the next edge detection type
 */
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdge);

/**
 * Description: Reads the timer/counter current value
 */
void SwICU_Read(volatile uint8_t * a_pu8_capt);

/**
 * Description: Stops the timer counter
 */
void SwICU_Stop(void);

/**
 * Description: Starts the timer counter
 */
void SwICU_Start(void);

/**
 * Description: 
 */
void SwICU_Enable(void);

/**
 * Description: 
 */
void SwICU_Disable(void);

#endif /* SWICU_H_ */
