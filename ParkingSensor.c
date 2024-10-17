/*
 * ParkingSensor.c
 *
 *  Created on: Oct 16, 2024
 *      Author: nadam
 */
/*******************************************************/
#include "ParkingSensor.h"
#include <util/delay.h>


int main (void)
{
	LCD_init();
	Buzzer_init();
	Ultrasonic_init();
	LEDS_init();

	SET_BIT (SREG, 7);

	uint16 distance_from_obstacle = 0;
	LCD_moveCursor (0,0);
	LCD_displayString("Distance=    cm");       /* Display the distance read by the Ultrasonic /sensor on the LCD */

	while(1)
	{

		distance_from_obstacle = Ultrasonic_readDistance() + 1;
		LCD_moveCursor(0, 10);
        LCD_integerToString (distance_from_obstacle);

		if(distance_from_obstacle < 10)
		{
			LCD_displayStringRowColumn(0, 11, " ");                /* Clear the extra digit */
		}


		if (distance_from_obstacle <= 5)
		{
			LCD_displayStringRowColumn(1, 6, "STOP!");             /* Display "STOP" on the LCD */
			LED_ON(RED_LED);
			LED_ON(GREEN_LED);
			LED_ON(BLUE_LED);
			Buzzer_on();                                           /* Turn on the buzzer */
			_delay_ms(100);                                        /* Wait for 100 ms then turn off the LEDs to create a blinking effect */
			LED_OFF(RED_LED);
			LED_OFF(GREEN_LED);
			LED_OFF(BLUE_LED);
			Buzzer_off();                                          /* Turn off the buzzer */
			_delay_ms(100);
		}

		else if (distance_from_obstacle >= 6 && distance_from_obstacle <= 10  )
		{
			LED_ON(RED_LED);
			LED_ON(GREEN_LED);
			LED_ON(BLUE_LED);
			Buzzer_off();

			LCD_displayStringRowColumn(1, 6, "     ");
		}

		else if(distance_from_obstacle >= 11 && distance_from_obstacle <= 15)
		{
			LED_ON(RED_LED);
			LED_ON(GREEN_LED);
			LED_OFF(BLUE_LED);
			Buzzer_off();

			LCD_displayStringRowColumn(1, 6, "     ");
		}

		else if(distance_from_obstacle >= 16 && distance_from_obstacle <= 20)
		{
			LED_ON(RED_LED);
			LED_OFF(GREEN_LED);
			LED_OFF(BLUE_LED);
			Buzzer_off();

			LCD_displayStringRowColumn(1, 6, "     ");
		}

		else                                                        /* If distance is greater than 20 cm */
		{
			LED_OFF(RED_LED);
			LED_OFF(GREEN_LED);
			LED_OFF(BLUE_LED);
			Buzzer_off();

			LCD_displayStringRowColumn(1, 6, "     ");
		}
	}
}
