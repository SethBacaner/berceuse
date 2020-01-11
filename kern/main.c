#include <arch_i386/isr.h>
#include <lib.h>
#include <tty.h>

void kmain()
{
  isr_bootstrap();
  timer_bootstrap();
  clear_screen();
  __asm__ __volatile__("sti");
  kprint("\n\nInterrupts have been bootstrapped.\n\n\n");

}
