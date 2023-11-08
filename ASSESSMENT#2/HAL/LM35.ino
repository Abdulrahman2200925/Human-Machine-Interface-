#include "STD_TYPES.h"
#include "I2C_LCD_INTERFACE.h"
#include "LM35_INTERFACE.h"






u8 ADCToTemperature(u16 adcReading) {
	u16 analog_value = (u16)(((u32)adcReading *(u32) 5000UL) / 1024UL); // Assuming V_REF is 5V   // To Convert from ( V --> mV )
   // u16 analog_value = (u16)(((u32)adcReading *(u32) 1100UL) / 1024UL); // Assuming V_REF is 1.1V   // To Convert from ( V --> mV )
	u8 temperatureC = (analog_value / 10); // LM35 sensitivity is 10 mV per 1°C
	return temperatureC;
	
	
}
void DisplayTemperatureOnLCD(u8 temperature) {
	// Clear the LCD screen
	 
   
	// Display temperature label
	LCD_voidSetPosition(1, 1);
	LCD_voidSendString("Temp:");

	// Position the cursor for temperature value
	LCD_voidSetPosition(1, 8);

	// Display temperature value as a two-digit number

	displayNumberWithLeadingZeros(temperature);

	// Position the cursor for temperature unit 'C'
	LCD_voidSetPosition(1, 11);

	// Display temperature unit
	LCD_voidSendString("  C'");
   
	
}
void LM35_temp(u16 ADC_READING){
	u8 temp_value=  ADCToTemperature(ADC_READING);

	DisplayTemperatureOnLCD(temp_value);
	
}
