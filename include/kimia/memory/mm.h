#ifndef _MM_H
#define _MM_H

#define PG_UNUSED	0
#define PG_NORMAL	1
#define PG_TASK		2
#define PG_REVERSED	0xff
#define PAGE_SIZE	(4*1024)
#define MEMORY_RANGE (4*1024*1024)
//--------------------------------------------
void init_memory_management();

#endif /*_MM_H */