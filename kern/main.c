#include <lib.h>
#include <tty.h>

void kmain()
{
  clear_screen();
  kprint("Hello world!");

  int* new_ints = kmalloc(4000);
  int i;
  for (i = 0; i < 500; ++i)
  {
    new_ints[i] = i;
  }

  kprint("kmalloc test");
}
