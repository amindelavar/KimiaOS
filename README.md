KimiaOS
===========

This is a hobby operating system that could Introduction of a real operating system.

Properties
--------
VERSION         0.4.7
ARCH            x86
VERSION_NAME    BETA
BIRTH_DAY       15.4.2018

Features
--------
- printf,puts functions for debugging kernel
- Full implementation GDT/IDT(ISR-IRQ)



TODO
--------
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
- init timer [OK]
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


Contributing
------------

I'm still learning this. For the moment, please restrict your contributions to fixing possible bugs
or improving existing documents. I'm not yet ready to accept enhancements.
