#include <keyboard.h>

#include <arch_i386/types.h>

#include <port.h>
#include <tty.h>

static char key_buf[256];

static void print_scancode(u8 scancode);

void key_press_interrupt()
{
  u8 scancode = port_byte_in(0x60);
  // TODO: print scancode only if necessary.
  // TODO: add character to buffer or reset if necessary.
  print_scancode(scancode);
}

static void print_scancode(u8 scancode)
{
  kprint("I will print the keys you press");
  switch (scancode)
  {
    case 0x00:
      panic();
    case 0x01:
      kprint("ESC");
      break;
    case 0x02:
      kprint("1");
      break;
    case 0x1c:
      kprint("\n");
      break;
    case 0x81:
      /* Escape key release. */
      break;
    case 0x82:
      /* 1 release. */
      break;
    case 0x9c:
      /* Enter key release. */
      break;
    case 0xfd:
      /* Keyboard internal error. We should not panic(), but definitely tell
         the user. Maybe a bell? */
    default:
      panic();
  }
}
