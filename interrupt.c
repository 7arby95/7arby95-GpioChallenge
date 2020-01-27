/*
 * interrupt.c
 *
 *  Created on: Jan 22, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "interrupt.h"
#include "led.h"
#include "timers.h"
#include "softwareDelay.h"

#define F_CPU 16000000UL

/* Global variables to manipulate when interrupts occur */
volatile static uint16_t gu16_globalInterruptVariable = 0;
volatile static uint16_t gu16_delayCounter = 0;
volatile static uint16_t gu8_flag = 0;
extern uint8_t gu8_dutyCycle;
extern uint8_t gu8_completionFlag;

/*- INTERRUPT APIs IMPLEMENTATION --------------------------*/

void EXTERNAL_INTERRUPT0 (void)
{

}

void EXTERNAL_INTERRUPT1 (void)
{

}

void EXTERNAL_INTERRUPT2 (void)
{

}

void TIMER0_CTC_MODE_INTERRUPT (void)
{
	/* A global interrupt variable used for controlling the motor speed every time the duty cycle changes */
	gu16_globalInterruptVariable++;
	
	if(gu16_globalInterruptVariable % 100 == (gu8_dutyCycle/3))
	{
		gpioPinWrite(GPIOD, BIT2, LOW);
		if(gu8_flag != 2)
			gpioPinWrite(GPIOD, BIT6, LOW);
		else
			gpioPinWrite(GPIOD, BIT7, LOW);
	}else if(gu16_globalInterruptVariable % 100 == 0)
	{
		gpioPinWrite(GPIOD, BIT2, HIGH);
		if(gu8_flag != 2)
			gpioPinWrite(GPIOD, BIT6, HIGH);
		else
			gpioPinWrite(GPIOD, BIT7, HIGH);
			
		gu16_globalInterruptVariable = 0;
	}

	if(gu8_completionFlag == 1)
	{
		cli();
	}

	gu16_delayCounter++;

	if(gu16_delayCounter == 540)
	{
		if(gu8_flag == 0)
			gu8_dutyCycle++;
		else if(gu8_flag == 1)
			gu8_dutyCycle--;
		else if(gu8_flag == 2)
			gu8_completionFlag = 1;
		gu16_delayCounter = 0;
	}

	if(gu8_dutyCycle >= 100 && gu8_flag == 0)
	{
		gu8_flag = 1;
	}
	else if(gu8_dutyCycle <= 0 && gu8_flag == 1)
	{
		gu8_flag = 2;
		gu8_dutyCycle = 60;
		gpioPinWrite(GPIOD, BIT6, LOW);
	}
}

void TIMER0_OVF_MODE_INTERRUPT (void)
{

}

void TIMER1_ICU_MODE_INTERRUPT (void)
{

}

void TIMER1_CTC_A_MODE_INTERRUPT (void)
{
//	Led_Toggle(LED_0);

gu16_globalInterruptVariable++;

if(gu16_globalInterruptVariable % 100 == (gu8_dutyCycle/3))
{
	gpioPinWrite(GPIOD, BIT2, LOW);
	if(gu8_flag != 2)
	gpioPinWrite(GPIOD, BIT6, LOW);
	else
	gpioPinWrite(GPIOD, BIT7, LOW);
}else if(gu16_globalInterruptVariable % 100 == 0)
{
	gpioPinWrite(GPIOD, BIT2, HIGH);
	if(gu8_flag != 2)
	gpioPinWrite(GPIOD, BIT6, HIGH);
	else
	gpioPinWrite(GPIOD, BIT7, HIGH);
	
	gu16_globalInterruptVariable = 0;
}

if(gu8_completionFlag == 1)
{
	cli();
}

gu16_delayCounter++;

if(gu16_delayCounter == 540)
{
	if(gu8_flag == 0)
	gu8_dutyCycle++;
	else if(gu8_flag == 1)
	gu8_dutyCycle--;
	else if(gu8_flag == 2)
	gu8_completionFlag = 1;
	gu16_delayCounter = 0;
}

if(gu8_dutyCycle >= 100 && gu8_flag == 0)
{
	gu8_flag = 1;
}
else if(gu8_dutyCycle <= 0 && gu8_flag == 1)
{
	gu8_flag = 2;
	gu8_dutyCycle = 60;
	gpioPinWrite(GPIOD, BIT6, LOW);
}
}

void TIMER1_CTC_B_MODE_INTERRUPT (void)
{
//	Led_Toggle(LED_0);
}

void TIMER1_OVF_MODE_INTERRUPT (void)
{
//	Led_Toggle(LED_0);
//	timer1Set(49911);
}

void TIMER2_CTC_MODE_INTERRUPT (void)
{
//	gu16_globalInterruptVariable++;
//	if(gu16_globalInterruptVariable == 125)
//	{
//		Led_Toggle(LED_0);
//		gu16_globalInterruptVariable = 0;
//	}

gu16_globalInterruptVariable++;

if(gu16_globalInterruptVariable % 100 == (gu8_dutyCycle/3))
{
	gpioPinWrite(GPIOD, BIT2, LOW);
	if(gu8_flag != 2)
	gpioPinWrite(GPIOD, BIT6, LOW);
	else
	gpioPinWrite(GPIOD, BIT7, LOW);
}else if(gu16_globalInterruptVariable % 100 == 0)
{
	gpioPinWrite(GPIOD, BIT2, HIGH);
	if(gu8_flag != 2)
	gpioPinWrite(GPIOD, BIT6, HIGH);
	else
	gpioPinWrite(GPIOD, BIT7, HIGH);
	
	gu16_globalInterruptVariable = 0;
}

if(gu8_completionFlag == 1)
{
	cli();
}

gu16_delayCounter++;

if(gu16_delayCounter == 540)
{
	if(gu8_flag == 0)
	gu8_dutyCycle++;
	else if(gu8_flag == 1)
	gu8_dutyCycle--;
	else if(gu8_flag == 2)
	gu8_completionFlag = 1;
	gu16_delayCounter = 0;
}

if(gu8_dutyCycle >= 100 && gu8_flag == 0)
{
	gu8_flag = 1;
}
else if(gu8_dutyCycle <= 0 && gu8_flag == 1)
{
	gu8_flag = 2;
	gu8_dutyCycle = 60;
	gpioPinWrite(GPIOD, BIT6, LOW);
}
}

void TIMER2_OVF_MODE_INTERRUPT (void)
{
//	gu16_globalInterruptVariable++;
//	timer2Set(6);
//	if(gu16_globalInterruptVariable == 250)
//	{
//		Led_Toggle(LED_0);
//		gu16_globalInterruptVariable = 0;
//	}
}

void SPI_STC_INTERRUPT (void)
{

}

void USART_RXC_INTERRUPT (void)
{

}

void USART_UDRE_INTERRUPT (void)
{

}

void USART_TXC_INTERRUPT (void)
{

}

void ADC_INTERRUPT (void)
{

}

void EE_RDY_INTERRUPT (void)
{

}

void ANA_COMP_INTERRUPT (void)
{

}

void TWI_INTERRUPT (void)
{

}

void SPM_RDY_INTERRUPT (void)
{

}
