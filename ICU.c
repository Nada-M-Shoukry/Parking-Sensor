/*
 * ICU.c
 *
 *  Created on: Oct 14, 2024
 *      Author: nadam
 */
/*****************************************************/

#include "ICU.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/****************Global Variables*********************/



static volatile void (*g_callBackPtr)(void) = NULL_PTR;        /* Global variable to hold the address of
                                                                  the call back function in the application */


/***********Interrupt service routines (ISR)**********/


ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();                                   /* Call the Call Back function in the application after the edge
		                                                         is detected using pointer to function g_callBackPtr(); */
	}
}


/****************Functions Definition*****************/


void ICU_init(const ICU_ConfigType * ICU_Config_Ptr)
{

	DDRD &= ~(1<<PD6);                                     /* Configure ICP1/PD6 as i/p pin */


	TCCR1A = (1<<FOC1A) | (1<<FOC1B);                         /* Timer1 always operates in Normal Mode */


	TCCR1B = (TCCR1B & 0xF8) | (ICU_Config_Ptr->clock);       /* insert the required clock value in the first three bits
	                                                             (CS10, CS11 and CS12) of TCCR1B Register */

	TCCR1B = (TCCR1B & 0xBF) | ((ICU_Config_Ptr->edge)<<6);   /* insert the required edge type in ICES1 bit in TCCR1B Register */


	TCNT1 = 0;                                                /* Initial Value for Timer1 */


	ICR1 = 0;                                                 /* Initial Value for the input capture register */


	TIMSK |= (1<<TICIE1);                                     /* Enable the Input Capture interrupt to generate an
	                                                             interrupt when edge is detected on ICP1/PD6 pin */

}

void ICU_setCallBack(void(*a_ptr)(void))
{
		g_callBackPtr = a_ptr;                                /* Save the address of the Call back function
		                                                         in a global variable */
}



void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType)
{
	   TCCR1B = (TCCR1B & 0xBF) | (edgeType<<6);              /* insert the required edge type in ICES1 bit
	                                                             in TCCR1B Register */
}



uint16 ICU_getInputCaptureValue(void)
{
	    return ICR1;                                          /* get the Timer1 Value when the input is captured,
	                                                           * The value stored at Input Capture Register ICR1 */
}

void ICU_clearTimerValue(void)
{
	    TCNT1 = 0;                                            /* clear the Timer1 Value to start count from ZERO */

}

void ICU_deInit(void)
{

		TCCR1A = 0;                                           /* Clear All Timer1/ICU Registers */
		TCCR1B = 0;
		TCNT1  = 0;
		ICR1   = 0;


		TIMSK &= ~(1<<TICIE1);                           /* Disable the Input Capture interrupt */


		g_callBackPtr = NULL_PTR;		                      /* Reset the global pointer value */
}


