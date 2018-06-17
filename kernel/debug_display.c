
#include <kimia/system.h>

//**************************************variables
const String preShell=STR" > ";
String vidmem=(String)0x000b8000;
uint8 fg_txt=15,bg_txt=0;
uint8 attrib=15;
uint16 cur_x=0,cur_y=0;
uint32 w_con=80,h_con=25;
uint16 tab_size=8;
/**
 * dbg_putc
 * get a char to print and return a char as status of print
 */
Boolean dbg_putc(int8 c){
	if(c==0){
	return false;
	}
	if(c==(int8)'\n'){
		dbg_gotoxy(0,cur_y+1);
	}else if(c==(int8)'\r'){
		dbg_gotoxy(0,cur_y);
	}else if(c==(int8)'\t'||c==0x09){
		dbg_gotoxy(cur_x+tab_size,cur_y);
	}else if(c==(int8)'\b'){
		
	}else{
		int16 loc=(cur_y*w_con+cur_x)*2;
		vidmem[loc]=c;
		vidmem[loc+1]=attrib;
		dbg_gotoxy(cur_x+1,cur_y);
	}
	return true;
}
/**
 * dbg_puts
 * get a string and print it and return a char as status of print
 */
Boolean dbg_puts(String s){
	uint16 i=0;
	for(;;){
		if(s[i]=='\0'){
			break;
		}
		Boolean b=dbg_putc(s[i]);
		if(!b){
			return false;
		}
		i++;
	}
	return true;
}
/**
 * dbg_gotoxy
 * get x , y and set it as cur_x,cur_y and return bool
 */
Boolean dbg_gotoxy(uint16 x,uint16 y){
	cur_x=x;
	cur_y=y;
	//--------------------------------
	for(;;){
		if(cur_x>=w_con){
			cur_y++;
			cur_x=cur_x-w_con;
		}else if(cur_y>=h_con){
			cur_y--;
			dbg_scroll(1);
		}else{
			break;
		}
	}
	//--------------------------------
	uint16 tmp=(cur_y*w_con)+cur_x;
	outb(0x3d4,14);
	outb(0x3d5,tmp>>8);
	outb(0x3d4,15);
	outb(0x3d5,tmp);
	
	return true;
}
/**
 * dbg_scroll
 * get a number that scroll by it and return a bool
 */
Boolean dbg_scroll(uint16 sc){
	
	return true;
}
/**
 * dbg_clearAll
 * clear all of screen with a color and return a bool
 */
Boolean dbg_clearAll(uint8 color){
	bg_txt=color;
	uint8 col=bg_txt<<4;
	for(uint16 i=0;i<h_con;i++){
		for(uint16 b=0;b<w_con;b+=2){
			uint16 c=(i*w_con)+b;
			vidmem[c]='\0';
			vidmem[c+1]=col;
		}
	}
	dbg_setColor(fg_txt);
	return true;
}
/**
 * dbg_setColor
 * set a foreground color for printing text
 */
Boolean dbg_setColor(uint8 c){
	/*
	 * 0 : black
	 * 1 : blue
	 * 2 : green
	 * 3 : cyan
	 * 4 : red
	 * 5 : magenta
	 * 6 : brown
	 * 7 : light gray
	 * 8 : dark gray
	 * 9 : light blue
	 * 10 : light green
	 * 11 : light cyan
	 * 12 : light red
	 * 13 : light magenta
	 * 14 : light brown
	 * 15 : white
	 */
	 if(c>15){
		 c=15;
	 }
	 attrib=(bg_txt<<4)|(c&0x0f);

	return true;
}
 
/**
 * dbg_printf
 * print a string by some arguments and return a bool
 */
Boolean dbg_printf(String format,...){
	String *argvs=(String *) &format;
	argvs++;
	uint32 c=0;
	uint8 ret[30];
	String str;
	uint32 u32;
	uint8 u8;
	while((c=*format++)!=0){
		if(c!='%'){
			dbg_putc(c);
		}else{
			c=*format++;
			switch(c){
				case 'c':
					u8=*(char *)argvs++;
					dbg_putc(u8);
					break;
				case 's':
					str=*argvs++;
					if(!str)
						str=STR"(null)";
					while(*str){
						dbg_putc(*str++);
					}
					break;
				case 'b':
					u32=*(int *)argvs++;
					if(u32==false)
						dbg_puts(STR"false");
					else
						dbg_puts(STR"true");
					break;
				case 'd':
					int_to_str(*((int *)argvs++),ret);
					for(uint16 i=0;i<30;i++){
						if(ret[i]==0)
							break;
						dbg_putc((uint8)ret[i]);
					}
					break;
				default:
					dbg_putc(*(int *)argvs++);
					
			}
		}
	}
	
	
	return true;
}
 
 
 
