/*
 * SwICU.c
 *
 *  Created on: Jan 29, 2020
 *      Author: Youssef Harby
 */


#include "SwICU.h"

#define INT2		5
#define INT0		6
#define INT1		7

volatile uint8_t gu8_swIcuRead = 0;
volatile uint8_t gu8_swIcuFlag = 0;

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
	timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_256, 0, 0, T0_POLLING);

	gpioPinDirection(GPIOB, BIT2, INPUT);
	gpioPinDirection(GPIOD, BIT0, OUTPUT);

	SET_BIT(GICR, INT2);
	MCUCSR = (MCUCSR & 0xBF) | a_en_inputCaptureEdge;

	sei();
}

EN_SwICU_Edge_t SwICU_GetCfgEdge(void)
{
	// BLANK Function
	return 0;
}

/*choose the detecting edge*/
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
	MCUCSR = (MCUCSR & 0xBF) | a_en_inputCaptureEdge;
}

void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
	*a_pu8_capt = timer0Read();
}

void SwICU_Stop(void)
{
	timer0Stop();
}

void SwICU_Start(void)
{
	timer0Start();
}

void SwICU_Enable(void)
{
	// BLANK Function
}

void SwICU_Disable(void)
{
	// BLANK Function
}
