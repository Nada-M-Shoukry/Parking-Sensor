/*
 * ULTRASONIC.c
 *
 *  Created on: Oct 14, 2024
 *      Author: nadam
 */
/*******************************************************/

#include "ULTRASONIC.h"
#include "ICU.h"
#include "GPIO.h"
#include "common_macros.h"
#include <util/delay.h>

/*********************Variables************************/

static volatile uint16 g_highTime = 0;
static uint8 g_edgeCount = 0;

ICU_ConfigType ICU_Config = { F_CPU_8, RISING };

uint16 distance = 0;

/***************** Functions Definitions **************/

void Ultrasonic_init(void)
{
	ICU_init (&ICU_Config);

	ICU_setCallBack (Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection (ULTRASONIC_TRIGG_PORT, ULTRASONIC_TRIGG_PIN, PIN_OUTPUT);

}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin (ULTRASONIC_TRIGG_PORT, ULTRASONIC_TRIGG_PIN, LOGIC_HIGH);
	_delay_us(ULTRASONIC_TRIGG_PULSE);
	GPIO_writePin (ULTRASONIC_TRIGG_PORT, ULTRASONIC_TRIGG_PIN, LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();


	distance = (float32) (g_highTime /  117.6);                        /* Distance = (Sound velocity * Echo time) / 2
	                                                                    * Distance = (34000 cm/s     * Echo time) / 2  = 17000 * Echo time
	                                                                    * While using, F_CPU_8 and 16MHz MCU Therefore, time to execute 1 instruction is 0.5 us.
	                                                                    * So, the timer gets incremented after 0.5 us time elapse
	                                                                    * Distance = 17000 * Echo time * 0.5 * 10^-6 cm
	                                                                    * Distance = Echo time / 117.6 */


	                                                                   /* Reset the pulse width for the next time. */

	return distance;

}

void Ultrasonic_edgeProcessing(void)
{
	if (g_edgeCount == 0)
	{
		ICU_clearTimerValue();                                        /* Clear the timer value */

		ICU_setEdgeDetectionType (FALLING);                           /* Switch to FALLING edge */

		g_edgeCount = 1;

	}

	else if (g_edgeCount == 1)
	{
		g_highTime = ICU_getInputCaptureValue() ;                     /* Falling edge detected, calculate the high time. */

		ICU_setEdgeDetectionType (RISING);                            /* Switch to RISING edge */

		g_edgeCount = 0;                                              /* Reset Edge Count for the next Falling edge detection. */

	}
}

