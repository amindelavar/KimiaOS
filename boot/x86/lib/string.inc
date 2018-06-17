;*****************************************
;--------------string.inc-----------------
;*****************************************

%ifndef __STRING_INC_INCLUDED__
%define __STRING_INC_INCLUDED__


bits 16

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;Printstr16
;Print a string to the screen in 16 bits
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Printstr16:
    pusha                                                       ; save all registers
    mov ah, 0Eh                                                 ; int 10h teletype function
    .repeat:
    lodsb                                                       ; load next byte from string from SI to AL 
    cmp al, 0                                                   ; Does AL=0?
    je .complete                                                 ; Yep, null terminator found-bail out
    int 10h                                                    ;BIOS Interrupt 0x10 - Used to print characters on the screen via Video Memory 
    jmp .repeat                                               ;Loop   	
    .complete:
        popa
        ret

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;Println16
;Print a string in a line to the screen in 16 bits
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Println16:
    pusha                                                       ; save all registers
    mov ah, 0Eh                                                 ; int 10h teletype function
    .repeat:
    lodsb                                                       ; load next byte from string from SI to AL 
    cmp al, 0                                                   ; Does AL=0?
    je .complete                                                 ; Yep, null terminator found-bail out
    int 10h                                                    ;BIOS Interrupt 0x10 - Used to print characters on the screen via Video Memory 
    jmp .repeat                                               ;Loop   	
    .complete:
        call PrtLine16
        popa
        ret

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;PrtLine16
;Prints empty new lines like '\n' in 16 bits
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
PrtLine16: 
    mov al, 0	                                                ; null terminator '\0'
    stosb                                                       ; Store string 
    ;Adds a newline break '\n'
    mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov al, 0x0A 
    int 0x10
	ret

%endif ;__STRING_INC_INCLUDED__