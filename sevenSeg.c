/*
 * sevenSeg.c
 *
 *  Created on: Jan 18, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "sevenSeg.h"
#include "sevenSegConfig.h"

/*- GLOBAL STATIC VARIABLES --------------------------------*/

static uint8_t gu8_sevenSeg0Status = LOW;
static uint8_t gu8_sevenSeg1Status = HIGH;

/*- APIs IMPLEMENTATION ------------------------------------*/

void sevenSegInit(En_SevenSegId_t a_segment_id)
{
	/* A switch-case statement to decide which 7seg to be initialized */
	switch(a_segment_id)
	{
	case SEG_0:
		gpioPinDirection(GPIOB, (BIT0 | BIT1 | BIT2 | BIT3), OUTPUT);
		gpioPinDirection(GPIOD, (BIT2 | BIT4), OUTPUT);
		gpioPinWrite(GPIOB, (BIT0 | BIT1 | BIT2 | BIT3), LOW);
		gpioPinWrite(GPIOD, BIT4, LOW);
		sevenSegDisable(SEG_0);
		break;
	case SEG_1:
		gpioPinDirection(GPIOB, (BIT0 | BIT1 | BIT2 | BIT3), OUTPUT);
		gpioPinDirection(GPIOD, (BIT3 | BIT4), OUTPUT);
		gpioPinWrite(GPIOB, (BIT0 | BIT1 | BIT2 | BIT3), LOW);
		gpioPinWrite(GPIOD, BIT4, LOW);
		sevenSegDisable(SEG_1);
		break;
	}
}

void sevenSegEnable(En_SevenSegId_t en_segment_id)
{
	/* A switch-case statement to decide which 7seg to be enabled */
	switch(en_segment_id)
	{
	case SEG_0:
		gpioPinWrite(GPIOD, BIT2, LOW);
		gu8_sevenSeg0Status = HIGH;
		break;
	case SEG_1:
		gpioPinWrite(GPIOD, BIT3, LOW);
		gu8_sevenSeg1Status = HIGH;
		break;
	}
}

void sevenSegDisable(En_SevenSegId_t en_segment_id)
{
	/* A switch-case statement to decide which 7seg to be disabled */
	switch(en_segment_id)
	{
	case SEG_0:
		gpioPinWrite(GPIOD, BIT2, HIGH);
		gu8_sevenSeg0Status = LOW;
		break;
	case SEG_1:
		gpioPinWrite(GPIOD, BIT3, HIGH);
		gu8_sevenSeg1Status = LOW;
		break;
	}
}

void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number)
{
	/* A switch-case statement to decide which 7seg to be written */
	switch(en_segment_id)
	{
	case SEG_0:
		if(gu8_sevenSeg0Status == HIGH)
		{
			gpioPortWrite(GPIOB, (GPIOB & 0xF0) | (u8_number & 0x0F));
		}
		break;
	case SEG_1:
		if(gu8_sevenSeg1Status == HIGH)
		{
			gpioPortWrite(GPIOB, (GPIOB & 0xF0) | (u8_number & 0x0F));
		}
		break;
	}
}
