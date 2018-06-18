
#include <kimia/system.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/keyboard/keymaps/keymap_us.h>
//--------------------------------------
#define UNUSED(x) (void)(x)
//static functions
static void keyboard_callback(registers_t regs);
//variables
uint16 ltmp=0;
uint8 Endup=0; //1:Enter,2:Char
 uint8 buffer[256],export_buf[256];
String Kb_layout=STR"en-us";
volatile uint32 kb_count = 0; //Position in buffer
Boolean caps_flag=false,shift_flag=false,print_flag=false,gets_flag=false;

/**
 keyboard_callback
 read a key interrpt from keyboard and analyze it
*/
static void keyboard_callback(registers_t regs){
	//Read scancode
    uint8 scancode = inb(0x60);
     //Check Endup
	if(buffer[0]>0&&Endup==2){
		gets_flag=false;
		return;
	} 
	//caps lock,num lock, scroll lock
    switch (scancode)
    {
           case 0x3A:
                /* CAPS_LOCK LEDS */
                outb(0x60,0xED);
                ltmp |= 4;
                outb(0x60,ltmp);
                
                if(caps_flag) caps_flag=false;
                else caps_flag=true;
                break;
           case 0x45:
                /* NUM_LOCK LEDS */
                outb(0x60,0xED);
                ltmp |= 2;
                outb(0x60,ltmp);
                break;
           case 0x46:
                /* SCROLL_LOCK LEDS */
                outb(0x60,0xED);
                ltmp |= 1;
                outb(0x60,ltmp);
                break;
           default:
                break;
    }
	// if Key release
    if (scancode & 0x80)
    {
        //Left and right shifts
        if (scancode - 0x80 == 42 || scancode - 0x80 == 54)
			shift_flag = false;
    } 
	//if Keypress (normal)
	else {   
        //Shift
        if (scancode == 42 || scancode == 54)
		{
			shift_flag = true;
			return;
		}
		uint8 kb_char=return_key_value(scancode);
        //analyzing char
        if(scancode == ENTER)
        {
			//dbg_printf("\nHHH:%s,%d\n",buffer,kb_count);
             for(uint32 tmp=0;tmp<kb_count; tmp++){
				export_buf[tmp]=buffer[tmp];
                buffer[tmp] = 0;    
			 }
			 kb_count=0;
			 //Check Endup
			if(scancode==ENTER&&Endup==1){
		 		gets_flag=false;
		 		return;
			}       
        } else {
			//backspace key
             if((scancode == BACKSPACE||scancode==0x09)&&kb_count)
             {
                  buffer[kb_count--] = 0;
             }else if(kb_char>0){
				 buffer[kb_count++] =kb_char; 
			 }
			 
        } 
		// print char
		if(print_flag)
			dbg_putc(kb_char);
	}
}

uint8 return_key_value(uint8 code){
	//dbg_printf("Key:%d\n",code);
	//non-printable chars
	if(code==0||code==1||code==14||code==15||code==28||code==29||code==56||code==58){
		switch(code){
			case 0: //ERROR
			case 1: //Esc
				return 0;
			case 14: //Backspace
				return '\b';
			case 15: //Tab
				return '\t';
			case 28: //Enter
				return '\n';
			case 29: //Ctrl
				return 0;
			case 56: //Alt
				return 0;
			case 58: //Capsloack
				return 0;
		}
	}
	//special non-printable chars
	if(code==72||code==75||code==77||code==80){
		switch(code){
			case 72: //Up arrow
				return 0;
			case 75: //Left arrow
				return 0;
			case 77: //Right arrow 
				return 0;
			case 80: //Down arrow 
				return 0;
			//F1..F12
		}
	}
	//any unknown chars
	if(code>57){
		return 0;
	}
	//printable chars
	//-------en-us keyboard layout-------
	if(str_compare(Kb_layout,STR"en-us")==0){
		if(!shift_flag&&!caps_flag)
			return kb_us[code];
		else
			return kb_us_shift[code];
    }   
	
	//return	
	return 0;
}

/** 
getch_keyboard
Reads a scan code from the keyboard(NOT an ASCII character!)
*/
uint8 getch_keyboard(Boolean is_printed){
   	init_keyboard(is_printed);
	Endup=2;
	while(gets_flag);
	dbg_putc('\n');
	remove_interrupt_handler(IRQ1);
     return buffer[0];
}
/**
init_keyboard
*/
void init_keyboard(Boolean is_printed){
	 register_interrupt_handler(IRQ1, &keyboard_callback);
	 print_flag=is_printed;
	 gets_flag=true;
}
/**
gets_keyboard
*/
String gets_keyboard(Boolean is_printed){
	init_keyboard(is_printed);
	Endup=1;
	while(gets_flag);
	dbg_putc('\n');
	remove_interrupt_handler(IRQ1);
	return (String)export_buf;
}



