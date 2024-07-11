#ifndef H_GLCD_H
#define H_GLCD_H

#include <stdint.h>


#define SCRN_WIDTH	128
#define SCRN_HEIGHT	64
#define SCRN_PAGES	SCRN_WIDTH/8


#define SYNC_FRAME_CMD	0xF8
#define SYNC_FRAME_DATA	0xFA


#define CMD_BASIC		0x30
#define CMD_CLEAR		0x01
#define CMD_HOME		0x02
#define	CMD_CURSOR_R		0x06
#define CMD_DISPLAY_ON		0x0C
#define CMD_CURSOR_ON		0x0E
#define CMD_CURSOR_BLINK	0x0F
#define CMD_LINE_0		0x80
#define CMD_LINE_1		0x90
#define CMD_LINE_2		0x88
#define CMD_LINE_3		0x98

#define CMD_EXTENDED		0x34
#define CMD_SCROLL		0x03
#define CMD_GFX			0x36
#define CMD_GDRAM_ADDR		0x80

typedef enum {
	OFF = 0,
	ON,
	TOGGLE
}PIXEL_STATE;


void glcd_init(void);
static void glcd_sndCmd(uint8_t );
static void glcd_sndData(uint8_t );
void glcd_setGfxMode(void);
void glcd_setTextMode(void);
void glcd_loadBuffer(void);
void glcd_fillScrn(void);
void glcd_clearScrn(void);
void glcd_drawPixel(uint8_t, uint8_t, PIXEL_STATE );
void glcd_drawLine(uint8_t, uint8_t, uint8_t, uint8_t, PIXEL_STATE);
void glcd_drawCircle(uint8_t, uint8_t, uint8_t, PIXEL_STATE);

void glcd_printStr(uint8_t , uint8_t, char *);
void glcd_clearText(void);
#endif
