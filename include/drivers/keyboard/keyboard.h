#ifndef _KEYBOARD_H
#define _KEYBOARD_H


#define KBD_DATA_PORT       0x60
#define BACKSPACE           0x0E
#define ENTER               0x1C
//--------------------------------------
void init_keyboard();
uint8 getch_keyboard();
String gets_keyboard();
uint8 inb(uint16 port);


#endif /* _KEYBOARD_H */