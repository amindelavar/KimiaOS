;*****************************************
;--------------fat12.inc-----------------
;*****************************************

%ifndef __FAT12_INC_INCLUDED__
%define __FAT12_INC_INCLUDED__


bits 16
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;-------------VARIABLES-------------
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
bootdevice      db 0x0
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;reset_floppy
;reset floppy to again reading sectors by int 13h in 16 bits
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
reset_floppy:
    mov ah,0
    mov dl,byte [bootdevice]
    int 13h                                                 ; Reset Disk Drive (result:cf=clear if no error)
    ret

%endif ;__FAT12_INC_INCLUDED__