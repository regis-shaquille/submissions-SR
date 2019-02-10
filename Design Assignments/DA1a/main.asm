;
; testProject_asm.asm
;
; Created: 2/9/2019 1:13:01 PM
; Author : regis
;


.include <m328pdef.inc>

.SET	COUNT = 0x25
.SET	COUNT1 = 0x19


.ORG 0
		LDI  R24, 0x10 ;upper
		LDI  R25, 0x27 ;lower
		LDI  R22, 0x64 ;upper
		LDI  R23, 0x00 ;zeroed reg
		;LDI  R26, 0x01
loop:
		ADD  R20, R24
		ADC  R19, R25
		ADC  R18, R23
		SUBI R22, 0x01
		SUB  R22, R23
		BRNE loop
end:	jmp end 