
#include <kimia/lib/mem.h>

/**
 * memset
 * write len copies of val into dest
 */
void *memset(String dest,uint8 val,uint32 len){
	String tmp=dest;
	for(;len!=0;len--)
		*tmp++=val;
	return tmp;
}

void *malloc(uint32 bytes){
	String tmp=0;
	/*for(;bytes!=0;bytes--)
		*tmp++;
	*tmp++=0;*/
	return tmp;
}



