/**
 * Kimia OS
 * init all gdt,idt,isr
 */

#ifndef _DESCRIPTOR_TABLES_H
#define _DESCRIPTOR_TABLES_H

#include "types.h"

#define KERNEL_CS		0x08
#define IDT_ENTRIES		256

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
//---------------------------------------
//this struct is value of one gdt entry
struct gdt_entry_struct{
	uint16 limit_low;		//lower 16 bits of limit 
	uint16 base_low;		//lower 16 bits of base 
	uint8 base_middle;		//next 8 bits of base
	uint8 access;			//flags,rings for this segment
	uint8 granularity;
	uint8 base_high;		//last 8 bits of base 
}__attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;
//this struct describe a gdt pointer
struct gdt_ptr_struct{
	uint16 limit;			//the upper 16 bits of all selector limits
	uint32 base;			//the address of the first gdt_entry_t struct
}__attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;
//---------------------------------------
struct idt_entry_struct{
	uint16 base_lo;			//the lower 16 bits of the address to jump to when this interrupt fires
	uint16 sel;				//kernel segment selector
	uint8 always0;
	uint8 flags;
	uint16 base_hi;
}__attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;
//this struct describe a idt pointer
struct idt_ptr_struct{
	uint16 limit;			//the upper 16 bits of all selector limits
	uint32 base;			//the address of the first idt_entry_t struct
}__attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;
//---------------------------------------
// Struct which aggregates many registers 
 struct registers_struct{
   uint32 ds; /* Data segment selector */
   uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
   uint32 int_no, err_code; /* Interrupt number and error code (if applicable) */
   uint32 eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
}__attribute__((packed));
typedef struct registers_struct registers_t;
typedef void (*isr_t)(registers_t);
//---------------------------------------
//call asm isr handlers
//Interrupt Service Routines (ISR)
extern void interrupt_handler_0();
extern void interrupt_handler_1();
extern void interrupt_handler_2();
extern void interrupt_handler_3();
extern void interrupt_handler_4();
extern void interrupt_handler_5();
extern void interrupt_handler_6();
extern void interrupt_handler_7();
extern void interrupt_handler_8();
extern void interrupt_handler_9();
extern void interrupt_handler_10();
extern void interrupt_handler_11();
extern void interrupt_handler_12();
extern void interrupt_handler_13();
extern void interrupt_handler_14();
extern void interrupt_handler_15();
extern void interrupt_handler_16();
extern void interrupt_handler_17();
extern void interrupt_handler_18();
extern void interrupt_handler_19();
extern void interrupt_handler_20();
extern void interrupt_handler_21();
extern void interrupt_handler_22();
extern void interrupt_handler_23();
extern void interrupt_handler_24();
extern void interrupt_handler_25();
extern void interrupt_handler_26();
extern void interrupt_handler_27();
extern void interrupt_handler_28();
extern void interrupt_handler_29();
extern void interrupt_handler_30();
extern void interrupt_handler_31();
//syscalls
extern void interrupt_handler_85();
extern void interrupt_handler_105();
//Interrupt Requests (IRQs)
//table of common interrupts (Maskable hardware interrupt are called IRQ):
extern void irq_handler_0 (); //32:Programmable Interrupt Timer Interrupt
extern void irq_handler_1 (); //33:Keyboard Interrupt
extern void irq_handler_2 (); //34:Cascade (used internally by the two PICs. never raised)
extern void irq_handler_3 (); //35:COM2 (if enabled)
extern void irq_handler_4 (); //36:COM1 (if enabled)
extern void irq_handler_5 (); //37:LPT2 (if enabled)
extern void irq_handler_6 (); //38:Floppy Disk
extern void irq_handler_7 (); //39:LPT1
extern void irq_handler_8 (); //40:CMOS real-time clock (if enabled)
extern void irq_handler_9 (); //41:Free for peripherals / legacy SCSI / NIC
extern void irq_handler_10(); //42:Free for peripherals / SCSI / NIC
extern void irq_handler_11(); //43:Free for peripherals / SCSI / NIC
extern void irq_handler_12(); //44:PS2 Mouse
extern void irq_handler_13(); //45:FPU / Coprocessor / Inter-processor
extern void irq_handler_14(); //46:Primary ATA Hard Disk
extern void irq_handler_15(); //47:Secondary ATA Hard Disk
//---------------------------------------
//call asm functions
extern void load_gdt(uint32);
extern void load_idt(uint32);
//---------------------------------------
void init_descriptor_tables();
void interrupt_handler(registers_t regs);
void irq_handler(registers_t regs);
void irq_install();

#endif /*_DESCRIPTOR_TABLES_H*/

