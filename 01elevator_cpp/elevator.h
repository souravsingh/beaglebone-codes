
/*******************************************************
 * Header File for Lift Simulation Add-on Card for
 * GPIO PIN Configurations and Other Definitions
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

#define 	LED_9		(0 * 32) + 30
#define 	LED_10		(2 * 32) + 2
#define 	LED_11		(1 * 32) + 28
#define 	LED_12		(2 * 32) + 3
#define 	LED_13		(0 * 32) + 31
#define 	LED_14		(2 * 32) + 5
#define 	LED_15		(1 * 32) + 18


#define 	SW_1		(0 * 32) + 14
#define 	SW_2		(0 * 32) + 27
#define 	SW_3		(0 * 32) + 22
#define 	SW_4		(2 * 32) + 1



/* DIRECTIN LEDS: to represent lift direction (up or down) */
#define 	LIFT_DIR_1			LED_9
#define 	LIFT_DIR_2			LED_10
#define 	LIFT_DIR_3			LED_11
#define 	LIFT_DIR_4			LED_12
#define 	LIFT_DIR_5			LED_13
#define 	LIFT_DIR_6			LED_14
#define 	LIFT_DIR_7			LED_15


/* POSITION LEDS: LEDs to indicate the current position of Lift */
#define 	LIFT_POS_0			LED_5
#define 	LIFT_POS_1			LED_6
#define 	LIFT_POS_2			LED_7
#define 	LIFT_POS_3			LED_8


/* LIFT BUTTONS: corresponding to each floor of the Lift */
#define 	LIFT_BUTTON_0			SW_1
#define 	LIFT_BUTTON_1			SW_2
#define 	LIFT_BUTTON_2			SW_3
#define 	LIFT_BUTTON_3			SW_4

/* LIFT LEDS: indication for BUTTON Press on each floor */
#define 	LIFT_LED_0			LED_1
#define 	LIFT_LED_1			LED_2
#define 	LIFT_LED_2			LED_3
#define 	LIFT_LED_3			LED_4

/* An array of DIRECTIN LEDS */
unsigned int dir_leds[] =
{
		LIFT_DIR_1,
		LIFT_DIR_2,
		LIFT_DIR_3,
		LIFT_DIR_4,
		LIFT_DIR_5,
		LIFT_DIR_6,
		LIFT_DIR_7
};

/* An array of POSITION LEDS */
unsigned int pos_leds[] = {
		LIFT_POS_0,
		LIFT_POS_1,
		LIFT_POS_2,
		LIFT_POS_3
};

unsigned int lift_leds[] = {
		LIFT_LED_0,
		LIFT_LED_1,
		LIFT_LED_2,
		LIFT_LED_3
};


unsigned int lift_buttons[] = {
		LIFT_BUTTON_0,
		LIFT_BUTTON_1,
		LIFT_BUTTON_2,
		LIFT_BUTTON_3
};


#define BUTTON_PRESSED		0
#define BUTTON_RELEASED		1


#define NO_OF_FLOORS		4
#define NO_OF_DIR_LEDS		7
#define DEFAULT_LIFT_POS	0

struct floor
{
	int fd;
	unsigned int button;
	unsigned int led;
};

struct  floor floor_set[NO_OF_FLOORS] =
{
		{-1, LIFT_BUTTON_0, LIFT_LED_0},

		{-1, LIFT_BUTTON_1, LIFT_LED_1},

		{-1, LIFT_BUTTON_2, LIFT_LED_2},

		{-1, LIFT_BUTTON_3, LIFT_LED_3}
};









