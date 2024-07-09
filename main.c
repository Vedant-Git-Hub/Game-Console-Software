#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "spi.h"


int main()
{

	glcd_init();
	glcd_clearText();
	glcd_fillScrn();
	glcd_loadBuffer();
	_delay_ms(1000);
	glcd_clearScrn();
	glcd_loadBuffer();
//	glcd_printStr(0,0,"Vedant B");
	while(1)
	{
//		glcd_printStr(0,0,"Vedant");
//		for(char i = 0; i < 128; i ++)
		{
//			for(char j = 0; j < 64; j++)
			{
				glcd_drawPixel(0, 0, ON);
				glcd_drawPixel(0, 63, ON);
				glcd_drawPixel(127, 0, ON);
				glcd_drawPixel(127, 63, ON);
				glcd_loadBuffer();
//				_delay_ms(200);
			}
		}

		_delay_ms(1000);
		glcd_clearScrn();
		glcd_loadBuffer();
		_delay_ms(1000);
	}
}
