#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "spi.h"
#include "glcd.h"

uint8_t displayBuffer[SCRN_HEIGHT][SCRN_PAGES];



void glcd_init()
{
	_delay_ms(100);
	spi_init();
	glcd_sndCmd(CMD_BASIC);
	glcd_sndCmd(CMD_HOME);
	glcd_clearText();
	glcd_sndCmd(CMD_CURSOR_R);
	glcd_sndCmd(CMD_DISPLAY_ON);
}

static void glcd_sndCmd(uint8_t cmd)
{
	spi_setCS();
	spi_writeByte(SYNC_FRAME_CMD);
	spi_writeByte(cmd & 0xF0);
	spi_writeByte(cmd << 4);
	spi_resetCS();
}

static void glcd_sndData(uint8_t data)
{
	spi_setCS();
	spi_writeByte(SYNC_FRAME_DATA);
	spi_writeByte(data & 0xF0);
	spi_writeByte(data << 4);
	spi_resetCS();
}

void glcd_setGfxMode()
{
	glcd_sndCmd(CMD_EXTENDED);
	glcd_sndCmd(CMD_GFX);	
}

void glcd_setTextMode()
{
	glcd_sndCmd(CMD_BASIC);
}

void glcd_loadBuffer()
{
#if 1
	uint8_t x, y;
	glcd_setGfxMode();
	for(x = 0; x < SCRN_PAGES; x += 2)
	{
		for(y = 0; y < SCRN_HEIGHT; y++)
		{
			glcd_sndCmd(CMD_GDRAM_ADDR | ((y > 31) ? (y - 32) : (y)));
			glcd_sndCmd(CMD_GDRAM_ADDR | ((y > 31) ? ((x / 2) + 8) : (x / 2)));
			glcd_sndData(displayBuffer[y][x]);
			glcd_sndData(displayBuffer[y][x+1]);
		}
	}
#elif 0
	uint8_t x, y;
	for(x = 0; x < SCRN_PAGES; x += 2)
	{
		for(y = 0; y < SCRN_HEIGHT/2; y++)
		{
			glcd_sndCmd(CMD_GDRAM_ADDR | y);
			glcd_sndCmd(CMD_GDRAM_ADDR | x / 2);
			glcd_sndData(displayBuffer[y][x]);
			glcd_sndData(displayBuffer[y][x+1]);
		}
	}

	for(x = 0; x < SCRN_PAGES; x += 2)
	{
		for(y = SCRN_HEIGHT/2; y < SCRN_HEIGHT; y ++)
		{
			glcd_sndCmd(CMD_GDRAM_ADDR | (y - 32));
			glcd_sndCmd(CMD_GDRAM_ADDR | (8 + (x / 2)));
			glcd_sndData(displayBuffer[y][x]);
			glcd_sndData(displayBuffer[y][x+1]);
		}
	}
#endif
}

void glcd_fillScrn()
{ 
#if 0
        uint8_t x, y, yCoor = 0;
        glcd_setGfxMode();
        for(x = 0; x < SCRN_PAGES; x++)
        {
               for(y = 0, yCoor = 0; y < SCRN_HEIGHT; y++)
               {
                        glcd_sndCmd(CMD_GDRAM_ADDR | yCoor);
                        glcd_sndCmd(CMD_GDRAM_ADDR | x);
                        glcd_sndData(0xFF);
                        glcd_sndData(0xFF);
                        yCoor++;
                        if(yCoor > 31)
                                yCoor -= 32;
                }               
         }

#endif
	memset(&displayBuffer, 0xFF, sizeof(displayBuffer));
}

void glcd_clearScrn()
{
#if 0
        uint8_t x, y, yCoor = 0;
	glcd_setGfxMode();
        for(x = 0; x < SCRN_PAGES; x++)
        {
                for(y = 0, yCoor = 0; y < SCRN_HEIGHT; y++)
                {
                        glcd_sndCmd(CMD_GDRAM_ADDR | yCoor);
			glcd_sndCmd(CMD_GDRAM_ADDR | x);
			glcd_sndData(0x00);
			glcd_sndData(0x00);
			yCoor++;
			if(yCoor > 31)
				yCoor -= 32;
                }
        }
#endif
	memset(&displayBuffer, 0x00, sizeof(displayBuffer));
}

void glcd_drawPixel(uint8_t x, uint8_t y, PIXEL_STATE state)
{
#if 1
	if(x >= SCRN_WIDTH || y >= SCRN_HEIGHT)
	{
		return;
	}

	switch(state)
	{
		case ON:
			displayBuffer[y][x/8] |= (0x80 >> (x & 0x07));
			break;

		case OFF:
			displayBuffer[y][x/8] &= ~(0x80 >> (x & 0x07));
			break;

		case TOGGLE:
			displayBuffer[y][x/8] ^= (0x80 >> (x & 0x07));
			break;
	}
#endif
}

void glcd_drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, PIXEL_STATE state)
{
  int dx = abs(x1-x0);
  int dy = abs(y1-y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while(1) 
  {
  	glcd_drawPixel(x0, y0, state);

        if(x0==x1 && y0==y1)
	       	return;
  	int err2 = err+err;

  	if(err2>-dy) 
	{
	       	err-=dy;
	       	x0+=sx; 
	}

  	if(err2< dx) 
	{ 
		err+=dx; 
		y0+=sy; 
	}
  }
}

void glcd_printStr(uint8_t x, uint8_t y, char *str)
{
	uint8_t pos;
	glcd_setTextMode();
	switch(y)
	{
		case 0:
			pos = CMD_LINE_0 | x;
			break;

		case 1:
			pos = CMD_LINE_1 | x;
			break;

		case 2:
			pos = CMD_LINE_2 | x;
			break;

		case 3:
			pos = CMD_LINE_3 | x;
			break;

	}
	glcd_sndCmd(pos);
	while(*str != '\0')
	{
		glcd_sndData(*(str++));
	}
}

void glcd_clearText()
{
	glcd_sndCmd(CMD_CLEAR);
	_delay_ms(2);
}
