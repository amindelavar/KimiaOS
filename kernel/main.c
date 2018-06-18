
#include <kimia/system.h>
#include <drivers/drivers.h>

int kmain(){
	dbg_clearAll(1);
	dbg_puts(STR"\n\tIn the name of ALLAH\n\n");
	dbg_printf(STR"Welcome Kimia OS(%s)-%s\n\n",OS_VERSION,OS_ARCH);
	dbg_printf(STR"%sinit Kernel(%s)...\n",preShell,KERNEL_VERSION);
	//------------------------------------init gdt/idt
	init_descriptor_tables();
	dbg_printf(STR"%sinit GDT and IDT(ISRs)\n",preShell);
	dbg_printf(STR"%sConfigure PIC and init IRQs\n",preShell);
	irq_install();
	//String io=gets_keyboard(true);
	//uint8 io=getch_keyboard(true);
	//dbg_printf(STR"GGGG:%c\n",io);
    //__asm__ __volatile__("int $7");
	//String buf="v b";
	/*append_char(buf,'h');
	append_char(buf,'i');
	append_char(buf,'!');*/
	//dbg_printf("FFF:%s\n",buf);
	//------------------------------------init memory
	init_memory_management();
	
	return 0;
}

