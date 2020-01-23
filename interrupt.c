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

/* Global variables to manipulate when interrupts occur */
volatile static uint16_t gu16_global_interrupt_variable = 0;

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
//	global_variable++;
//	if(global_variable == 125)
//	{
//		Led_Toggle(LED_0);
//		global_variable = 0;
//	}
}

void TIMER2_OVF_MODE_INTERRUPT (void)
{
//	global_variable++;
//	timer2Set(6);
//	if(global_variable == 250)
//	{
//		Led_Toggle(LED_0);
//		global_variable = 0;
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
