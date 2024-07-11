#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "spi.h"


int main()
{

	glcd_init();
	glcd_clearText();
	glcd_clearScrn();
	glcd_loadBuffer();
	_delay_ms(1000);
	while(1)
	{/*
		glcd_drawLine(0, 0, 128/2, 64/2, ON);
		glcd_loadBuffer();
		_delay_ms(200);
		glcd_clearScrn();
		glcd_drawLine(127, 0, 128/2, 64/2, ON);
		glcd_loadBuffer();
		_delay_ms(200);
		glcd_clearScrn();
		glcd_drawLine(127, 63, 128/2, 64/2, ON);
		glcd_loadBuffer();
		_delay_ms(200);
		glcd_clearScrn();
		glcd_drawLine(0, 63, 128/2, 64/2, ON);
		glcd_loadBuffer();
		_delay_ms(200);
		glcd_clearScrn();
		*/
		glcd_printStr(0, 2, "VB");
		for(int i = 0; i < 128; i+=4)
		{
			for(int j = 0; j < 64; j++)
			{
				if(i == j)
				{
					glcd_drawCircle(i, j, 31, ON);
					glcd_loadBuffer();
					glcd_clearScrn();
				}
			}
		}
	}
}
