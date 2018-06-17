bits 16                                     ; real mode
org 0                                       ; Tells the assembler to consider this as the base address

jmp short main                              ; Jump to start main() entry-point 
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;-------------INCLUDE---------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
%include "lib/string.inc"
%include "lib/fat12.inc"
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;-------------VARIABLES-------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
%DEFINE BOOTLOAD_VER '0.0.6'	            ; Bootloader version number
intro           db "Please Wait...",0x0
HELLO           db "KIMIA bootloader (v ",BOOTLOAD_VER,")",0x0
op_progress     db ".",0x0
bootStage2      db "BOOT2   BIN",0X0        ;filename must be 11 chars
firstSector     dw 0
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;----------other functions----------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;---------------main----------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
main:
    ;code located at 0000:7C00, update the segment registers 
    cli                                     ; Clear interrupts 
    ;Setup stack segments
    mov ax,0x7c0         
    mov ds,ax   
    mov es,ax               
    mov ss,ax
    mov fs,ax
    mov gs,ax
    ;create stack
    mov ax,0x0000                           ; set the stack
    mov ss,ax                               ; set stack segment
    mov sp,0xFFFF                           ; set stack pointer as last pointer(stack grows bottom to top)              
    sti                                     ; Enable interrupts 
    mov [bootdevice],dl
    ;print HELLO , intro
    mov si, HELLO 
    call Println16
    mov si, intro 
    call Println16
    ; Set up arguments to int 13h
    mov bx,buffer                           ; buffer address pointer
    mov ah,0x2                              ; always is 2
    mov al,1                                ; sectors to read count (read 1 sector)
    mov ch,0                                ; cylinder address
    mov cl,2                                ; sector address
    mov dh,1                                ; head address
    mov dl,0                                ; Drive number
    pusha                                   ;push all registers to stack (push all)
    load_root:
        int 13h                             ; Read Sectors From Drive (results:cf=clear if no error,ah=return code,al=actual sectors read count)
        jnc loaded_root                     ; jnc(jump no carry[cf])
        call reset_floppy
        jmp load_root

    loaded_root:
        mov si,op_progress
        call Printstr16
        popa
        mov di,buffer
        mov cx,224
        search_loop:
            push cx
            push di
            mov al,bootStage2
            mov cx,11
            repe cmpsb                      ; repe comsb(repeat with equal compare string bytes)
            pop di
            je found_file                   ; jump if equal(je)
            pop cx
            add di,32
            loop search_loop                ; lopp with cx counter
            int 18h                         ; crash system

        found_file:
            mov ax,word[di+15]
            mov word[firstSector],ax
            ; Set up arguments to int 13h
            mov bx,buffer                           ; buffer address pointer
            mov ah,0x2                              ; always is 2
            mov al,9                                ; sectors to read count (read 1 sector)
            mov ch,0                                ; cylinder address
            mov cl,2                                ; sector address
            mov dh,0                                ; head address
            pusha
        load_fat:
            int 13h
            ;jnc loaded_fat
            call reset_floppy
            jmp load_fat
        ;loaded_fat:




;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;---------FINISH STAGE1-------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
times 510-($-$$) db 0                        ; fill the rest by 0
dw 0xAA55                                    ; boot signature  

buffer:                                      ; byte 513