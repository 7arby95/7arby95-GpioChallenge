/*
 * softwareDelay.c
 *
 *  Created on: Jan 17, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "softwareDelay.h"

/*- APIs IMPLEMENTATION ------------------------------------*/

void softwareDelayMs(uint32_t u32_delay_in_ms)
{
	/* 16 MHz */
	uint32_t ticks=2276, i, j;
	for(i=0 ; i<u32_delay_in_ms ; i++)
	{
		for(j=0 ; j<ticks ; j++);
	}
}
