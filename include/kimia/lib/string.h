/**
 * Kimia OS
 * includes String functions
 */

#ifndef _STRING_H
#define _STRING_H

#include "../arch/x86/types.h"

void int_to_str(int32 num,uint8 ret[]);

void str_reverse(uint8 s[]);

uint32 str_len(String str);

uint8  str_compare(String s1,String s2);

void append_char(String buf,uint8 ch);

#endif /*_ISR_H*/
