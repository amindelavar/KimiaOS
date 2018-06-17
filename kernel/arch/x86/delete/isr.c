#include <kimia/system.h>

isr_t interrupt_handlers[256];

/**
 * register_interrupt_handler
 * 
 */
void register_interrupt_handler(uint8 n,isr_t handler){
	interrupt_handlers[n]=handler;
}
/**
 * isr_handler
 * called by isr_common_stub in interrupt.asm
 */
void isr_handler(registers_t regs){
	uint8 int_no=regs.int_no &0xff;
	if(interrupt_handlers[int_no]!=0){
		isr_t handler=interrupt_handlers[int_no];
		handler(&regs);
		return;
	}else{
		dbg_printf("unhandled interrupt : %i,%i\n",regs.int_no,regs.err_code);
	}
}
/**
 * irq_handler
 * called by irq_common_stub in interrupt.asm
 */
void irq_handler(registers_t regs){
	//send an EOI(end of interrupt) signal to PICs
	if(regs.int_no>=40){
		outb(0xA0,0x20); //send reset signal to slave PIC
	}
	outb(0x20,0x20); //send reset signal to master PIC
	if(interrupt_handlers[regs.int_no]!=0){
		isr_t handler=interrupt_handlers[regs.int_no];
		handler(&regs);
		return;
	}
}
