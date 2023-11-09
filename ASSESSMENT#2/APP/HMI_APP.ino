#include <avr/interrupt.h>          // Include the AVR interrupt header file
#include "BIT.h"                    // Include custom BIT.h header file for bit manipulation
#include "STD_TYPES.h"              // Include custom STD_TYPES.h header file for standard types
#include "DIO_INTERFACE.h"          // Include custom DIO_INTERFACE.h header file for Digital I/O
#include "ADC_INTERFACE.h"          // Include custom ADC_INTERFACE.h header file for ADC operations
#include "EXIT_INT_INTERFACE.h"     // Include custom EXIT_INT_INTERFACE.h header file for external interrupts
#include "I2C_LCD_INTERFACE.h"      // Include custom I2C_LCD_INTERFACE.h header file for I2C LCD interface
#include "LM35_INTERFACE.h"         // Include custom LM35_INTERFACE.h header file for LM35 sensor interface
#include "BTN_INTERFACE.h"          // Include custom BTN_INTERFACE.h header file for button interface

void temp_lm35(void);                // Declare a function prototype for temp_lm35

/* GLOBAL VARIABLE THAT STORES THE ADC RESULT */
volatile u16 adc_result = 0;        // Declare a volatile 16-bit variable to store the ADC result
volatile u8 LM35_TEMP = 0;          // Declare a volatile 8-bit variable to store LM35 temperature

int main(void) {
    /* SET THE GLOBAL INTERRUPT TO BE ABLE TO RECEIVE INTERRUPTS */
    sei();                           // Enable global interrupts

    /* INITIALIZE THE ADC */
    ADC_voidINIT();                  // Initialize the ADC module

    /* INITIALIZE THE I2C_LCD */
    LCD_initI2C();                   // Initialize the I2C LCD module

    /* INITIALIZE EXTERNAL INTERRUPT 0 FOR INCREMENT BUTTON */
    INT0_init();                     // Initialize external interrupt 0

    /* INITIALIZE EXTERNAL INTERRUPT 1 FOR DECREMENT BUTTON */
    INT1_init();                     // Initialize external interrupt 1

    /* Replace with your application code */
    display_button();                // Call the function to initialize buttons and display Temp_Limitter

    /* SET THE ADC PIN AS INPUT */
    DIO_u8SetPinDirection(DIO_PORTC, DIO_PIN0, DIO_PIN_INPUT);  // Set ADC input pin as input

    /* SET THE BUZZER PIN AS OUTPUT */
    DIO_u8SetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT);  // Set buzzer pin as output

    /* SDA PIN SET AS AN OUTPUT, WITH PULL-UP RESISTANCE */
    DIO_u8SetPinDirection(DIO_PORTC, DIO_PIN4, DIO_PIN_INPUT);  // Set SDA pin as input with pull-up resistor
    DIO_u8SetPinValue(DIO_PORTC, DIO_PIN4, DIO_PIN_HIGH);       // Set the value of SDA pin to HIGH

    /* SCL PIN SET AS AN OUTPUT, WITH PULL-UP RESISTANCE */
    DIO_u8SetPinDirection(DIO_PORTC, DIO_PIN5, DIO_PIN_INPUT);  // Set SCL pin as input with pull-up resistor
    DIO_u8SetPinValue(DIO_PORTC, DIO_PIN5, DIO_PIN_HIGH);       // Set the value of SCL pin to HIGH

    while (1) {
        /* FUNCTION THAT STARTS CONVERSION OF THE ADC AND IMPLEMENTS THE INTERRUPT WHEN IT FINISHES CONVERSION */
        ADC_u8StartConversionAsynch(ADC_CHANNEL0, &adc_result, &temp_lm35);

        if (Temp_Limitter >= LM35_TEMP) {   // Check if LM35_TEMP is greater than or equal to LM35_TEMP
            DIO_u8SetPinValue(DIO_PORTD, DIO_PIN7, DIO_PIN_LOW);  // Set a pin (buzzer?) to HIGH
        } else {
            DIO_u8SetPinValue(DIO_PORTD, DIO_PIN7, DIO_PIN_HIGH);   // Set a pin (buzzer?) to LOW
        }
    }
}

/* FUNCTION THAT DISPLAYS THE TEMPERATURE OF LM35 */
void temp_lm35(void) {
    LM35_TEMP = ADCToTemperature(adc_result);   // Get the temperature reading from LM35 and store it in LM35_TEMP
    DisplayTemperatureOnLCD(LM35_TEMP);         // Display the temperature on the LCD
}

