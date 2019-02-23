;
; DA1B.asm
;
; Created: 2/22/2019 12:44:26 PM
; Author : regis
;


; Replace with your application code
.org 0x0000

start:
	;ldi XL, 0x02
	;ldi XH, 0x00
	ldi XL, low(0x0200)
	ldi XH, high(0x0200)
	ldi r16, 0x63
	ldi r17, 0x60
	ldi r18, 0x00
; Part 1: load 99 numbers between 10 and 255 starting at addr 0x0200
loadNum:
	st X, r17
	ld r20, X
	inc XL
	inc r17
	dec r16
	brne loadNum
; Check that the numbers were stored properly (delete later)
	subi XL, 0x63
	ldi r20, 0x00
	ld r20, X

; Part 2: Check if a number is divisible by 3.
	ldi r20, 0x03
; Load addr for sorting
	ldi XL, low(0x0200)
	ldi XH, high(0x0200) ; Reset Orginal list addr
	ldi YL, low(0x0400)
	ldi YH, high(0x0400) ; Numbers divisible by 3
	ldi ZL, low(0x0600)
	ldi ZH, high(0x0600) ; other numbers not divisible by 3
	ldi r21, 0x63
	ldi r24, 0x00	; Y counter
	ldi r25, 0x00	; Z counter
; initialize value to be divided
divStart:
	ldi r17, 0x00
	ld r16, X
	ld r19, X
div:
	sub r16, r20
	inc r17
	cp r16, r20
	brsh div
	cpi r16, 0x00
	brne not3
; Number is divisible by 3
is3:
	st Y, r19
	inc YL
	inc r24
	jmp endDiv
; Number is not divisible by 3
not3:
	st Z, r19
	inc ZL
	inc r25
; Increment list
endDiv:
	inc XL
	dec r21
	brne divStart

; Part 3: Find the cumulative sum of the lists of numbers
; Store sum of Y in r16:r17 and sum of Z in r18:r19
; Reset Addresses
	ldi XL, low(0x0200)
	ldi XH, high(0x0200) ; Reset Orginal list addr
	ldi YL, low(0x0400)
	ldi YH, high(0x0400) ; Numbers divisible by 3
	ldi ZL, low(0x0600)
	ldi ZH, high(0x0600) ; other numbers not divisible by 3
; Set r16:r17 and r18:r19 to 0
	ldi r16, 0x00
	ldi r17, 0x00
	ldi r18, 0x00
	ldi r19, 0x00
sumLoopY:
	ld r20, Y
	add r17, r20
	adc r16, r0
	inc YL
	dec r24
	brne sumLoopY
sumLoopZ:
	ld r20, Z
	add r19, r20
	adc r18, r0
	inc ZL
	dec r25
	brne sumLoopZ

end: rjmp end