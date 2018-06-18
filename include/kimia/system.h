/**
 * Kimia OS
 * All header files that kernel need it.
 */
#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "os_info.h"
//----------------------------------x86 architecture
#ifdef Arch_x86
#include "arch/x86/types.h"
#include "arch/x86/descriptor_tables.h"
#include "arch/x86/ports.h"
#include "arch/x86/timer.h"
#include "arch/x86/cpu.h"
#include "arch/x86/panic.h"
#endif
//----------------------------------display
#include "debug_display.h"
//----------------------------------memory
#include "memory/mm.h"
//----------------------------------lib
#include "lib/string.h"
#include "lib/mem.h"



#endif /*_SYSTEM_H*/
