/**
 * Kimia OS
 * text mode functions for debugging kernel
 */

#ifndef _DEBUG_DISPLAY_H
#define _DEBUG_DISPLAY_H

const String preShell;

Boolean dbg_putc(int8 c);
Boolean dbg_puts(String s);
Boolean dbg_printf(String format,...);


Boolean dbg_clearAll(uint8 color);
Boolean dbg_setColor(uint8 c);

Boolean dbg_gotoxy(uint16 x,uint16 y);
Boolean dbg_scroll(uint16 sc);





#endif /*_DEBUG_DISPLAY_H*/
