

[GLOBAL load_gdt] ;call load_gdt in c code

load_gdt:
	mov eax,[esp+4] ;get the pointer to the gdt
	lgdt [eax] ;load new gdt pointer
	
	mov ax,0x10 ;0x10 is address of second descriptor[kernel data segment] (Loading the segment selector registers is easy for the data registers)
	;load all data segment selectrors
	mov ds,ax 
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	jmp 0x08:.flush_cs ;0x08 is the address of our kernel code segment : far jump -- It will first set cs to 0x08 and then jump to flush_cs using its absolute address.
	.flush_cs: ; to load cs we have to do a “far jump”:
		ret
	
[GLOBAL load_idt] ;call load idt in c code
load_idt:
	mov eax,[esp+4]	; load the address of the IDT into register eax
	lidt [eax]		; load the IDT
	ret				; return to the calling function
