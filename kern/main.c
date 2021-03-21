#include <arch_i386/isr.h>
#include <lib.h>
#include <tty.h>

void kmain()
{
  isr_bootstrap();
  timer_bootstrap();
  clear_screen();
  __asm__ __volatile__("sti");

  int result1 = kstrcmp("abce", "abcd");
  kprint("\n");
  kprint_hex(result1);

  int result2 = kstrcmp("", "");
  kprint_hex(result2);
  kprint("\n\n");

}
