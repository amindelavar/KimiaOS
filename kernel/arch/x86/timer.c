#include <kimia/system.h>




void init_timer(uint32 frequency){
/*
// setup default handler for pit
	register_isr( 32, &pit_irq_handler );

	// 
	u32_t divisor = PIT_FREQUENCY / freq ;
	
	if (!divisor)
	{
		divisor++;
	}
	
	// send the command byte
	outb ( PIT_REG_COMMAND, 0x36 );

	// spiliting divisor into upper/lower bytes
	u8_t l = (u8_t)( divisor & 0xFF );
	u8_t h = (u8_t)( (divisor >>8) & 0xFF );

	// send the frequeny divisor
	outb( PIT_REG_COUNTER0, l  ); // sending lower byte
	outb( PIT_REG_COUNTER0, h ); // sending upper byte	
*/
//OR
/*
// Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
*/
}