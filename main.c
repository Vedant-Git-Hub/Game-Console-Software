#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "7seg.h"


int main()
{
	glcd_init();
	glcd_clearText();
	glcd_clearScrn();
	glcd_loadBuffer();
	seg7_init();
	for(int i = 0; i < 1000; i ++)
	{
		seg7_printDigit(i);
		_delay_ms(50);
	}
	glcd_clearText();
	_delay_ms(1000);
	while(1)
	{
//		glcd_printStr(0, 2, "VB");
		glcd_drawRectangle(0, 0, 40, 20, TOGGLE);
		glcd_fillRectangle(0, 30, 40, 20, TOGGLE);
		glcd_drawCircle(128/2, 64/2, 10, TOGGLE);
		glcd_fillCircle(110, 36, 10, TOGGLE);
		glcd_loadBuffer();
		_delay_ms(300);
		glcd_clearText();
	}
}
