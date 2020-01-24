/*
 * timers.c
 *
 *  Created on: Jan 20, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "timers.h"

/* Register TCCR0 bit definitions */
#define FOC0 		7
#define WGM00 		6
#define COM01 		5
#define COM00 		4
#define WGM01		3
#define CS02		2
#define CS01		1
#define CS00		0

/* Registers TCCR1A & TCCR1B bit definitions */
#define COM1A1		7
#define COM1A0		6
#define COM1B1		5
#define COM1B0		4
#define FOC1A		3
#define FOC1B		2
#define WGM11		1
#define WGM10		0
#define ICNC1		7
#define ICES1		6
#define WGM13		4
#define WGM12		3
#define CS12		2
#define CS11		1
#define CS10		0

/* Register TCCR2 bit definitions */
#define FOC2 		7
#define WGM20 		6
#define COM21 		5
#define COM20 		4
#define WGM21		3
#define CS22		2
#define CS21		1
#define CS20		0

/* Register TIFR bit definitions */
#define TOV0		0
#define OCF0		1
#define TOV1		2
#define OCF1B		3
#define OCF1A		4
#define ICF1		5
#define TOV2		6
#define OCF2		7

#define TIMER_MS_DIVISION_FACTOR		64000
#define TIMER_US_DIVISION_FACTOR		1000000

/*- GLOBAL STATIC VARIABLES --------------------------------*/

/* Global variables to hold the prescaler values: one for both timer0 and timer1 as they share the prescaler and one for timer2 */
static uint8_t gu8_timer0Timer1PreScaler = 0;
static uint8_t gu8_timer2PreScaler = 0;

/*- APIs IMPLEMENTATION ------------------------------------*/

void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
{
	/* Non-PWM mode */
	SET_BIT(TCCR0, FOC0);

	/* Set the required operating mode */
	TCCR0 = (TCCR0 & 0xB7) | (en_mode);

	/* Set the compare match output mode */
	TCCR0 = (TCCR0 & 0xCF) | (en_OC0);

	/* Set the pre-scaler */
	gu8_timer0Timer1PreScaler = en_prescal;

	/* Set the timer/counter0 initial value */
	TCNT0 = u8_initialValue;

	/* Set the timer/counter0 CTC mode compare value */
	OCR0 = u8_outputCompare;

	/* Enable the interrupt corresponding to the mode */
	TIMSK = (TIMSK & 0xFC) | (en_interruptMask);
}

void timer0Set(uint8_t u8_value)
{
	/* Set the timer/counter0 custom value */
	TCNT0 = u8_value;
}

uint8_t timer0Read(void)
{
	/* Read the counter register */
	return TCNT0;
}

void timer0Start(void)
{
	/* Provide suitable clock to the timer according to the chosen prescaler value */
	TCCR0 = (TCCR0 & 0xF8) | (gu8_timer0Timer1PreScaler);
	/* Set the timer/counter0 initial value to zero */
	TCNT0 = 0;
}

void timer0Stop(void)
{
	/* disable the timer clock */
	TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
}

void timer0DelayMs(uint16_t u16_delay_in_ms)
{
	uint16_t u16_msCounter = 0;
	uint8_t u8_outputCompare = F_CPU / TIMER_MS_DIVISION_FACTOR;

	timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_64, 0, 0, T0_POLLING);
	timer0Start();

	for(u16_msCounter=0 ; u16_msCounter < u16_delay_in_ms ; u16_msCounter++)
	{
		while(TCNT0 < u8_outputCompare);
		TCNT0 = 0;
	}
}

void timer0DelayUs(uint32_t u32_delay_in_us)
{
	uint32_t u32_usCounter = 0;
	uint8_t u8_outputCompare = F_CPU / TIMER_US_DIVISION_FACTOR;

	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_NO, 0, u8_outputCompare, T0_POLLING);
	timer0Start();

	for(u32_usCounter=0 ; u32_usCounter < u32_delay_in_us ; u32_usCounter++)
	{
		while(BIT_IS_CLEAR(TIFR, OCF0));
		SET_BIT(TIFR, OCF0);
		TCNT0 = 0;
	}
}

void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{

}

/*
 ********************************************************************************************************************************************************
 */

void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC1,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask)
{
	/* Non-PWM mode */
	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);

	TCCR1 = 0x0000;

	/* Set the required operating mode */
	TCCR1 = en_mode | en_OC1;

	/* Set the pre-scaler */
	gu8_timer0Timer1PreScaler = en_prescal;

	/* Set the timer/counter0 initial value */
	TCNT1 = u16_initialValue;

	/* Set the timer/counter0 CTC mode compare value */
	OCR1A = u16_outputCompareA;
	OCR1B = u16_outputCompareB;

	/* Enable the interrupt corresponding to the mode */
	TIMSK = (TIMSK & 0xC3) | (en_interruptMask);
}

void timer1Set(uint16_t u16_value)
{
	/* Set the timer/counter1 custom value */
	TCNT1 = u16_value;
}

uint16_t timer1Read(void)
{
	/* Read the counter register */
	return TCNT1;
}

void timer1Start(void)
{
	/* Provide suitable clock to the timer according to the chosen prescaler value */
	TCCR1B = (TCCR1B & 0xF8) | (gu8_timer0Timer1PreScaler);
	/* Set the timer/counter0 initial value to zero */
	TCNT1 = 0;
}

void timer1Stop(void)
{
	/* disable the timer clock */
	TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
}

void timer1DelayMs(uint16_t u16_delay_in_ms)
{
	uint16_t u16_msCounter = 0;
	uint16_t u16_outputCompare = F_CPU / TIMER_MS_DIVISION_FACTOR;

	timer1Init(T1_NORMAL_MODE, T1_OC1_DIS, T1_PRESCALER_64, 0, 0, 0, 0, T1_POLLING);
	timer1Start();

	for(u16_msCounter=0 ; u16_msCounter < u16_delay_in_ms ; u16_msCounter++)
	{
		while(TCNT1 < u16_outputCompare);
		TCNT1 = 0;
	}
}

void timer1DelayUs(uint32_t u32_delay_in_us)
{
	uint32_t u32_usCounter = 0;
	uint16_t u16_outputCompare = F_CPU / TIMER_US_DIVISION_FACTOR;

	timer1Init(T1_COMP_MODE_OCR1A_TOP, T1_OC1_DIS, T1_PRESCALER_NO, 0, u16_outputCompare, 0, 0, T1_POLLING);
	timer1Start();

	for(u32_usCounter=0 ; u32_usCounter < u32_delay_in_us ; u32_usCounter++)
	{
		while(BIT_IS_CLEAR(TIFR, OCF1A));
		SET_BIT(TIFR, OCF1A);
		TCNT1 = 0;
	}
}

void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{

}

/*
 ********************************************************************************************************************************************************
 */

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC2,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask)
{
	/* Non-PWM mode */
	SET_BIT(TCCR2, FOC2);

	/* Set the required operating mode */
	TCCR2 = (TCCR2 & 0xB7) | (en_mode);

	/* Set the compare match output mode */
	TCCR2 = (TCCR2 & 0xCF) | (en_OC2);

	/* Set the pre-scaler */
	gu8_timer2PreScaler = en_prescal;

	/* Set the timer/counter0 initial value */
	TCNT2 = u8_initialValue;

	/* Set the timer/counter0 CTC mode compare value */
	OCR2 = u8_outputCompare;

	/* Enable the interrupt corresponding to the mode */
	TIMSK = (TIMSK & 0x3F) | (en_interruptMask);
}

void timer2Set(uint8_t u8_value)
{
	/* Set the timer/counter2 custom value */
	TCNT2 = u8_value;
}

uint8_t timer2Read(void)
{
	/* Read the counter register */
	return TCNT2;
}

void timer2Start(void)
{
	/* Provide suitable clock to the timer according to the chosen prescaler value */
	TCCR2 = (TCCR2 & 0xF8) | (gu8_timer2PreScaler);
	/* Set the timer/counter0 initial value to zero */
	TCNT2 = 0;
}

void timer2Stop(void)
{
	/* disable the timer clock */
	TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));
}

void timer2DelayMs(uint16_t u16_delay_in_ms)
{
	uint16_t u16_msCounter = 0;
	uint8_t u8_outputCompare = F_CPU / TIMER_MS_DIVISION_FACTOR;

	timer2Init(T2_NORMAL_MODE, T2_OC2_DIS, T2_PRESCALER_64, 0, 0, 0, T2_POLLING);
	timer2Start();

	for(u16_msCounter=0 ; u16_msCounter < u16_delay_in_ms ; u16_msCounter++)
	{
		while(TCNT2 < u8_outputCompare);
		TCNT2 = 0;
	}
}

void timer2DelayUs(uint32_t u32_delay_in_us)
{
	uint32_t u32_usCounter = 0;
	uint8_t u8_outputCompare = F_CPU / TIMER_US_DIVISION_FACTOR;

	timer2Init(T2_COMP_MODE, T2_OC2_DIS, T2_PRESCALER_NO, 0, u8_outputCompare, 0, T2_POLLING);
	timer2Start();

	for(u32_usCounter=0 ; u32_usCounter < u32_delay_in_us ; u32_usCounter++)
	{
		while(BIT_IS_CLEAR(TIFR, OCF2));
		SET_BIT(TIFR, OCF2);
		TCNT2 = 0;
	}
}

void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{

}
