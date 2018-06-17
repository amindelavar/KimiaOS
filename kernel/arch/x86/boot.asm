

;These are the multiboot macroes, they are used to configure how GRUB
;loads the kernel
MBOOT_PAGE_ALIGN    equ 1<<0 ;Loads everything on page boundaries
MBOOT_MEM_INFO      equ 1<<1 ;Load memory map
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Required (MAGIC)

MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

bits 32

[GLOBAL mboot]
[EXTERN code] ;.text
[EXTERN bss]  ;.bss
[EXTERN end]  ;defined in linker script
[GLOBAL start]
[EXTERN kmain]

mboot:
  dd  MBOOT_HEADER_MAGIC
  dd  MBOOT_HEADER_FLAGS
  dd  MBOOT_CHECKSUM
   
  dd  mboot
  dd  code
  dd  bss
  dd  end
  dd  start ;Initial EIP

;start point of kernel
start:
push esp ;Stack location (GRUB doesn't tell us)
push ebx ;Multiboot header location

cli
call kmain
jmp $

;hlt

;create a stack for kerrnel in memory named kernel_stack
KERNEL_STACK_SIZE   equ 4096
section .bss
align 4
kernel_stack: ; label points to beginning of memory
resb KERNEL_STACK_SIZE ; reserve stack for the kernel
mov esp , kernel_stack+KERNEL_STACK_SIZE ; point esp to the start of the stack (end of memory area)
