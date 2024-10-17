/*
 * LED.h
 *
 *  Created on: Oct 8, 2024
 *      Author: nadam
 */
/***********************************************/


#ifndef LED_H_
#define LED_H_

#include "std_types.h"

/***************Definitions*********************/

#define RED_LED_PORT_ID      PORTC_ID
#define GREEN_LED_PORT_ID    PORTC_ID
#define BLUE_LED_PORT_ID     PORTC_ID

#define RED_LED_PIN_ID       PIN0_ID
#define GREEN_LED_PIN_ID     PIN1_ID
#define BLUE_LED_PIN_ID      PIN2_ID

#define LED_CONNECTION       positive_logic

typedef enum
{
	RED_LED, GREEN_LED, BLUE_LED

}LED_ID;

/***************Functions Prototypes************/

void LEDS_init(void);

void LED_ON(LED_ID id);

void LED_OFF(LED_ID id);

#endif /* LED_H_ */
