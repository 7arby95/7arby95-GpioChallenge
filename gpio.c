/*
 * gpio.c
 *
 *  Created on: Jan 17, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "gpio.h"


/*- APIs IMPLEMENTATION ------------------------------------*/

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	/* A switch-case statement to decide which port to manipulate its direction */
	switch(u8_port)
	{
	case GPIOA:
		PORTA_DIR = u8_direction;
		break;
	case GPIOB:
		PORTB_DIR = u8_direction;
		break;
	case GPIOC:
		PORTC_DIR = u8_direction;
		break;
	case GPIOD:
		PORTD_DIR = u8_direction;
		break;
	default:

		break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
	/* A switch-case statement to decide which port to assign the value to */
	switch(u8_port)
	{
	case GPIOA:
		PORTA_DATA = u8_value;
		break;
	case GPIOB:
		PORTB_DATA = u8_value;
		break;
	case GPIOC:
		PORTC_DATA = u8_value;
		break;
	case GPIOD:
		PORTD_DATA = u8_value;
		break;
	default:

		break;
	}
}

void gpioPortToggle(uint8_t u8_port)
{
	/* A switch-case statement to decide which port to toggle its value */
	switch(u8_port)
	{
	case GPIOA:
		PORTA_DATA ^= HIGH;
		break;
	case GPIOB:
		PORTB_DATA ^= HIGH;
		break;
	case GPIOC:
		PORTC_DATA ^= HIGH;
		break;
	case GPIOD:
		PORTD_DATA ^= HIGH;
		break;
	default:

		break;
	}
}

uint8_t gpioPortRead(uint8_t u8_port)
{
	/* A switch-case statement to decide which port to be read */
	switch(u8_port)
	{
	case GPIOA:
		return PORTA_PIN;
		break;
	case GPIOB:
		return PORTB_PIN;
		break;
	case GPIOC:
		return PORTC_PIN;
		break;
	case GPIOD:
		return PORTD_PIN;
		break;
	default:
		return ERROR;
		break;
	}
}

void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
	/* A pointer to hold the address of the port which direction is to be manipulated */
	uint8_t* pu8_portDirectionPointer = NULL;

	/* A switch-case statement to assign the right port address to the pointer */
	switch(u8_port)
	{
	case GPIOA:
		pu8_portDirectionPointer = (uint8_t*)(&PORTA_DIR);
		break;
	case GPIOB:
		pu8_portDirectionPointer = (uint8_t*)(&PORTB_DIR);
		break;
	case GPIOC:
		pu8_portDirectionPointer = (uint8_t*)(&PORTC_DIR);
		break;
	case GPIOD:
		pu8_portDirectionPointer = (uint8_t*)(&PORTD_DIR);
		break;
	default:

		break;
	}

	/* A switch-case statement to decide whether the pins are to be input or output */
	switch(u8_direction)
	{
	case INPUT:
		*pu8_portDirectionPointer &= ~u8_pins;
		break;
	case OUTPUT:
		*pu8_portDirectionPointer |= u8_pins;
		break;
	default:

		break;
	}
}

void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	/* A pointer to hold the address of the port which pins values are to be changed */
	uint8_t* pu8_portDataPointer = NULL;

	/* A switch-case statement to assign the right port address to the pointer */
	switch(u8_port)
	{
	case GPIOA:
		pu8_portDataPointer = (uint8_t*)(&PORTA_DATA);
		break;
	case GPIOB:
		pu8_portDataPointer = (uint8_t*)(&PORTB_DATA);
		break;
	case GPIOC:
		pu8_portDataPointer = (uint8_t*)(&PORTC_DATA);
		break;
	case GPIOD:
		pu8_portDataPointer = (uint8_t*)(&PORTD_DATA);
		break;
	default:

		break;
	}

	/* A switch-case statement to decide whether the bits values are to be high or low */
	switch(u8_value)
	{
	case LOW:
		*pu8_portDataPointer &= ~u8_pins;
		break;
	case HIGH:
		*pu8_portDataPointer |= u8_pins;
		break;
	default:

		break;
	}
}

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins)
{
	/* A switch-case statement to decide which port to toggle its pins */
	switch(u8_port)
	{
	case GPIOA:
		PORTA_DATA ^= u8_pins;
		break;
	case GPIOB:
		PORTB_DATA ^= u8_pins;
		break;
	case GPIOC:
		PORTC_DATA ^= u8_pins;
		break;
	case GPIOD:
		PORTD_DATA ^= u8_pins;
		break;
	default:

		break;
	}
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin)
{
	/* A switch-case statement to decide which port to read its pin */
	switch(u8_port)
	{
	case GPIOA:
		return ((PORTA_PIN & u8_pin)? 1:0);
		break;
	case GPIOB:
		return ((PORTB_PIN & u8_pin)? 1:0);
		break;
	case GPIOC:
		return ((PORTC_PIN & u8_pin)? 1:0);
		break;
	case GPIOD:
		return ((PORTD_PIN & u8_pin)? 1:0);
		break;
	default:
		return ERROR;
		break;
	}
}
