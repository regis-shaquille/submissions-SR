;
; DA2bASM.asm
;
; Created: 3/9/2019 5:09:00 PM
; Author : regis
;


; Replace with your application code
start:
.include <m328pdef.inc>
.ORG 0;location for reset
	JMP MAIN
.ORG 0x02;location for external interrupt 0
	JMP EX0_ISR
MAIN:
	LDI R20,HIGH(RAMEND)
	OUT SPH,R20
	LDI R20,LOW(RAMEND)
	OUT SPL,R20;initialize stack
	LDI R20,0x2;make INT0 falling edge triggered
	STS EICRA,R20
	SBI DDRB,2;PORTB.2 = output
	SBI PORTD,2;pull-up activated
	LDI R20,1<<INT0;enable INT0
	OUT EIMSK,R20
	SEI;enable interrupts
HERE:JMP HERE
EX0_ISR:
	IN R21,PORTB
	LDI R22,(1<<2);00100000 for toggling PB5
	EOR R21,R22
	OUT PORTB,R21
	RETI