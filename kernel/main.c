
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
	
	//String io=gets_keyboard();
	//dbg_printf(STR"GGGG:%s\n",io);
    //__asm__ __volatile__("int $7");
	//String buf="v ";
	/*append_char(buf,'h');
	append_char(buf,'i');
	append_char(buf,'!');*/

	//dbg_printf("FFF:%s\n",buf);
	 //int a=5/0;
	//dbg_printf(STR"DDD:%c\n",'r');
	//------------------------------------
	
	return 0;
}

