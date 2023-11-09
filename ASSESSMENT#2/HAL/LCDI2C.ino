#define F_CPU 16000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT.h"


#include "TWI_INTERFACE.h"
#include "I2C_LCD_INTERFACE.h"
#include "I2C_LCD_PRIVATE.h"


u8 global_LCD=0;

static u8 PCF8574_write_I2C(u8 data) {
	
	
    // Start I2C communication
    u8 Local_Error = TWI_SendStartCondition();
    if (Local_Error != NoError) {
        return ERROR;
    }
    
    // Send the device address with write bit
    Local_Error = TWI_SendSlaveAddressWithWrite(slave_address_fixed_bits);
    if (Local_Error != NoError) {
        return ERROR;
    }

    // Send the data byte
    Local_Error = TWI_MasterWriteDataByte(data);
    if (Local_Error!= NoError) {
        return ERROR;
    }

    // Stop I2C communication
    TWI_SendStopCondition();

    return Local_Error;
}



void I2CLCD_init(void) {
    // Initialize your Master Address
    TWI_voidInitMaster(0x01);
 
    // Perform LCD initialization steps
    I2CLCD_sendCommand(LCD_GO_TO_HOME);					// Return to Home
    I2CLCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);   // 4-Bit Mode, 2-Row Select
    I2CLCD_sendCommand( LCD_CURSOR_OFF );               // Cursor on, Blinking on
    I2CLCD_sendCommand(LCD_CLEAR_COMMAND);
	I2CLCD_sendCommand(lcd_EntryMode);					// Clear LCD
}

/*
Brief: This Function sends data to the I2C LCD.
Parameters:
=> u8 Data --> Data that you want to display (for every pixel)
Return: nothing
*/
void I2CLCD_Senddata(u8 data) {
    // Write to PCF8574 to set RS and RW (RW = 0)
    SET_BIT(global_LCD, LCD_RS_PIN_ID); // Set RS bit
    PCF8574_write_I2C(global_LCD);     // Write to PCF8574

    CLR_BIT(global_LCD, LCD_RW_PIN_ID); // Clear RW bit
    PCF8574_write_I2C(global_LCD);     // Write to PCF8574
    _delay_ms(1);

    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID); // Set E bit
    PCF8574_write_I2C(global_LCD);     // Write to PCF8574
    _delay_ms(1);

    // Prepare the data based on LCD_LAST_PORT_PINS configuration
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | (data & 0xF0);
    #else
        global_LCD = (global_LCD & 0xF0) | ((data & 0xF0) >> 4);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);

    // Disable LCD (E=0)
    CLR_BIT(global_LCD, LCD_E_PIN_ID); // Clear E bit
    PCF8574_write_I2C(global_LCD);     // Write to PCF8574
    _delay_ms(1);

    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID); // Set E bit
    PCF8574_write_I2C(global_LCD);     // Write to PCF8574
    _delay_ms(1);

    // Prepare the data for the second nibble
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | ((data & 0x0F) << 4);
    #else
        global_LCD = (global_LCD & 0xF0) | (data & 0x0F);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);

    CLR_BIT(global_LCD, LCD_E_PIN_ID); // Disable LCD E=0
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);
}



//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
Brief: This Function interfaces to send configuration commands to the LCD Driver using I2C.
Parameters:
=> u8 Copy_u8Command --> Command number
Return: Nothing
Hint: RS pin Mode is the difference between this function and the previous (I2CLCD_voidSendData)
*/
void I2CLCD_sendCommand(u8 command) {
    CLR_BIT(global_LCD, LCD_RS_PIN_ID);     // Instruction Mode RS = 0
    PCF8574_write_I2C(global_LCD);

    CLR_BIT(global_LCD, LCD_RW_PIN_ID);     // Write data to LCD so RW = 0
    PCF8574_write_I2C(global_LCD);

    _delay_ms(1);

    SET_BIT(global_LCD, LCD_E_PIN_ID);      // Enable LCD E = 1
    PCF8574_write_I2C(global_LCD);

    _delay_ms(1);

    // Prepare the data based on LCD_LAST_PORT_PINS configuration
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | (command & 0xF0);
    #else
        global_LCD = (global_LCD & 0xF0) | ((command & 0xF0) >> 4);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);

    // Disable LCD (E = 0)
    CLR_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);

    // Enable LCD (E = 1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);

    // Prepare the data for the second nibble
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | ((command & 0x0F) << 4);
    #else
        global_LCD = (global_LCD & 0xF0) | (command & 0x0F);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);

    CLR_BIT(global_LCD, LCD_E_PIN_ID);       // Disable LCD E = 0
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
Brief : This Function send string to the port which is defined in config.h
Parameters :
=> * Copy_u8ptrString  --> Pointer to the string
return : nothing
*/
void I2CLCD_voidSendString  ( const u8 * Copy_u8ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while( Copy_u8ptrString[LOC_u8Iterator] != '\0' ){

		I2CLCD_Senddata( Copy_u8ptrString[LOC_u8Iterator] );
		LOC_u8Iterator++ ;

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
Brief : This Function send number to the port which is defined in config.h
Parameters :
=> Copy_u64Number --> number that you want to display
return : nothing
*/
void I2CLCD_voidSendNumber   ( u64 Copy_u64Number    ){

	u64 LOC_u64Reversed = 1 ;

	if( Copy_u64Number == 0 ){ I2CLCD_Senddata('0'); }

	else{

		while( Copy_u64Number != 0 ){

			LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copy_u64Number % 10 );
			Copy_u64Number /= 10 ;

		}
		while( LOC_u64Reversed != 1 ){

			I2CLCD_Senddata( ( LOC_u64Reversed % 10 ) + 48 );
			LOC_u64Reversed /= 10 ;

		}

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
Brief : This Function set the cursor position
Parameters :
=> Copy_u8Row --> row number (LCD_ROW_1 or LCD_ROW_2)
=> Copy_u8Col --> column number (LCD_COL_1 ... LCD_COL_16)
return : nothing

Hint :
   In This function we send a command which =0b1xxxxxxx
   MSB = 1  ===> refers that it is command to set cursor
   xxxxxxx  ===> refers to AC ( Address Counter 7Bits / DDRAM Locations 128Location )
*/
void I2CLCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col ){

	u8 LOC_u8data ;

	// In These cases will set at (0,0) ==> if the user enter invalid location 
	if(Copy_u8Row>2||Copy_u8Row<1||Copy_u8Col>16||Copy_u8Col<1)							  //check
	{
		LOC_u8data = LCD_SET_CURSOR_LOCATION   ;										  // first location 
	}

	else if( Copy_u8Row == LCD_ROW_1 ){

		LOC_u8data = ( ( LCD_SET_CURSOR_LOCATION   ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

	}

	else if( Copy_u8Row == LCD_ROW_2 ){

		LOC_u8data = ( ( LCD_SET_CURSOR_LOCATION   ) + (64) + ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

	}
	I2CLCD_sendCommand ( LOC_u8data );
	_delay_ms(1);

}




//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
Brief: This Function clear LCD
Parameters nothing
return nothing
*/
void I2CLCD_voidClearScreen(void)
{
	I2CLCD_sendCommand(LCD_CLEAR_COMMAND);
	_delay_ms(10);											
}

void LCD_voidClearLine(u8 Copy_u8Row) {
    u8 LOC_u8data;

    // Check if the row is valid (1 or 2)
    if (Copy_u8Row < 1 || Copy_u8Row > 2) {
        // Invalid row, do nothing
        return;
    }

    // Calculate the starting position of the row
    if (Copy_u8Row == LCD_ROW_1) {
        LOC_u8data = LCD_SET_CURSOR_LOCATION;
    } else if (Copy_u8Row == LCD_ROW_2) {
        LOC_u8data = LCD_SET_CURSOR_LOCATION + 64;
    }

    // Clear the entire line by writing spaces (ASCII value for space is 0x20)
    for (u8 col = 0; col < 16; col++) {
        	I2CLCD_Senddata(' '); // Write a space character
    }

    // Set the cursor back to the beginning of the cleared line
    I2CLCD_sendCommand(LOC_u8data);
}
void I2CdisplayNumberWithLeadingZeros(u8 number) {
	if (number < 10) {
		// Display two leading zeros if the number is less than 10
		I2CLCD_voidSendNumber(0);
		I2CLCD_voidSendNumber(0);
	}
     else if (number < 100) {
	     // Display an additional leading zero if the number is less than 100
	     I2CLCD_voidSendNumber(0);
     }
	I2CLCD_voidSendNumber(number);
}
