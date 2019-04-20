/*
 * DA4b Part 1.c
 *
 * Created: 4/20/2019 3:04:31 PM
 * Author : regis
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t value;

ISR(ADC_vect)
{
	value = ADCH;	//read potentiometer value and set it
}

void delayFunct(void) //use CTC Mode for the delay
{
	
	TCNT1 = 0;
	OCR1A = value;
	TCCR1B |= ( 1<< WGM12) | (1 << CS12) | (1<< CS10);
	TCCR1A |= (1 <<COM1A0);
	while(TIFR1 & ( 1 << OCF1A));

	TIFR1 |= ( 1 << OCF1A);

}

int main(void)
{

	DDRB = 0xFF;
	
	ADMUX = (0<<REFS1)| // Reference Selection Bits

	(1<<REFS0)| // AVcc - external cap at AREF
	(0<<ADLAR)| // ADC Left Adjust Result
	(0<<MUX2)| // ANalog Channel Selection Bits
	(1<<MUX1)| // ADC2 (PC2 PIN25)
	(0<<MUX0);

	ADCSRA = (1<<ADEN)| // ADC ENable

	(0<<ADSC)| // ADC Start Conversion
	(0<<ADATE)| // ADC Auto Trigger Enable
	(0<<ADIF)| // ADC Interrupt Flag
	(0<<ADIE)| // ADC Interrupt Enable
	(1<<ADPS2)| // ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);
	
	sei(); //interrupt
	
	while(1)
	{
		PORTB |= (1<< PORTB0); //used for stepper
		delayFunct();		//call function to implement CTC mode as a timer.
		PORTB |= (1<< PORTB1);
		delayFunct();
		PORTB |= (1<< PORTB2);
		delayFunct();
		PORTB |= (1<< PORTB3);
		delayFunct();
		
		
	}
	
}

