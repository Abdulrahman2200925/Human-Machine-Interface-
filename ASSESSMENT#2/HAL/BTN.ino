#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT.h"
#include "DIO_INTERFACE.h"
#include "EXIT_INT_INTERFACE.h"
#include "I2C_LCD_INTERFACE.h"



volatile u8 Temp_Limitter = 0;


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
	// External interrupt service routine
	_delay_ms(50); // Simple debouncing delay

	if (GET_BIT(DIO_PORTD, DIO_PIN2)==0) {
		// Button is pressed
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
	// External interrupt service routine
	_delay_ms(50); // Simple debouncing delay

	if (GET_BIT(DIO_PORTD, DIO_PIN3)==0) {
		// Button is pressed
		if (Temp_Limitter > 0) {
			Temp_Limitter--;
			I2CLCD_voidSetPosition(2, 14);
			I2CLCD_voidSendString(" ");
			I2CLCD_voidSetPosition(2, 14);
			I2CdisplayNumberWithLeadingZeros(Temp_Limitter); // Display the updated value
		}
	}
}