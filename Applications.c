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
#include "dcMotor.h"
#include "SwICU.h"
#include "HwPWM.h"

#define MOT_FREQ			100
#define OBSTACLE_DISTANCE	10

#define	WAVE_SEND(); { \
	gpioPinWrite(GPIOD, BIT0, HIGH); \
	timer2DelayMs(1); \
	gpioPinWrite(GPIOD, BIT0, LOW); \
}

volatile uint8_t gu8_completionFlag = 0;
volatile uint8_t gu8_dutyCycle = 0;

extern uint8_t gu8_swIcuRead;
extern uint8_t gu8_swIcuFlag;

/*		ICU 4 leds application
int main(void)
{
	uint8_t u8_swIcuVariable = 0;
	
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	
	SwICU_Init(SwICU_EdgeRising);
	
	while(1)
	{
		softwareDelayMs(200);
		
		if(gu8_swIcuFlag)
		{
			u8_swIcuVariable = gu8_swIcuRead * 0.544;
			
			gpioPinWrite(GPIOD, BIT0, HIGH);
			timer2DelayMs(1);
			gpioPinWrite(GPIOD, BIT0, LOW);
			
			gu8_swIcuFlag = 0;
		}
		
		PORTB_DATA = (PORTB_DATA & 0x0F) | (u8_swIcuVariable << 4);
	}
}
*/

/* HwPWM and SwICU application (stop in case of an obstacle ahead) */

int main(void)
{
	uint8_t u8_swIcuDistance = 0;
	uint8_t u8_dutyCycle = 0;
	
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);
	
	SwICU_Init(SwICU_EdgeRising);

	u8_dutyCycle = 20;

	HwPWMInit();
	HwPWMSetDuty(u8_dutyCycle, MOT_FREQ);

	while(1)
	{
		softwareDelayMs(100);

		if(gu8_swIcuFlag)
		{
			u8_swIcuDistance = gu8_swIcuRead * 0.544;
			
			if(u8_swIcuDistance <= OBSTACLE_DISTANCE)
			{
				MotorDC_Dir(MOT_1, STOP);
				MotorDC_Dir(MOT_2, STOP);
			}else
			{
				MotorDC_Dir(MOT_1, FORWARD);
				MotorDC_Dir(MOT_2, FORWARD);
			}
			
			WAVE_SEND();

			gu8_swIcuFlag = 0;
		}
	}
}

/*- ENUMS --------------------------------------------------*/

/*
typedef enum En_GpioReq9State_t{
	GO,
	STOP,
	GET_READY
}En_GpioReq9State_t;
*/

/*- APIs PROTOTYPES ----------------------------------------*/

//void GPIO_REQ7(void);
//void GPIO_REQ8(void);
//void GPIO_REQ9(void);

/*- APIs IMPLEMENTATION ------------------------------------*/

/*
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
*/

/*
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
*/

/*
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
*/

/*
 * MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	
	gu8_dutyCycle = 0;

	MotorDC_Speed_PollingWithT0(gu8_dutyCycle);

	while(1)
	{
		if(gu8_completionFlag == 1)
		{
			softwareDelayMs(500);
			MotorDC_Dir(MOT_1, STOP);
			MotorDC_Dir(MOT_2, STOP);
		}
	}
 */
