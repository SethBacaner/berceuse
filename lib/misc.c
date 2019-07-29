/*
 * misc.c
 *
 * Implementation of miscellaneous kernel-wide functions that aren't
 * categorized.
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
