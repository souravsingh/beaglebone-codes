/*******************************************************
 * Header File for Traffic Signal Simulation Add-on Card
 * for GPIO PIN Configurations and Other Definitions
 ********************************************************/

/*
 * NOTE About BBB GPIO Pin Numbering
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * - Linux kernel on BBB treats all GPIOs as pins on external I/O chips.
 * - On BBB TI processor, each "GPIO Chip" controls up to 32 individual pins
 *   and there are 4 GPIO controller chips.
 * - There are 4 "Base I/O" numbers assigned to these GPIO controllers
 *   They are in the multiples of 32.
 *  ---------------------------------------------------------------------
 *		GPIO Controller (or Chip)		Base I/O Number
 *	---------------------------------------------------------------------
 *				GPIO0 						0			(First Pin of GPIO0)
 *				GPIO1 						32			(First Pin of GPIO1)
 *				GPIO2 						64			(First Pin of GPIO2)
 *				GPIO3 						96			(First Pin of GPIO3)
 * 	---------------------------------------------------------------------
 *
 * - To access a specific pin you need to calculate the pin's GPIO number.
 *   For a particular pin on particular GPIO controller, you need to add
 *   the pin number to Base I/O number of that GPIO controller.
 *
 * - So simply take the GPIO controller number, multiply by 32 and add the pin.
 *
 *  			GPIO2_5 = (2 * 32) + 5 = 69
 *
 *
 */


#define 	LED_1		(0 * 32) + 3		/* GPIO0_3 */
#define 	LED_2		(0 * 32) + 23
#define 	LED_3		(0 * 32) + 2
#define 	LED_4		(0 * 32) + 26

#define 	LED_5		(1 * 32) + 17
#define 	LED_6		(1 * 32) + 15
#define 	LED_7		(0 * 32) + 15
#define 	LED_8		(1 * 32) + 14

#define 	LED_9		(0 * 32) + 14
#define 	LED_10		(0 * 32) + 27
#define 	LED_11		(0 * 32) + 22
#define 	LED_12		(2 * 32) + 1


/*
 *
 * DIRECTIN LEDS: to represent Traffic flow direction
 *
 * */

#define 	NORTH_GREEN			LED_1
#define 	NORTH_YELLOW		LED_5
#define 	NORTH_RED			LED_9


#define 	EAST_GREEN			LED_2
#define 	EAST_YELLOW			LED_6
#define 	EAST_RED			LED_10


#define 	SOUTH_GREEN			LED_3
#define 	SOUTH_YELLOW		LED_7
#define 	SOUTH_RED			LED_11


#define 	WEST_GREEN			LED_4
#define 	WEST_YELLOW			LED_8
#define 	WEST_RED			LED_12



