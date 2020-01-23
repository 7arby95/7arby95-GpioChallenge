/*
 * Applications.c
 *
 *  Created on: Jan 18, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "gpio.h"
#include "softwareDelay.h"
#include "led.h"
#include "pushButton.h"
#include "sevenSeg.h"
#include "timers.h"
#include "interrupt.h"

/*- ENUMS --------------------------------------------------*/

typedef enum En_GpioReq9State_t{
	GO,
	STOP,
	GET_READY
}En_GpioReq9State_t;

/*- APIs IMPLEMENTATION ------------------------------------*/

void GPIO_REQ7(void)
{
	uint8_t u8_countUpCounter = 0;
	uint32_t u32_delayCounter = 0;

	sevenSegInit(SEG_0);
	sevenSegInit(SEG_1);

	while(1)
	{
		while(u8_countUpCounter <= 99)
		{
			sevenSegEnable(SEG_0);
			sevenSegWrite(SEG_0, ((u8_countUpCounter / 10) % 10));
			softwareDelayMs(1);
			sevenSegDisable(SEG_0);

			sevenSegEnable(SEG_1);
			sevenSegWrite(SEG_1, (u8_countUpCounter % 10));
			softwareDelayMs(1);
			sevenSegDisable(SEG_1);

			u32_delayCounter++;

			if(u32_delayCounter % 469 == 0)
				u8_countUpCounter++;
		}
	}
}

void GPIO_REQ8(void)
{
	uint8_t u8_appCounter = 0, u8_delayDivider = 20;

	Led_Init(LED_1);
	pushButtonInit(BTN_1);

	while(1)
	{
		u8_delayDivider = 20;
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			while(pushButtonGetStatus(BTN_1) != Released);
			u8_appCounter++;
			while(u8_appCounter > 0)
			{
				Led_On(LED_1);
				while(u8_delayDivider > 0)
				{
					softwareDelayMs(49);
					if(pushButtonGetStatus(BTN_1) == Pressed)
					{
						softwareDelayMs(300);
						u8_delayDivider += 14;
					}
					u8_delayDivider--;
				}
				Led_Off(LED_1);
				u8_appCounter--;
			}
			break;
		}
	}
}

void GPIO_REQ9(void)
{
	uint8_t u8_currentState = GO;

	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	while(1)
	{
		switch(u8_currentState)
		{
		case GO:
			Led_On(LED_1);
			Led_Off(LED_2);
			Led_Off(LED_3);
			u8_currentState = STOP;
			break;
		case STOP:
			Led_Off(LED_1);
			Led_On(LED_2);
			Led_Off(LED_3);
			u8_currentState = GET_READY;
			break;
		case GET_READY:
			Led_Off(LED_1);
			Led_Off(LED_2);
			Led_On(LED_3);
			u8_currentState = GO;
			break;
		}
		softwareDelayMs(1000);
	}
}

int main(void)
{


	while(1)
	{

	}
}
