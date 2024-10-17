/*
 * ICU.h
 *
 *  Created on: Oct 14, 2024
 *      Author: nadam
 */
/*******************************************************************/
#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/***********************Types Declarations*************************/

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}ICU_ClockType;

typedef enum
{
	FALLING, RISING
}ICU_EdgeType;

typedef struct
{
	ICU_ClockType clock;
	ICU_EdgeType edge;
}ICU_ConfigType;

/********************Functions Prototype*************************/

void ICU_init(const ICU_ConfigType * ICU_Config_Ptr);

/* Function Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers */

void ICU_setCallBack(void(*a_ptr)(void));

/* Function Description: Function to set the Call Back function address. */

void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/* Function Description: Function to set the required edge detection. */

uint16 ICU_getInputCaptureValue(void);

/* Function Description: Function to get the Timer1 Value when the input is captured
 * The value stored at Input Capture Register ICR1. */

void ICU_clearTimerValue(void);

/* Function Description: Function to clear the Timer1 Value to start count from ZERO. */

void ICU_deInit(void);

/* Function Description: Function to disable the Timer1 to stop the ICU Driver. */

#endif /* ICU_H_ */
