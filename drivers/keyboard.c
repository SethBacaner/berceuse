#include <keyboard.h>

#include <arch_i386/types.h>

#include <lib.h>
#include <port.h>
#include <tty.h>

static char key_buf[256];

static void print_scancode(u8 scancode);

void keyboard_interrupt()
{
  u8 scancode = port_byte_in(0x60);

  // TODO: add character to buffer or reset if necessary.
  print_scancode(scancode);
}

static void print_scancode(u8 scancode)
{
  // The keyboard is telling us a key has been released. We are ignoring these
  // for now.
  if (scancode & 0x80) {
    return;
  }

  switch (scancode)
  {
    case 0x00:
      kprint("keyboard error");
    case 0x01:
      // Esc.
      break;
    case 0x02:
      kprint("1");
      break;
    case 0x03:
      kprint("2");
      break;
    case 0x04:
      kprint("3");
      break;
    case 0x05:
      kprint("4");
      break;
    case 0x06:
      kprint("5");
      break;
    case 0x07:
      kprint("6");
      break;
    case 0x08:
      kprint("7");
      break;
    case 0x09:
      kprint("8");
      break;
    case 0x0a:
      kprint("9");
      break;
    case 0x0b:
      kprint("0");
      break;
    case 0x0c:
      kprint("-");
      break;
    case 0x0d:
      kprint("=");
      break;
    case 0x0e:
      // this is backspace
    case 0x0f:
      kprint("    ");
      break;
    case 0x10:
      kprint("Q");
      break;
    case 0x11:
      kprint("W");
      break;
    case 0x12:
      kprint("E");
      break;
    case 0x13:
      kprint("R");
      break;
    case 0x14:
      kprint("T");
      break;
    case 0x15:
      kprint("Y");
      break;
    case 0x16:
      kprint("U");
      break;
    case 0x17:
      kprint("I");
      break;
    case 0x18:
      kprint("O");
      break;
    case 0x19:
      kprint("P");
      break;
    case 0x1a:
      kprint("[");
      break;
    case 0x1b:
      kprint("]");
      break;
    case 0x1c:
      kprint("\n");
      break;
    case 0x1d:
      // LCtrl.
      break;
    case 0x1e:
      kprint("A");
      break;
    case 0x1f:
      kprint("S");
      break;
    case 0x20:
      kprint("D");
      break;
    case 0x21:
      kprint("F");
      break;
    case 0x22:
      kprint("G");
      break;
    case 0x23:
      kprint("H");
      break;
    case 0x24:
      kprint("H");
      break;
    case 0x25:
      kprint("K");
      break;
    case 0x26:
      kprint("L");
      break;
    case 0x27:
      kprint(";");
      break;
    case 0x28:
      kprint("'");
      break;
    case 0x29:
      kprint("`");
      break;
    case 0x2a:
      // LShift.
      break;
    case 0x2b:
      kprint("\\");
      break;
    case 0x2c:
      kprint("Z");
      break;
    case 0x2d:
      kprint("X");
      break;
    case 0x2e:
      kprint("C");
      break;
    case 0x2f:
      kprint("V");
      break;
    case 0x30:
      kprint("B");
      break;
    case 0x31:
      kprint("N");
      break;
    case 0x32:
      kprint("M");
      break;
    case 0x33:
      kprint(",");
      break;
    case 0x34:
      kprint(".");
      break;
    case 0x35:
      kprint("/");
      break;
    case 0xfd:
      kprint("keyboard internal error");
      break;
    case 0xff:
      kprint("keyboard error");
      break;
    default:
      break;
  }
}
