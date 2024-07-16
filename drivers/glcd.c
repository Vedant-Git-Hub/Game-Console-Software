#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "../includes/spi.h"
#include "../includes/glcd.h"

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

        if(x0 == x1 && y0 == y1)
	       	return;
  	int err2 = err + err;

  	if(err2 > -dy) 
	{
	       	err -= dy;
	       	x0 += sx; 
	}

  	if(err2 < dx) 
	{ 
		err += dx; 
		y0 += sy; 
	}
  }
}

void glcd_drawFastLineV(uint8_t x, uint8_t y0, uint8_t y1, PIXEL_STATE state)
{

	uint8_t mask = 0x80 >> (x&7);

 	if(y1<y0) 
	{
    		mask=y0; y0=y1; y1=mask; // swap
 	}

 	mask = 0x80 >> (x&7);

  	switch(state)
       	{
   		case ON: 
			for(int y=y0; y<=y1; y++) 
				displayBuffer[y][x/8] |= mask;   
			break;

   		case OFF: 
			for(int y=y0; y<=y1; y++) 
				displayBuffer[y][x/8] &= ~mask;  
			break;

   		case TOGGLE: 
			for(int y=y0; y<=y1; y++) 
				displayBuffer[y][x/8] ^= mask;   
			break;
 	}
}

void glcd_drawFastLineH(uint8_t x0, uint8_t x1, uint8_t y, PIXEL_STATE state)
{
	uint8_t xstab[8]={0xff,0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01};
	uint8_t xetab[8]={0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};
	uint8_t pattern[4]={0xaa,0x55,0xaa,0x55};
 	int x8s, x8e;

  	if(x1 >= x0) 
	{
    		x8s = x0 / 8;
    		x8e = x1 / 8;
  	} 
	else 
	{
    		x8s = x1; 
		x1 = x0; 
		x0 = x8s; // swap
    		x8s = x1 / 8;
    		x8e = x0 / 8;
  	}

  	switch(state) 
	{
    		case ON:
      			if(x8s == x8e) 
				displayBuffer[y][x8s] |= (xstab[x0 & 7] & xetab[x1 & 7]);
      			else 
			{ 
				displayBuffer[y][x8s] |= xstab[x0 & 7]; 
				displayBuffer[y][x8e] |= xetab[x1 & 7]; 
			}
      			for(int x = x8s + 1; x < x8e; x++) 
				displayBuffer[y][x] = 0xff;
      			break;

    		case OFF:
      			if(x8s == x8e) 
				displayBuffer[y][x8s] &= ~(xstab[x0 & 7] & xetab[x1 & 7]);
      			else 
			{ 
				displayBuffer[y][x8s] &= ~xstab[x0 & 7]; 
				displayBuffer[y][x8e] &= ~xetab[x1 & 7]; 
			}

      			for(int x = x8s + 1; x < x8e; x++) 
				displayBuffer[y][x] = 0x00;
     			 break;

    		case TOGGLE:
      			if(x8s == x8e) 
				displayBuffer[y][x8s] ^= (xstab[x0 & 7] & xetab[x1 & 7]);
      			else 
			{ 
				displayBuffer[y][x8s] ^= xstab[x0 & 7]; 
				displayBuffer[y][x8e] ^= xetab[x1 & 7]; 
			}

      			for(int x = x8s + 1; x < x8e; x++) 
				displayBuffer[y][x] ^= 0xff;
      			break;
 	 }
}

void glcd_drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, PIXEL_STATE state)
{
	if(x >= SCRN_WIDTH || y >= SCRN_HEIGHT) 
		return;

  	uint8_t drawVright = 1;

  	if(x+w > SCRN_WIDTH) 
	{ 
		w = SCRN_WIDTH - x; 
		drawVright = 0; 
	}

  	if(y + h > SCRN_HEIGHT) 
		h = SCRN_HEIGHT - y; 
	else 
		glcd_drawFastLineH(x, x + w - 1, y + h - 1, state);
 	 	glcd_drawFastLineH(x, x + w - 1, y, state);
  		glcd_drawFastLineV(x, y + 1, y + h - 2, state);

  	if(drawVright) 
		glcd_drawFastLineV(x + w - 1, y + 1, y + h - 2, state);
}

void glcd_fillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, PIXEL_STATE state)
{
	if(x >=SCRN_WIDTH || y >= SCRN_HEIGHT) 
		return;

  	if(x + w > SCRN_WIDTH) 
		w = SCRN_WIDTH - x;

  	if(y + h > SCRN_HEIGHT) 
		h = SCRN_HEIGHT - y;

  	for(int i = y; i < y + h; i++) 
		glcd_drawFastLineH(x, x + w - 1, i, state);
}

void glcd_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, PIXEL_STATE state)
{
	int f = 1 - (int)radius;
	int ddF_x = 1;
	int ddF_y = -2 * (int)radius;
	int x = 0;
	int y = radius;
 
	glcd_drawPixel(x0, y0 + radius, state);
	glcd_drawPixel(x0, y0 - radius, state);
	glcd_drawPixel(x0 + radius, y0, state);
  	glcd_drawPixel(x0 - radius, y0, state);
 
 	 while(x < y) 
 	 {


		 if(f >= 0) 
	 	 {
     			y--; 
		 	ddF_y += 2; f += ddF_y;
	  	 }

    	         x++;
	 	 ddF_x += 2; 
	 	 f += ddF_x;    
   		 glcd_drawPixel(x0 + x, y0 + y, state);
   		 glcd_drawPixel(x0 - x, y0 + y, state);
   		 glcd_drawPixel(x0 + x, y0 - y, state);
   		 glcd_drawPixel(x0 - x, y0 - y, state);
   		 glcd_drawPixel(x0 + y, y0 + x, state);
   		 glcd_drawPixel(x0 - y, y0 + x, state);
   		 glcd_drawPixel(x0 + y, y0 - x, state);
   		 glcd_drawPixel(x0 - y, y0 - x, state);
 	 }
}

void glcd_fillCircle(uint8_t x0, uint8_t y0, uint8_t r, PIXEL_STATE state)
{
#if 1
	glcd_drawFastLineH(x0 - r, x0 - r + 2 * r + 1, y0, state);

  	int16_t f = 1 - r;
  	int16_t ddF_x = 1;
  	int16_t ddF_y = -2 * r;
  	int16_t x = 0;
  	int16_t y = r;

  	while(x < y) 
	{
    		if (f >= 0) 
		{
      			y--;
      			ddF_y += 2;
      			f += ddF_y;
    		}

    		x++;
   		ddF_x += 2;
    		f += ddF_x;

    		glcd_drawFastLineH(x0 - x, x0 - x + 2 * x + 1, y0 + y, state);
    		glcd_drawFastLineH(x0 - y, x0 - y + 2 * y + 1, y0 + x, state);
    		glcd_drawFastLineH(x0 - x, x0 - x + 2 * x + 1, y0 - y, state);
    		glcd_drawFastLineH(x0 - y, x0 - y + 2 * y + 1, y0 - x, state);
 	 }
#elif 0
	for(int i = r; i >= 0; i--)
		glcd_drawCircle(x0, y0, i, state);
#endif
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

void glcd_clearLine(uint8_t lineNo)
{
	char spaces[] = "                ";
	glcd_setTextMode();
	glcd_printStr(0, lineNo, spaces);
}

void glcd_clearText()
{
	glcd_sndCmd(CMD_CLEAR);
	_delay_ms(10);
}
