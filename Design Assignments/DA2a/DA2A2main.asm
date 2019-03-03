;
; DA2A2.asm
;
; Created: 3/2/2019 7:49:36 PM
; Author : regis
;


; Replace with your application code
start:
	SBI DDRB, 0x4
	CBI DDRC, 0x2
	LDI r16, 0x00
	OUT PORTB, r16
	
loop:
	IN r18, PINC
	CP r16, r18
	BRNE lightOn
	rjmp loop
lightOn:
	LDI r18, 0xff
	OUT PORTB, r18
	RCALL delay
	rjmp start
delay:
	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28
	CPI R28,0x8B ;comparing if lower is 0xC6
	BRSH body
	RJMP delay
body:
	CPI R29,0x1A
	BRSH done
	RJMP delay
