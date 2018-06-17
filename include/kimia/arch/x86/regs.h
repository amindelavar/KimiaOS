/**
 * Kimia OS
 * regs struct define
 */

#ifndef _REGS_H
#define _REGS_H

#include "types.h"

//this define what the stack looks like after an ISR was running
struct regs{
	uint32 gs,fs,es,ds;
	uint32 edi,esi,ebp,esp,ebx,edx,ecx,eax;
	uint32 int_no,err_code;
	uint32 eip,cs,eflags,useresp,ss;
};
//----------------------------------
typedef struct registers{
	uint32 ds;									//data segment selector
	uint32 edi,esi,ebp,esp,ebx,edx,ecx,eax;		//pushed by pusha
	uint32 int_no,err_code;						//intrrupt number , error code
	uint32 eip,cs,eflags,useresp,ss;			//pushed by processor automatically
}__attribute__((packed)) registers_t;
typedef registers_t* registers_ptr_t;


#endif /*_REGS_H*/
