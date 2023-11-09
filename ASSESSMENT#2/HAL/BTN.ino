#include <avr/interrupt.h>          // Include the AVR interrupt header file
#define F_CPU 16000000UL           // Define the CPU frequency as 16 MHz
#include <util/delay.h>            // Include the delay header file
#include "STD_TYPES.h"             // Include custom STD_TYPES.h header file for standard types
#include "BIT.h"                   // Include custom BIT.h header file for bit manipulation
#include "DIO_INTERFACE.h"         // Include custom DIO_INTERFACE.h header file for Digital I/O
#include "EXIT_INT_INTERFACE.h"    // Include custom EXIT_INT_INTERFACE.h header file for external interrupts
#include "I2C_LCD_INTERFACE.h"     // Include custom I2C_LCD_INTERFACE.h header file for I2C LCD interface

volatile u8 Temp_Limitter = 0;    // Declare a volatile 8-bit variable for Temp_Limitter
volatile u8 button_state;          // Declare a volatile 8-bit variable for button state


void display_button() {
	// Initialize LCD
	

	// Initialize button pin as input with a pull-up resistor  INT0
	
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	DIO_u8SetPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_HIGH);
	// Initialize button pin as input with a pull-up resistor  INT1
	
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);
	DIO_u8SetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);



	// Display initial value on LCD
	I2CLCD_voidSetPosition(2, 1);
	I2CLCD_voidSendString ("Temp_limit: ");
	I2CLCD_voidSetPosition(2, 14);
	I2CLCD_voidSendNumber (Temp_Limitter);
	
}

ISR(INT0_vect) {
// External interrupt service routine for INT0
    _delay_ms(50);  // Simple debouncing delay

    DIO_u8GetPinValue(DIO_PORTD, DIO_PIN2, &button_state);
    if (button_state == 0) {
        // Button on INT0 is pressed
		if (Temp_Limitter < 255) {
			Temp_Limitter++;
			I2CLCD_voidSetPosition(2, 14);
			I2CLCD_voidSendString(" ");
			I2CLCD_voidSetPosition(2, 14);
			I2CdisplayNumberWithLeadingZeros(Temp_Limitter); // Display the updated value
		}
	}
}
ISR(INT1_vect) {
	 // External interrupt service routine for INT1
    _delay_ms(50);  // Simple debouncing delay
    DIO_u8GetPinValue(DIO_PORTD, DIO_PIN3, &button_state);
    if (button_state == 0) {
        // Button on INT1 is pressed
		if (Temp_Limitter > 0) {
			Temp_Limitter--;
			I2CLCD_voidSetPosition(2, 14);
			I2CLCD_voidSendString(" ");
			I2CLCD_voidSetPosition(2, 14);
			I2CdisplayNumberWithLeadingZeros(Temp_Limitter); // Display the updated value
		}
	}
}
