/**
 * Kimia OS
 * memory functions
 */

#ifndef _MEM_H
#define _MEM_H

#include "../arch/x86/types.h"

void *memset(String dest,uint8 val,uint32 len);

void *malloc(uint32 bytes);

#endif /*_MEM_H*/
