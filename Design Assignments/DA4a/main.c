/*
 * DA4a.c
 *
 * Created: 4/11/2019 10:34:54 AM
 * Author : regis
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int check = 0; //bool

int main(void)
{
	
	DDRD = 0xFF;		//set PORTD as output
	DDRB = 0xFF;		//set PORTB as output
	EIMSK = 0x01;		//enable INT0
	EIFR = 0x01;		//enable INTF0
	EICRA = 0x03;		//enable ISC01 and ISC00
	TCCR1B = 0b00000001;	//sets no Prescaler
	TCCR1A = 0x83;		//sets COM0 and Fast PWM
	sei();				//interrupt
	ADMUX = 0x60;		//set PC0 as ADC pin
	ADCSRA = 0xE6;
	
	
	while (1){
		
		while(!(ADCSRA & (1<<ADIF)));	//poll
		ADCSRA |=0b00010000;			//set ADIF 1
		OCR1A = ADCH;					//read ADC value from pot
	}
	return 0;
}
ISR(INT0_vect) //external interrupt
{
	if(check == 0)
	{
		PORTB |= 1 << PORTB1;
		_delay_ms(1000);
	}
	else
	{
		
		PORTB &= ~(1<<PORTB1);
		_delay_ms(1000);
	}
	check ^= 1; // toggle DC Motor when external interrupt is pressed

}