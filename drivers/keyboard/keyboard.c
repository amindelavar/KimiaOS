
//#include <kimia/system.h>


#include <kimia/arch/x86/types.h>
//--------------------------------------
#include <drivers/keyboard/keyboard.h>
//--------------------------------------
#include <drivers/keyboard/keymaps/keymap_us.h>

/** 
getch_keyboard
Reads a scan code from the keyboard(NOT an ASCII character!)
*/
uint8 getch_keyboard(){
	uint8 getch_char=0;
   /* if(kbdus[inb(KBD_DATA_PORT)] != 0) //Not empty
     outb(KBD_DATA_PORT,0xf4); //Clear buffer
     
     while(kbdus[inb(KBD_DATA_PORT)] == 0); //While buffer is empty
     getch_char = kbdus[inb(KBD_DATA_PORT)];
     outb(KBD_DATA_PORT,0xf4); //Leave it emptying*/
     return getch_char;
}
/**
init_keyboard
*/
void init_keyboard(){

}
/**
gets_keyboard
*/
String gets_keyboard(){
	/*Boolean reading=true;
	String buffer="";
	while(reading){
		if(inb(KBD_DATA_PORT)>0){

		}
	}*/
	return 0;
}

/**
inb
*/
uint8 inb(uint16 port){
	uint8 ret;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (ret): "dN" (port));
	return ret;
}


