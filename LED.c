/*
 * LED.c
 *
 *  Created on: Oct 9, 2024
 *      Author: nadam
 */
/************************************************************/

#include "LED.h"
#include "GPIO.h"

/******************Functions Definitions********************/

void LEDS_init(void)
{
	GPIO_setupPinDirection (RED_LED_PORT_ID, RED_LED_PIN_ID, PIN_OUTPUT);        /*LEDS PINS O/P */
	GPIO_setupPinDirection (GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection (BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, PIN_OUTPUT);

	GPIO_writePin (RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);                  /* All LEDS initially OFF */
	GPIO_writePin (GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
	GPIO_writePin (BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
}

void LED_ON(LED_ID id)
{
 #if (LED_CONNECTION == positive_logic)
	{
		switch(id)
		{
		case (RED_LED) :

		GPIO_writePin (RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
		break;

		case (GREEN_LED) :

		GPIO_writePin (GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
		break;

		case (BLUE_LED) :

		GPIO_writePin (BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_HIGH);
		break;

		}
	}

 #elif
	{
		switch(id)
		{
		case (RED_LED) :

		GPIO_writePin (RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
		break;

		case (GREEN_LED) :

		GPIO_writePin (GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
		break;

		case (BLUE_LED) :

		GPIO_writePin (BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
		break;

		}
	}
#endif
}

void LED_OFF(LED_ID id)
{
#if (LED_CONNECTION == positive_logic)
	{
		switch(id)
		{
		case (RED_LED) :

		GPIO_writePin (RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
		break;

		case (GREEN_LED) :

		GPIO_writePin (GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
		break;

		case (BLUE_LED) :

		GPIO_writePin (BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
		break;

		}
	}

#elif
	{
		switch(id)
		{
		case (RED_LED) :

		GPIO_writePin (RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
		break;

		case (GREEN_LED) :

		GPIO_writePin (GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
		break;

		case (BLUE_LED) :

		GPIO_writePin (BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_HIGH);
		break;

		}
	}
#endif
}



