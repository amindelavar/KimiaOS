#include <kimia/system.h>


/**
 * reboot
 * restart system
 */
void reboot(){
    outb (0x64, 0xFE); /* send reboot command */
}

/**
 * sti
 * remap interupts
 */
void sti(){
     __asm__ __volatile__ ("sti");
}

/**
 * cli
 * clear all interupts
 */
void cli(){
     __asm__ __volatile__ ("cli");
}
/**
 * hlt
 * halt system
 */
void hlt(){
     __asm__ __volatile__ ("hlt");
}