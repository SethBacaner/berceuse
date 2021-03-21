/*
 * misc.c
 *
 * Implementation of miscellaneous kernel-wide functions.
 */

#include <lib.h>

#include <tty.h>

/*
 * Loops infinitely in case of a fatal error.
 */
void panic()
{
  /* TODO: Should probably turn interrupts off when we arrive here. */

  kprint("Something fatal happened. Panicing!");
  for(;;);
}

/*
 * The expansion of the KASSERT(expr) macro from lib.h comes here.
 *
 * Can't actually print any of these arguments yet, because we don't have
 * kmalloc for the strings and a method that converts an integral type to a
 * string for the line number.
 */
 void assert_failed(const char *expr,
                    const char *file,
                    int line,
                    const char *func)
{
  (void)expr;
  (void)file;
  (void)line;
  (void)func;

  panic();
}

int kstrcmp(const char *str1, const char *str2)
{
  char c1 = *str1;
  char c2 = *str2;

  while (c1 != '\0' || c2 != '\0') {
    if (c1 != '\0' && c2 == '\0') {
      return 1;
    } else if (c1 == '\0' && c2 != '\0') {
      return -1;
    } else if (c1 > c2) {
      return 1;
    } else if (c1 < c2) {
      return -1;
    }

    c1 = *(++str1);
    c2 = *(++str2);
  }

  return 0;
}

void kprint_hex(unsigned int n)
{
  char buf[11];
  buf[0] = '0';
  buf[1] = 'x';
  buf[10] = '\0';

  unsigned int remainder;
  unsigned int quotient = n;

  int i = 9;
  while (i > 1)
  {
    remainder = quotient % 16;
    if (remainder < 10)
    {
      buf[i] = 48 + remainder;
    }
    else
    {
      buf[i] = 55 + remainder;
    }

    quotient /= 16;

    i--;
  }

  kprint(buf);
}
