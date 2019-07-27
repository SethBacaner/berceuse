#include <tty.h>

#include <port.h>

static void kprint_at(char *str, int col, int row);
static int print_char(char c, int col, int row, char attr_byte);

static int get_cursor_offset();
static void set_cursor_offset(int offset);
static int get_screen_offset(int col, int row);
static int get_offset_row(int offset);
static int get_offset_col(int offset);

void kprint(char *str)
{
  kprint_at(str, -1, -1);
}

void kprint_at(char *str, int col, int row)
{
  int offset;

  if (col >= 0 && row >= 0) {
    offset = get_screen_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(row);
    col = get_offset_col(col);
  }

  int i = 0;
  while (str[i] != '\0') {
    offset = print_char(str[i], col, row, WHITE_ON_BLACK);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
    i++;
  }
}

int print_char(char c, int col, int row, char attr_byte)
{
  /* Point to the beginning of video memory. */
  unsigned char *video_memory = (unsigned char*)VIDEO_MEM_ADDR;

  if (!attr_byte) {
    attr_byte = WHITE_ON_BLACK;
  }

  int offset;

  /* When a column and row are specified, print c there, else print to the
     current cursor position. */
  if (col >= 0 && row >= 0) {
    offset = get_screen_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }

  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_screen_offset(0, row + 1);
  } else {
    video_memory[offset] = c;
    video_memory[offset + 1] = attr_byte;
    offset += 2;
  }

  /*offset += 2;*/
  /* NEED THIS STATEMENT FOR SCROLLING offset = scroll(offset); */
  set_cursor_offset(offset);
  return offset;
}

int get_cursor_offset()
{
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}

void set_cursor_offset(int offset)
{
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{
  int row;
  int col;

  /* Prints blank characters at every position. */
  for (row = 0; row < MAX_ROWS; ++row) {
    for (col = 0; col < MAX_COLS; ++col) {
      print_char(' ', col, row, WHITE_ON_BLACK);
    }
  }

  /* Returns the cursor position to (0, 0). */
  set_cursor_offset(get_screen_offset(0, 0));
}

int get_screen_offset(int col, int row)
{
  return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset)
{
  return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS )) / 2;
}
