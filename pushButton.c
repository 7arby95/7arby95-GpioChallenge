/*
 * pushButton.c
 *
 *  Created on: Jan 17, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "pushButton.h"
#include "pushButtonConfig.h"

/*- APIs IMPLEMENTATION ------------------------------------*/

void pushButtonInit(En_buttonId_t en_button_id)
{
	/* A switch-case statement to decide which push button to be initialized */
	switch(en_button_id)
	{
	case BTN_0:
		gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, INPUT);
		break;
	case BTN_1:
		gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, INPUT);
		break;
	case BTN_2:

		break;
	case BTN_3:

		break;
	default:

		break;
	}
}

void pushButtonUpdate(void)
{
	/* Postponed */
}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_button_id)
{
	/* A switch-case statement to decide which push button to read its status (pressed or released) */
	switch(en_button_id)
	{
	case BTN_0:
		if(gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
		{
			softwareDelayMs(20);
			if(gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
			{
				return Pressed;
			}else
			{
				return Released;
			}
		}else
		{
			return Released;
		}
		break;
	case BTN_1:
		if(gpioPinRead(BTN_1_GPIO, BTN_1_BIT))
		{
			softwareDelayMs(20);
			if(gpioPinRead(BTN_1_GPIO, BTN_1_BIT))
			{
				return Pressed;
			}else
			{
				return Released;
			}
		}else
		{
			return Released;
		}
		break;
	case BTN_2:
		return ERROR;
		break;
	case BTN_3:
		return ERROR;
		break;
	default:
		return ERROR;
		break;
	}
}
