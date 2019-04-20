/*
 * DA4b.c
 *
 * Created: 4/20/2019 12:51:09 PM
 * Author : regis
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int check = 0;

int main(void)
{
	DDRB = 0xFF; //DDRB as an output
	DDRD = 0xFF;
	TCCR1B=3; //set prescaler
	TCCR1A=0x83; //set Fast PWM

	ADMUX = 0x60; //use PC0 as ADC pin
	ADCSRA = 0xE6;

	while (1)
	{
		ADCSRA |= ( 1 << ADSC); //start conversion
		while((ADCSRA & (1 << ADIF))== 0);
		check = ADCH; //temp value
		
		if(check == 0) //MIN value
		{
			OCR1A = 15; //turn 0 deg
			_delay_ms(1000);
		}
		else if(check == 255) //MAX pot value
		{
			OCR1A = 30;			// turn 180
			_delay_ms(1000);
		}
		else;
	}
}

