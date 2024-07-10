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
	{
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
	}
}
