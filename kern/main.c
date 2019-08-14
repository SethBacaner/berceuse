#include <arch_i386/isr.h>
#include <lib.h>
#include <tty.h>

void kmain()
{
  isr_bootstrap();
  clear_screen();
  kprint("Interrupts have been bootstrapped.");

  __asm__ __volatile__("int $2");
  __asm__ __volatile__("int $3");
}
