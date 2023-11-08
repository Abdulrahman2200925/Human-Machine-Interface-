# Human-Machine-Interface-

# Embedded Systems Assessment 2
This is a sample readme file for our project, the project is to make a c program on arduino ide that utilizes a LM35 temperature sensor, push buttons, a buzzer, a 16x2 LCD display, I2C communication, external interrupts, and an ADC interface. This system allows users to monitor temperature readings from a sensor, control temperature limits using buttons, and receive alerts via a buzzer when the temperature goes beyond the configured limits. To make that we used some built in libraries, and created some header files that contain functions, prototyes, macros to make the main file more organized and understandable to any person.

## Table of contents:
* [Team Members](#team-members)
* [Built In Libraries We used](#built-in-libraries-we-used)
* [Functions Created and Used In The Main](#functions-created-and=used-in-the-main)
* [Design of the Circuit Using Tinkercad](#design-of-the-circuit-using-tinkercad)
* [Design of the Circuit on Proteus](#design-of-the-circuit-on-proteus)

## Team Members:
* Abdelrahman Mohammed
* Khalid Ahmed Almasry
* Amr Ibrahim

## Built In Libraries We used:
* avr/interrupt.h

### Functions Created and Used In The Main:
```
* u8 DIO_u8SetPinDirection(u8 copy_Port, u8  copy_PinNumber,u8  copy_PinDirection):
Sets the pin chosen as input or output

* u8 DIO_u8SetPinValue(u8 copy_Port, u8  copy_PinNumber,u8  copy_PinValue):
Sets the pin chosen as high or low

* ADC_voidINIT():
INITIALIZE THE ADC: Select the voltage reference, Set Left Adjust Result, Set Prescaler Value, Enable ADC Peripheral, Enable ADC Interrupt

* I2CLCD_init():
INITIALIZE THE I2C_LCD: Initialize your Master Address and Perform LCD initialization steps such as  4-Bit Mode, 2-Row Select, etc.

* INT0_init():
INITIALIZE EXTERNAL INTERRUPT 0 FOR INCREMENT BUTTON, trigger on falling edge

* INT1_init():
INITIALIZE EXTERNAL INTERRUPT 1  FOR DECREMENT BUTTON, trigger on falling edge

* ADC_u8StartConversionAsynchu8 (Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void)):
FUNCTION THAT START CONVERSION OF THE ADC AND IMPLEMENT THE INTERRUPT WHEN IT FINISHES CONVERSION

* temp_lm35():
FUNCTION THAT DISPLAY THE TEMPERATURE OF LM35 AND CHECK IF THE TEMPERATURE EXCEED THE LIMITTER VALUE


```
## Design of the Circuit Using Tinkercad :
![image](https://github.com/Abdulrahman2200925/Human-Machine-Interface-/assets/114658809/9afc1a76-df8f-43bd-8955-16bc8ecd0755)


## Design of the Circuit on Proteus:
![image](https://github.com/Abdulrahman2200925/Human-Machine-Interface-/assets/114658809/d3e56552-bf91-4d98-8225-b8ca80c74750)
