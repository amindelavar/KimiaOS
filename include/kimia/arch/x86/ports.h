/**
 * Kimia OS
 * input , output to ports
 */

#ifndef _PORTS_H
#define _PORTS_H

#include "types.h"

void outb(uint16 port,uint8 value);
uint8 inb(uint16 port);

uint16 inw (uint16 port);
void outw (uint16 port, uint16 data);



#endif /*_PORTS_H*/
