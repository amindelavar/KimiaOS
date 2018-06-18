#include <kimia/system.h>

//declare static functions
static void timer_callback(registers_t regs);
//define variables
volatile uint32 tick = 0;
volatile long_int wait_ticks = 0;
volatile uint32 useconds = 0,Rseconds=0,Rminutes=0;


static void timer_callback(registers_t regs) {
    tick++;
	wait_ticks++;
	useconds++;
    
    if(useconds == 100) {
		useconds = 0;
		Rseconds++;
		//dbg_printf(STR"Tick: %d,sec:%d\n",tick,Rseconds);
	}
    //dbg_printf(STR"Tick: %d\n",tick);
}

void timer_wait(uint32 ticks)
{
    wait_ticks = 0;
    while(wait_ticks <= ticks);
}

void init_timer(uint32 frequency){
	// setup default handler for pit
    register_interrupt_handler(IRQ0, timer_callback);
	/* Get the PIT value: hardware clock at 1193180 Hz */
    uint32 divisor = 1193180 / frequency;
	if(divisor==0)divisor++;
	// send the command byte
	outb(PIT_REG_COMMAND, 0x36);
	// spiliting divisor into upper/lower bytes
    uint8 low  = (uint8)(divisor & 0xFF);
    uint8 high = (uint8)( (divisor >> 8) & 0xFF);
    // send the frequency divisor
    outb(PIT_REG_COUNTER0, low); 	// sending lower byte
    outb(PIT_REG_COUNTER0, high); 	// sending upper byte
}