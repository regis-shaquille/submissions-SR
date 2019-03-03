/*
 * DA2AC2.c
 *
 * Created: 3/2/2019 5:12:51 PM
 * Author : regis
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<2); //Define PORTB2 as an output so we can blink our led
	
	DDRC &= (0<<2);
	PORTC |= (1<<2);
	while(1){
		//PORTB |= (1<<PB2); //Turn led off
		//_delay_ms(290);//290); //Wait 1 second
		if(PINC & 0x2){
			_delay_ms(1250); //Wait another second
			PORTB |= (1<<PB2);
			
		}
		else
			PORTB &= ~(1<<PB2); //Turn led on
		
	}
	return 0;	
}

