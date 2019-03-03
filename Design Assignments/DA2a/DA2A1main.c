/*
 * DA2AC.c
 *
 * Created: 3/2/2019 2:52:43 PM
 * Author : regis
 */ 

#include <avr/io.h> //This contains definitions for all the registers locations and some
// other things, must always be included
#define F_CPU 16000000UL //F_CPU tells the compiler that our crystal is an 16Mhz one so it
// can generate an accurate delay, must be declared above delay so
// delay knows what is the value of F_CPU
#include <util/delay.h> //Contains some delay functions that will generate accurate delays
// of ms and us
int main(void){ //In ANSI C, the main function as always an int return and using
	// void will give you an warning
	DDRB |= (1<<PB2); //Define PORTB2 as an output so we can blink our led
	while(1){ 
		PORTB |= (1<<PB2); //Turn led on
		_delay_ms(290);//290); //Wait
		PORTB &= ~(1<<PB2); //Turn led off
		_delay_ms(435); //Wait 
	}
	return 1;
}

