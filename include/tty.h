/*
 * tty.h
 *
 * Teletype display and setup.
 */

#ifndef BERCEUSE_TTY_H_
#define BERCEUSE_TTY_H_

#define VIDEO_MEM_ADDR 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define BLACK_ON_WHITE 0xf0

/*
 * Convenience macros that can be |'d together to change text and background
 * color.
 */
#define BLACK_TEXT          0x0
#define BLUE_TEXT           0x1
#define GREEN_TEXT          0x2
#define CYAN_TEXT           0x3
#define RED_TEXT            0x4
#define MEGENTA_TEXT        0x5
/*
 * TODO: Fill in these macros.
 */
#define LIGHT_MAGENTA_TEXT  0xd
#define YELLOW_TEXT         0xe
#define WHITE_TEXT          0xf

#define BLACK_BACKGROUND          0x00
#define BLUE_BACKGROUND           0x10
/*
 * TODO: Fill in these macros.
 */
#define LIGHT_MAGENTA_BACKGROUND  0xd0
#define YELLOW_BACKGROUND         0xe0
#define WHITE_BACKGROUND          0xf0

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void kprint(char *str);

void clear_screen();

#endif /* BERCEUSE_TTY_H_ */
