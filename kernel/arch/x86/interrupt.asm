
[extern interrupt_handler] 
[extern irq_handler]
;--------------------------------------------------------
%macro ISR_NOERRCODE 1
	global interrupt_handler_%1
	interrupt_handler_%1:
		cli
		push byte 0						; push 0 as error code
		push byte %1					; push the intrrupt number
		jmp common_interrupt_handler	; jump to the common handler
%endmacro
;--------------------------------------------------------
%macro ISR_ERRCODE 1
	global interrupt_handler_%1
	interrupt_handler_%1:
		cli
		push byte %1					; push the intrrupt number
		jmp common_interrupt_handler	; jump to the common handler
%endmacro
;--------------------------------------------------------
%macro IRQ 2							; get two parameters
	global irq_handler_%1
	irq_handler_%1:
		cli
		push byte 0
		push byte %2
		jmp common_irq_handler
%endmacro
;--------------------------------------------------------
%macro push_regs 0
	push eax
	push edx
	push ecx
	push ebx
	push ebp
	push esi
	push edi
%endmacro
;--------------------------------------------------------
%macro pop_regs 0
	pop edi
    pop esi
    pop ebp
    pop ebx
    pop ecx
    pop edx
    pop eax
%endmacro
;--------------------------------------------------------
common_interrupt_handler:				; the common parts of the generic interrupt handler
	; save the registers
	;push_regs
	pusha 								; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds 							; Lower 16-bits of eax = ds.
	push eax							; save the data segment descriptor
	mov ax, 0x10  						; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	; call the C function
	call interrupt_handler
	;restore the registers
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	;pop_regs
	; restore the esp
	add esp,8								; (because of the error code and the interrupt number pushed earlier).
	sti
	; return to the code that got interrupted
	iret									; interrupt return (pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP)
;--------------------------------------------------------
common_irq_handler:
	; save the registers
	;push_regs
	pusha 
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	; call the C function
	call irq_handler
	;restore the registers
	pop ebx  								; Different than the ISR code
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
	;pop_regs
	add esp, 8
	sti
	iret
;--------------------------------------------------------
ISR_NOERRCODE	0							; create handler for interrupt 0
ISR_NOERRCODE	1
ISR_NOERRCODE	2
ISR_NOERRCODE	3
ISR_NOERRCODE	4
ISR_NOERRCODE	5
ISR_NOERRCODE	6
ISR_NOERRCODE	7
ISR_ERRCODE		8
ISR_NOERRCODE	9
ISR_ERRCODE		10
ISR_ERRCODE		11
ISR_ERRCODE		12
ISR_ERRCODE		13
ISR_ERRCODE		14
ISR_NOERRCODE	15
ISR_NOERRCODE	16
ISR_NOERRCODE	17
ISR_NOERRCODE	18
ISR_NOERRCODE	19
ISR_NOERRCODE	20
ISR_NOERRCODE	21
ISR_NOERRCODE	22
ISR_NOERRCODE	23
ISR_NOERRCODE	24
ISR_NOERRCODE	25
ISR_NOERRCODE	26
ISR_NOERRCODE	27
ISR_NOERRCODE	28
ISR_NOERRCODE	29
ISR_NOERRCODE	30
ISR_NOERRCODE	31
;syscalls
ISR_NOERRCODE	105
ISR_NOERRCODE	85

;IRQs
IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47



