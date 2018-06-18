#ifndef _KEYBOARD_H
#define _KEYBOARD_H


#define KBD_DATA_PORT       0x60
#define BACKSPACE           0x0E
#define ENTER               0x1C
//--------------------------------------
void init_keyboard(Boolean is_printed);
uint8 getch_keyboard(Boolean is_printed);
String gets_keyboard(Boolean is_printed);
uint8 return_key_value(uint8 code);

#endif /* _KEYBOARD_H */