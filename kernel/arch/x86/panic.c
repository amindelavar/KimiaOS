#include <kimia/system.h>


void set_panic(uint32 line,String filename,String msg){
    //if(filename[0]==0)
        //filename=STR__FILE__;
    dbg_puts(STR"\n\t=-=-=-=-=PANIC=-=-=-=-=\n");
    dbg_printf(STR"KERNEL PANIC :: %s [%s - Line %d]",msg,filename,line);
    dbg_puts(STR"\n\t=-=-=-=-=-=-=-=-=-=-=-=\n");
    cli();
    hlt();
}