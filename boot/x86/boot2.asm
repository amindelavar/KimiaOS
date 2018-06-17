bits 16

org 0x500

jmp main                                            ; go to start entry point
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;-------------INCLUDE---------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
%include "lib/string.inc"
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;-------------VARIABLES-------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
LoadingMsg db "Searching for KIMIA Operating System...",0x0


;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;---------------main---------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
main:
    ; Setup segments and stack
    cli	                                            ; clear interrupts
	xor		ax, ax                                  ; null segments
	mov		ds, ax
	mov		es, ax
	mov		ax, 0x0000                              ; stack begins at 0x9000-0xffff
	mov		ss, ax
	mov		sp, 0xFFFF
	sti	                                            ; enable interrupts

    mov si, LoadingMsg                              ; print LoadingMsg 
    call Println16
