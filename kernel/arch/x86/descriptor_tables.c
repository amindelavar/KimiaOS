
#include <kimia/system.h>
#include <drivers/drivers.h>



//private functions
static void init_gdt();
static void init_idt();
static void gdt_set_gate(int32 num,uint32 base,uint32 limit,uint8 access,uint8 gran);
static void idt_set_gate(uint8 num,uint32 base);
//variables
isr_t interrupt_handlers[256];
gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;
idt_entry_t idt_entries[IDT_ENTRIES];
idt_ptr_t idt_ptr;
String exception_messages[] = {
    STR"Divide by 0", 						//0:Fault
    STR"Single step (Debugger)",			//1:Trap or Fault
    STR"Non Maskable Interrupt (NMI) Pin",	//2:Unclassed
    STR"Breakpoint (Debugger)",				//3:Trap
    STR"Overflow",							//4:Trap
    STR"Bounds check",						//5:Fault
    STR"Invalid OPCode",					//6:Fault
    STR"Device not available",				//7:Fault
    STR"Double Fault",						//8:Abort
    STR"Coprocessor Segment Overrun",		//9:Abort (Reserved, do not use)
    STR"Invalid Task State Segment (TSS)",	//10:Fault
    STR"Segment Not Present",				//11:Fault
    STR"Stack Fault Exception",				//12:Fault
    STR"General Protection Fault(GPF)",		//13:Fault
    STR"Page Fault",						//14:Fault
    STR"Unassigned",						//15:-
    STR"x87 FPU Error",						//16:Fault
    STR"Alignment Check(486+ Only)",		//17:Fault
    STR"Machine Check (Pentium/586+ Only)",	//18:Abort
    STR"SIMD FPU Exception"					//19:Fault
};
//extern isr_t interrupt_handlers[];
/**
 * init_descriptor_tables
 * init gdt,idt and return a bool
 */
void init_descriptor_tables(){
	//init gdt
	init_gdt();
	//init idt
	init_idt();
}

/**
 * init_gdt
 * init gdt and return a bool
 */
static void init_gdt(){
	gdt_ptr.limit=(sizeof(gdt_entry_t)*5)-1;
	gdt_ptr.base=(uint32) &gdt_entries;
	gdt_set_gate(0,0,0,0,0);				//null segment
	gdt_set_gate(1,0,0xFFFFFFFF,0x9A,0xCF);	//kernel code segment
	gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF);	//kernel data segment
	gdt_set_gate(3,0,0xFFFFFFFF,0xFA,0xCF);	//user mode code segment
	gdt_set_gate(4,0,0xFFFFFFFF,0xF2,0xCF);	//user mode data segment
	
	load_gdt((uint32)&gdt_ptr);
}
/**
 * gdt_set_gate
 * set value of one gdt entry
 */
static void gdt_set_gate(int32 num,uint32 base,uint32 limit,uint8 access,uint8 gran){
	gdt_entries[num].base_low=(base&0xFFFF);
	gdt_entries[num].base_middle=(base>>16)&0xFF;
	gdt_entries[num].base_high=(base>>24)&0xFF;
	
	gdt_entries[num].limit_low=(limit&0xFFFF);
	gdt_entries[num].granularity=(limit>>16)&0x0F;
	
	gdt_entries[num].granularity |=gran&0xF0;
	gdt_entries[num].access=access;
}
/**
 * init_idt
 * init idt and return a bool
 */
static void init_idt(){

	// install ISRs and syscalls ints
	uint32 int_hnds[32]={
		(uint32)interrupt_handler_0,
		(uint32)interrupt_handler_1,
		(uint32)interrupt_handler_2,
		(uint32)interrupt_handler_3,
		(uint32)interrupt_handler_4,
		(uint32)interrupt_handler_5,
		(uint32)interrupt_handler_6,
		(uint32)interrupt_handler_7,
		(uint32)interrupt_handler_8,
		(uint32)interrupt_handler_9,
		(uint32)interrupt_handler_10,
		(uint32)interrupt_handler_11,
		(uint32)interrupt_handler_12,
		(uint32)interrupt_handler_13,
		(uint32)interrupt_handler_14,
		(uint32)interrupt_handler_15,
		(uint32)interrupt_handler_16,
		(uint32)interrupt_handler_17,
		(uint32)interrupt_handler_18,
		(uint32)interrupt_handler_19,
		(uint32)interrupt_handler_20,
		(uint32)interrupt_handler_21,
		(uint32)interrupt_handler_22,
		(uint32)interrupt_handler_23,
		(uint32)interrupt_handler_24,
		(uint32)interrupt_handler_25,
		(uint32)interrupt_handler_26,
		(uint32)interrupt_handler_27,
		(uint32)interrupt_handler_28,
		(uint32)interrupt_handler_29,
		(uint32)interrupt_handler_30,
		(uint32)interrupt_handler_31
		};
	for(uint32 i=0;i<32;i++){
		idt_set_gate(i,int_hnds[i]);
	}
	idt_set_gate(105,(uint32)interrupt_handler_105);
	idt_set_gate(85,(uint32)interrupt_handler_85);
	// remap the irq table (Or Remap the PIC1,PIC2)
	outb(0x20,0x11);
	outb(0xA0,0x11);
	outb(0x21,0x20);
	outb(0xA1,0x28);
	outb(0x21,0x04);
	outb(0xA1,0x02);
	outb(0x21,0x01);
	outb(0xA1,0x01);
	outb(0x21,0x0);
	outb(0xA1,0x0);
	// Install the IRQs
	uint32 irq_hnds[16]={
		(uint32)irq_handler_0,
		(uint32)irq_handler_1,
		(uint32)irq_handler_2,
		(uint32)irq_handler_3,
		(uint32)irq_handler_4,
		(uint32)irq_handler_5,
		(uint32)irq_handler_6,
		(uint32)irq_handler_7,
		(uint32)irq_handler_8,
		(uint32)irq_handler_9,
		(uint32)irq_handler_10,
		(uint32)irq_handler_11,
		(uint32)irq_handler_12,
		(uint32)irq_handler_13,
		(uint32)irq_handler_14,
		(uint32)irq_handler_15
	};
	for(uint32 i=32;i<32+16;i++){
		idt_set_gate(i,irq_hnds[i-32]);
	}
	// set idt
	idt_ptr.limit=(sizeof(idt_entry_t)*IDT_ENTRIES)-1;
	idt_ptr.base=(uint32) &idt_entries;
	load_idt((uint32)&idt_ptr);
	//memset((String) &idt_entries,0,sizeof(idt_entry_t)*IDT_ENTRIES);
}
/**
 * idt_set_gate
 * set value of one idt entry
 */
static void idt_set_gate(uint8 num,uint32 base){
	idt_entries[num].base_lo=base&0xFFFF;
	idt_entries[num].base_hi=(base>>16)&0xFFFF;
	
	idt_entries[num].sel=KERNEL_CS;
	idt_entries[num].always0=0;
	//it sets the interrupt gate's privilege level to 3
	idt_entries[num].flags=0x8E;
	return;
}
/**
irq_handler
handles IRQ interrupts
*/
void irq_handler(registers_t regs){
	uint32 interrupt=regs.int_no;
	// Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (interrupt >= 40){
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master.
    outb(0x20, 0x20);
	// Handle the interrupt in a more modular way
    if (interrupt_handlers[interrupt] != 0)
    {   
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

/**
interrupt_handler
handles ISR interrupts
*/
void interrupt_handler(registers_t regs){
	uint32 interrupt=regs.int_no;
	Boolean is_exception=true;
	//--------------------------------------------
	//system call interrupt
	if(interrupt==105||interrupt==85){
		
	}
	//messaged interrupt
	if(interrupt>=0&&interrupt<20){
		dbg_printf(STR"Recieved interrupt %d [err=%d]: %s\n", interrupt, regs.err_code, exception_messages[interrupt]);
	}
	//Reserved interrupt
	else if(interrupt>=20&&interrupt<=31){
		dbg_printf(STR"Recieved interrupt %d [err=%d]: %s\n", interrupt, regs.err_code,"Reserved");
	}
	//Available for software use
	else if(interrupt>31&&interrupt<=255){
		dbg_printf(STR"Available for software use : %i,%i\n",interrupt,regs.err_code);
		is_exception=false;
	}
	//unknown interrupt
	else{
		dbg_printf(STR"unhandled interrupt : %i,%i\n",interrupt,regs.err_code);
		
	}
	//--------------------------------------------
	if(is_exception){
	set_panic(__LINE__,STR __FILE__,STR"Kernel Exception");
	}

}

/**

*/
void register_interrupt_handler(uint8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

/**
irq_install
install and init IRQ interrupts and its devices
*/
void irq_install(){
 	// Enable interruptions
    sti();
    // IRQ0: timer
	dbg_printf(STR"%sinit Timer\n",preShell);
	//for(int i=0;i<10;i++){
    init_timer(50);
	//}
    // IRQ1: keyboard
    init_keyboard();
	
}
