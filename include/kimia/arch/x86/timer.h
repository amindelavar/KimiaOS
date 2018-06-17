/**
 * Kimia OS
 * PIT Timer
 */

#ifndef _TIMER_H
#define _TIMER_H


#define BCD2BIN(bcd)        ((((bcd)&15) + ((bcd)>>4)*10))
#define MINUTE              60
#define HOUR                (60*MINUTE)
#define DAY                 (24*HOUR)
#define YEAR                (365*DAY)

#define PIT_REG_COUNTER0	0x40
#define PIT_REG_COUNTER1	0x41
#define PIT_REG_COUNTER2	0x42
#define PIT_REG_COMMAND		0x43

#define PIT_FREQUENCY		1193180
//----------------------------------------------
void init_timer(uint32 frequency);
void timer_wait(uint32 ticks);

#endif /*_TIMER_H*/
