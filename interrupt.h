/*
 * interrupt.h
 *
 *  Created on: Jan 22, 2020
 *      Author: Youssef Harby
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "registers.h"

#define EXTERNAL_INTERRUPT0					__vector_1
#define EXTERNAL_INTERRUPT1					__vector_2
#define EXTERNAL_INTERRUPT2					__vector_3

#define TIMER0_CTC_MODE_INTERRUPT			__vector_10
#define TIMER0_OVF_MODE_INTERRUPT			__vector_11

#define TIMER1_ICU_MODE_INTERRUPT			__vector_6
#define TIMER1_CTC_A_MODE_INTERRUPT			__vector_7
#define TIMER1_CTC_B_MODE_INTERRUPT			__vector_8
#define TIMER1_OVF_MODE_INTERRUPT			__vector_9

#define TIMER2_CTC_MODE_INTERRUPT			__vector_4
#define TIMER2_OVF_MODE_INTERRUPT			__vector_5

#define SPI_STC_INTERRUPT					__vector_12

#define USART_RXC_INTERRUPT					__vector_13
#define USART_UDRE_INTERRUPT				__vector_14
#define USART_TXC_INTERRUPT					__vector_15

#define ADC_INTERRUPT						__vector_16

#define EE_RDY_INTERRUPT					__vector_17

#define ANA_COMP_INTERRUPT					__vector_18

#define TWI_INTERRUPT						__vector_19

#define SPM_RDY_INTERRUPT					__vector_20


#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)


void EXTERNAL_INTERRUPT0 (void) __attribute__ ((signal, interrupt));
void EXTERNAL_INTERRUPT1 (void) __attribute__ ((signal, interrupt));
void EXTERNAL_INTERRUPT2 (void) __attribute__ ((signal, interrupt));
void TIMER0_CTC_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER0_OVF_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER1_ICU_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER1_CTC_A_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER1_CTC_B_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER1_OVF_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER2_CTC_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TIMER2_OVF_MODE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void SPI_STC_INTERRUPT (void) __attribute__ ((signal, interrupt));
void USART_RXC_INTERRUPT (void) __attribute__ ((signal, interrupt));
void USART_UDRE_INTERRUPT (void) __attribute__ ((signal, interrupt));
void USART_TXC_INTERRUPT (void) __attribute__ ((signal, interrupt));
void ADC_INTERRUPT (void) __attribute__ ((signal, interrupt));
void EE_RDY_INTERRUPT (void) __attribute__ ((signal, interrupt));
void ANA_COMP_INTERRUPT (void) __attribute__ ((signal, interrupt));
void TWI_INTERRUPT (void) __attribute__ ((signal, interrupt));
void SPM_RDY_INTERRUPT (void) __attribute__ ((signal, interrupt));


#endif /* INTERRUPT_H_ */
