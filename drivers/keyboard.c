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
  // TODO: __asm__ __volatile__("hlt") when a certain scancode is received,
  // but remember to say goodbye first.
  print_scancode(scancode);
}

static void print_scancode(u8 scancode)
{
  if (scancode > 0x80) {
    // The keyboard is telling us a key has been released.
    return;
  }

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
    case 0x2a:
      kprint("lshift");
      break;
    case 0xfd:
      /* Keyboard internal error. We should not panic(), but definitely tell
         the user. Maybe a bell? */
    default:
      break;
      //panic();
  }
}
