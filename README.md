# Human-Machine-Interface-

# Embedded Systems Assessment 2
This is a sample readme file for our project, the project is to make a c program on arduino ide that utilizes a LM35 temperature sensor, push buttons, a buzzer, a 16x2 LCD display, I2C communication, external interrupts, and an ADC interface. This system allows users to monitor temperature readings from a sensor, control temperature limits using buttons, and receive alerts via a buzzer when the temperature goes beyond the configured limits. To make that we used some built in libraries, and created some header files that contain functions, prototyes, macros to make the main file more organized and understandable to any person.

## Table of contents:
* [Team Members](#team-members)
* [Built In Libraries We used](#built-in-libraries-we-used)
* [Functions Created and Used](#functions-created-and=used)
* [Design of the Circuit Using Tinkercad](#design-of-the-circuit-using-tinkercad)
* [Design of the Circuit on Proteus](#design-of-the-circuit-on-proteus)

## Team Members:
* Abdelrahman Mohammed
* Khalid Ahmed Almasry
* Amr Ibrahim

## Built In Libraries We used:
* avr/interrupt.h

### Functions Created and Used:
```
* function DIO_SetPinDirection:
Sets the pin chosen as input or output

* function DIO_SetPinValue:
Sets the pin chosen as high or low

* function DIO_GetPinValue: 
Gets the value/signal from the component connected to the pin chosen

* function button_init:
Initalize button as an input by using DIO_SetPinDirection

```
## Design of the Circuit Using Tinkercad :
![image](![image](https://github.com/Abdulrahman2200925/Human-Machine-Interface-/assets/114658809/9afc1a76-df8f-43bd-8955-16bc8ecd0755)


## Design of the Circuit on Proteus:
![image](![image](https://github.com/Abdulrahman2200925/Human-Machine-Interface-/assets/114658809/d3e56552-bf91-4d98-8225-b8ca80c74750)
