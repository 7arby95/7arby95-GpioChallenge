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

/*- LOCAL MACROS -------------------------------------------*/

#define MOT_FREQ			100
#define OBSTACLE_DISTANCE	15

/*- FUNCTION-LIKE MACROS -----------------------------------*/

#define	WAVE_SEND(); { \
	gpioPinWrite(GPIOD, BIT0, HIGH); \
	timer2DelayMs(1); \
	gpioPinWrite(GPIOD, BIT0, LOW); \
}

/*- GLOBAL EXTERN VARIABLES --------------------------------*/

volatile uint8_t gu8_completionFlag = 0;
volatile uint8_t gu8_dutyCycle = 0;

extern uint8_t gu8_swIcuRead;
extern uint8_t gu8_swIcuFlag;


/* ICU 4 leds application */

/*
int main(void)
{
	/ * A variable to store the distance between the ultrasonic sensor and the obstacle * /
	uint8_t u8_swIcuDistance = 0;
	
	/ * Initialize the four leds to represent the current distance between the sensor and the obstacle * /
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	
	/ * Initialize the Software ICU module * /
	SwICU_Init(SwICU_EdgeRising);
	
	while(1)
	{
		/ * A software delay of 200 milliseconds to avoid leds flickering * /
		softwareDelayMs(200);
		
		/ * When the previous operation is done * /
		if(gu8_swIcuFlag)
		{
			/ * An equation to calculate the distance * /
			u8_swIcuDistance = gu8_swIcuRead * 0.544;
			
			/ * Send the trigger signal each time the previous wave is read * /
			WAVE_SEND();
			
			/ * clear the flag when the trigger signal is sent * /
			gu8_swIcuFlag = 0;
		}
		
		/ * Displays the distance on the leds as binary * /
		PORTB_DATA = (PORTB_DATA & 0x0F) | (u8_swIcuDistance << 4);
	}
}
*/



/* HwPWM and SwICU application (stop in case of an obstacle ahead) */

int main(void)
{
	/* A variable to store the distance between the ultrasonic sensor and the obstacle */
	uint8_t u8_swIcuDistance = 0;
	/* A variable to store the value of the duty cycle at which the motor will operate */
	uint8_t u8_dutyCycle = 0;
	
	/* Initialization of the two motors along with their initial direction */
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);
	
	/* Initialization of the ICU driver with detecting the rising edge as the first detection case */
	SwICU_Init(SwICU_EdgeRising);

	/* Sets the duty cycle to the required value */
	u8_dutyCycle = 20;
	
	/* Initializes the PWM signal at a suitable frequency and duty cycle */
	HwPWMInit();
	HwPWMSetDuty(u8_dutyCycle, MOT_FREQ);

	while(1)
	{
		softwareDelayMs(50);
		
		/* When the previous operation is done */
		if(gu8_swIcuFlag)
		{
			/* An equation to calculate the distance */
			u8_swIcuDistance = gu8_swIcuRead * 0.544;
			
			/* If condition to stop the car in case of an obstacle ahead */
			if(u8_swIcuDistance <= OBSTACLE_DISTANCE)
			{
				MotorDC_Dir(MOT_1, STOP);
				MotorDC_Dir(MOT_2, STOP);
			}else
			{
				MotorDC_Dir(MOT_1, FORWARD);
				MotorDC_Dir(MOT_2, FORWARD);
			}
			
			/* Send the trigger signal each time the previous wave is read */
			WAVE_SEND();

			/* clear the flag when the trigger signal is sent */
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
