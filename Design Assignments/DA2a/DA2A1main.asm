;
; DA2A.asm
;
; Created: 3/2/2019 1:21:47 PM
; Author : regis
;


; Replace with your application code
start:
.org 0
	LDI R16,4
	SBI DDRB, 0x2 ;PB2 as output
	LDI R17,0 ;needed to toogle led
	out PORTB,R17
	LDI R20,5 ;to set prescaler
	STS TCCR1B,R20 ;Prescaler: 1024
	LDI R18, 0
begin:
	RCALL delay ;calling timer to wait for 1 sec
	EOR R17,R16 ;XOR to toogle led
	out PORTB,R17
	RCALL delay2 ;calling timer to wait for 1 sec
	EOR R17,R16 ;XOR to toogle led
	out PORTB,R17
	RJMP begin ;repeating i.e, while(1)
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
delay2:
	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28
	CPI R28,0xB2 ;comparing if lower is 0xC6
	BRSH body2
	RJMP delay2
body2:
	CPI R29,0x11
	BRSH done
	RJMP delay2
done:
	LDI R20,0x00
	STS TCNT1H,R20 ;resetting the counter to 0 for next round
	LDI R20,0x00
	STS TCNT1L,R20 ;resetting the counter to 0 for next round
	RET