/*
 * timer.h
 *
 * Programmable Interval Timer
 */

#ifndef BERCEUSE_ARCH_I386_TIMER_H_
#define BERCEUSE_ARCH_I386_TIMER_H_

#include <arch_i386/isr.h>
#include <arch_i386/types.h>

u32 __volatile__ timer_ticks;

#define TIMER_COMMAND_PORT 0x43

/*
 * There are two more timer channels, but we only care about channel 0 for now.
 * We might care about channel 2 later for the speaker, however.
 */
#define TIMER_CHANNEL_0_PORT 0x40

/*
 * Access both bytes during timer bootstrapping.
 */
#define TIMER_ACCESS_MODE_LOBYTEHIBYTE 0x30

/*
 * Operating mode: square wave generator
 */
#define TIMER_SQUARE_WAVE_MODE 0x06

void timer_bootstrap();

void timer_tick_interrupt(interrupt_frame_t iframe);

#endif /* BERCEUSE_ARCH_I386_TIMER_H_ */
