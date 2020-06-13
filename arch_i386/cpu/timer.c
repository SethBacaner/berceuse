#include <arch_i386/timer.h>

#include <arch_i386/isr.h>
#include <arch_i386/types.h>

#include <port.h>

u32 timer_ticks = 0;

void timer_bootstrap()
{
  u16 divisor = 4096;

  port_byte_out(TIMER_COMMAND_PORT, TIMER_ACCESS_MODE_LOBYTEHIBYTE
                                    | TIMER_SQUARE_WAVE_MODE);
  port_byte_out(TIMER_CHANNEL_0_PORT, (u8)(divisor & 0xFF));
  port_byte_out(TIMER_CHANNEL_0_PORT, (u8)(divisor >> 8));
}

void timer_tick_interrupt(interrupt_frame_t iframe)
{
  if (timer_ticks == 1000)
  {
    timer_ticks = 0;
  }
  else
  {
    timer_ticks++;
  }
}
