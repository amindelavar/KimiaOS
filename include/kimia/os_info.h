

#ifndef _OS_INFO_H
#define _OS_INFO_H

#define KERNEL_VERSION		"0.4.4"
#define OS_VERSION			"0.1"
#define OS_VERSION_NAME     "BETA"
#define OS_NAME				"KIMIA"
#define OS_BIRTH_DAY		"15.4.2018"
#define OS_ARCH				"x86" //32 bits
#define OS_BUILD_DATE       __DATE__
#define OS_BUILD_TIME       __TIME__



#endif /*_OS_INFO_H*/


/**
- start of kernel in 32 bits mode [OK]
- enter to kmain function in c [OK]
- print a char in screen [OK]
- writting basic ports functions [OK]
- writting functions for print text in kernel mode [OK]
=-=-=-=-=-=-=-=-=-=-=-=-=BUILD=-=-=-=-=-=-=-=-=-=-=-=-=
- init IDT [OK]
- init GDT [OK]
- init ISRs [OK]
- configure PIC [OK]
- init IRQs [OK]
=-=-=-=-=-=-=-=-=-=-=-=-=BUILD=-=-=-=-=-=-=-=-=-=-=-=-=
- init timer [..]
- init keyboard [..]
- implement paging memory
- init memory file system
=-=-=-=-=-=-=-=-=-=-=-=-=BUILD=-=-=-=-=-=-=-=-=-=-=-=-=
- init PCI bus
- init keyboard
- init virtual file system(vfs)
=-=-=-=-=-=-=-=-=-=-=-=-=BUILD=-=-=-=-=-=-=-=-=-=-=-=-=
- writing system calls
- init tasking
- enter to user mode
- init multi tasking
- test a user program named helloworld.exe
- implement a shell
=-=-=-=-=-=-=-=-=-=-=-=-=BUILD=-=-=-=-=-=-=-=-=-=-=-=-=
- init VGA
- init window manager
*/
