/*
 * timers.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Sprints
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "common_macros.h"
#include "registers.h"
#include "gpio.h"

/*
 * User Configuration Macros
 */

#define T0_PWM_GPIO	GPIOD
#define T0_PWM_BIT	BIT0

#define T1_PWM_GPIO	GPIOD
#define T1_PWM_BIT	BIT1

#define T2_PWM_GPIO GPIOD
#define T2_PWM_BIT	BIT2

typedef enum En_timer0Mode_t{
	T0_NORMAL_MODE=0,T0_COMP_MODE=0x08
}En_timer0Mode_t;

typedef enum En_timer0OC_t{
	T0_OC0_DIS=0,T0_OC0_TOGGLE=0x10,T0_OC0_CLEAR=0x20,T0_OC0_SET=0x30
}En_timer0OC_t;

typedef enum En_timer0perscaler_t{
	T0_NO_CLOCK=0,T0_PRESCALER_NO=0x01,T0_PRESCALER_8=0x02,T0_PRESCALER_64=0x03,T0_PRESCALER_256=0x04,T0_PRESCALER_1024=0x05
}En_timer0perscaler_t;

typedef enum En_timer0Interrupt_t{
	T0_POLLING=0,T0_INTERRUPT_NORMAL=0x01,T0_INTERRUPT_CMP=0x02
}En_timer0Interrupt_t;





// for timer 1
typedef enum En_timer1Mode_t{
	T1_NORMAL_MODE=0x0000,T1_COMP_MODE_OCR1A_TOP=0x0008, T1_COMP_MODE_ICR1_TOP = 0x0018

}En_timer1Mode_t;
typedef enum En_timer1OC_t{
	T1_OC1_DIS=0,T1_OC1A_TOGGLE=0x4000,T1_OC1B_TOGGLE=0x1000,T1_OC1A_CLEAR=0x8000,T1_OC1B_CLEAR=0x2000,T1_OC1A_SET=0xC000,T1_OC1B_SET=0x3000
}En_timer1OC_t;

typedef enum En_timer1perscaler_t{
	T1_NO_CLOCK=0x0000,T1_PRESCALER_NO=0x0001,T1_PRESCALER_8=0x0002,T1_PRESCALER_64=0x0003,T1_PRESCALER_256=0x0004,T1_PRESCALER_1024=0x0005
}En_timer1perscaler_t;

typedef enum En_timer1Interrupt_t{
	T1_POLLING=0,T1_INTERRUPT_NORMAL=0x04,T1_INTERRUPT_CMP_1B=0x08, T1_INTERRUPT_CMP_1A=0x10, T1_INTERRUPT_ICAPTURE = 0x20
}En_timer1Interrupt_t;




// for timer 2
typedef enum En_timer2Mode_t{
	T2_NORMAL_MODE=0,T2_COMP_MODE=0x08
}En_timer2Mode_t;

typedef enum En_timer2OC_t{
	T2_OC2_DIS=0,T2_OC2_TOGGLE=0x10,T2_OC2_CLEAR=0x20,T2_OC2_SET=0x30
}En_timer2OC_t;

typedef enum En_timer2perscaler_t{
	T2_NO_CLOCK=0,T2_PRESCALER_NO=0x01,T2_PRESCALER_8=0x02, T2_PRESCALER_32=0x03, T2_PRESCALER_64=0x04, T2_PRESCALER_128=0x05, T2_PRESCALER_256 = 0x06, T2_PRESCALER_1024=0x07
}En_timer2perscaler_t;

typedef enum En_timer2Interrupt_t{
	T2_POLLING=0,T2_INTERRUPT_NORMAL=0x40,T2_INTERRUPT_CMP=0x80
}En_timer2Interrupt_t;







/*===========================Timer0 Control===============================*/
/**
 * Description: initialize timer0
 * @param control:
 * 				mode: timer mode and takes the following values
 * 				- 0x00 -> T0_NORMAL_MODE
 * 				- 0x08 -> T0_COMP_MODE
 *
 *
 * 				OC0: decides what to do with pin OC0 when compare match occurs and takes the following values
 * 				- 0x00 -> T0_OC0_DIS
 * 				- 0x10 -> T0_OC0_TOGGLE
 *  			- 0x20 -> T0_OC0_CLEAR
 * 				- 0x30 -> T0_OC0_SET
 *
 * @param prescal: decides the prescaler value upon which the cpu frequency will be divided to produce the timer frequency
 * 				- 0x00 -> T0_OC0_DIS
 * 				- 0x10 -> T0_OC0_TOGGLE
 *  			- 0x20 -> T0_OC0_CLEAR
 * 				- 0x30 -> T0_OC0_SET
 *
 * @param initialValue: the value from which the timer will start counting
 *
 * @param interruptMask: decides the operating mode and takes the following values
 * 				- 0x00 -> T0_POLLING
 * 				- 0x01 -> T0_INTERRUPT_NORMAL
 *  			- 0x02 -> T0_INTERRUPT_CMP
 */
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask);

/**
 * Description: sets a value from which the timer will start counting
 * @param value: the value which is to be put in the counter register
 */
void timer0Set(uint8_t u8_value);

/**
 * Description: read the value in the counter register
 * @return
 */
uint8_t timer0Read(void);

/**
 * Description: starts the timer by providing the control register (TCCR0) with the chosen prescaler
 */
void timer0Start(void);

/**
 * Description: stops the timer by zeroing the prescaler bits (CS00, CS01, CS02) in the control register (TCCR0)
 */
void timer0Stop(void);

/**
 * Description: provides a delay in milliseconds using timer0
 * @param delay: the number of milliseconds by which the timer0 will delay the cpu
 */
void timer0DelayMs(uint16_t u16_delay_in_ms);

/*
 * NOTE: This function isn't operational because the processor speed is too low to provide an exact delay in microseconds
 */
void timer0DelayUs(uint32_t u32_delay_in_us);

/**
 * Description:
 * @param dutyCycle
 */
void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency);









/*===========================Timer1 Control===============================*/
/**
 * Description: initialize timer1
 * @param control:
 * 				mode: timer mode and takes the following values
 * 				- 0x0000 -> T1_NORMAL_MODE
 * 				- 0x0008 -> T1_COMP_MODE
 * 				- 0x0018 -> T1_COMP_MODE_ICR1_TOP
 *
 * 				OC1: decides what to do with pin OC1 when compare match occurs and takes the following values
 * 				- 0x0000 -> T1_OC1_DIS
 * 				- 0x4000 -> T1_OC1A_TOGGLE
 *  			- 0x1000 -> T1_OC1B_TOGGLE
 * 				- 0x8000 -> T1_OC1A_CLEAR
 * 				- 0x2000 -> T1_OC1B_CLEAR
 * 				- 0xC000 -> T1_OC1A_SET
 *  			- 0x3000 -> T1_OC1B_SET
 *
 *				prescal: Decides the prescaler value upon which the cpu frequency will be divided to produce the timer frequency
 * 				- 0x0000 -> T1_NO_CLOCK
 * 				- 0x0001 -> T1_PRESCALER_NO
 *  			- 0x0002 -> T1_PRESCALER_8
 * 				- 0x0003 -> T1_PRESCALER_64
 * 				- 0x0004 -> T1_PRESCALER_256
 * 				- 0x0005 -> T1_PRESCALER_1024
 *
 * @param initialValue: the value from which the timer will start counting
 *
 * @param outputCompare: the value from which the timer will start counting
 *
 * @param interruptMask: Decides the operating mode and takes the following values
 * 				- 0x00 -> T1_POLLING
 * 				- 0x04 -> T1_INTERRUPT_NORMAL
 *  			- 0x08 -> T1_INTERRUPT_CMP_1B
 *  			- 0x10 -> T1_INTERRUPT_CMP_1A
 *  			- 0x20 -> T1_INTERRUPT_ICAPTURE
 */
void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC1,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask);

/**
 * Description: sets a value from which the timer will start counting
 * @param value: the value which is to be put in the counter register
 */
void timer1Set(uint16_t u16_value);

/**
 * Description: read the value in the counter register
 * @return
 */
uint16_t timer1Read(void);

/**
 * Description: starts the timer by providing the control B register (TCCR1B) with the chosen prescaler
 */
void timer1Start(void);

/**
 * Description: stops the timer by zeroing the prescaler bits (CS10, CS11, CS12) in the control B register (TCCR1B)
 */
void timer1Stop(void);

/**
 * Description: provides a delay in milliseconds using timer1
 * @param delay: the number of milliseconds by which the timer1 will delay the cpu
 */
void timer1DelayMs(uint16_t u16_delay_in_ms);

/*
 * NOTE: This function isn't operational because the processor speed is too low to provide an exact delay in microseconds
 */
void timer1DelayUs(uint32_t u32_delay_in_us);

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency);





/*===========================Timer2 Control===============================*/
/**
 * Description: initialize timer2
 * @param control:
 * 				mode: timer mode and takes the following values
 * 				- 0x00 -> T2_NORMAL_MODE
 * 				- 0x08 -> T2_COMP_MODE
 * 				OC2: decides what to do with pin OC1 when compare match occurs and takes the following values
 * 				- 0x0000 -> T2_OC2_DIS
 * 				- 0x4000 -> T2_OC2_TOGGLE
 *  			- 0x1000 -> T2_OC2_CLEAR
 * 				- 0x8000 -> T2_OC2_SET
 *				prescal: Decides the prescaler value upon which the cpu frequency will be divided to produce the timer frequency
 * 				- 0x00 -> T2_NO_CLOCK
 * 				- 0x01 -> T2_PRESCALER_NO
 *  			- 0x02 -> T2_PRESCALER_8
 * 				- 0x03 -> T2_PRESCALER_32
 * 				- 0x04 -> T2_PRESCALER_64
 * 				- 0x05 -> T2_PRESCALER_128
 * 				- 0x06 -> T2_PRESCALER_256
 * 				- 0x07 -> T2_PRESCALER_1024
 *
 * @param initialValue: the value from which the timer will start counting
 *
 * @param outputCompare: the value from which the timer will start counting
 *
 * @param interruptMask: Decides the operating mode and takes the following values
 * 				- 0x00 -> T2_POLLING
 * 				- 0x40 -> T2_INTERRUPT_NORMAL
 *  			- 0x80 -> T2_INTERRUPT_CMP
 */
void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC2,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask);

/**
 * Description: sets a value from which the timer will start counting
 * @param value: the value which is to be put in the counter register
 */
void timer2Set(uint8_t u8_value);

/**
 * Description: read the value in the counter register
 * @return
 */
uint8_t timer2Read(void);

/**
 * Description: starts the timer by providing the control register (TCCR2) with the chosen prescaler
 */
void timer2Start(void);

/**
 * Description: stops the timer by zeroing the prescaler bits (CS20, CS21, CS22) in the control register (TCCR2)
 */
void timer2Stop(void);

/**
 * Description: provides a delay in milliseconds using timer2
 * @param delay: the number of milliseconds by which the timer2 will delay the cpu
 */
void timer2DelayMs(uint16_t u16_delay_in_ms);

/*
 * NOTE: This function isn't operational because the processor speed is too low to provide an exact delay in microseconds
 */
void timer2DelayUs(uint32_t u32_delay_in_us);

/**
 * Description:
 * @param dutyCycle
 */
void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency);

#endif /* TIMERS_H_ */
