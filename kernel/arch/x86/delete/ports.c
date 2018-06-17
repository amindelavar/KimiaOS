
#include <kimia/arch/x86/ports.h>


/*void outb(uint16 port,uint8 value){
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port),"a" (value));
}*/

/*uint8 inb(uint16 port){
	uint8 ret;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (ret): "dN" (port));
	return ret;
}*/
