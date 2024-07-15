#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "7seg.h"
#include "keypad.h"
#include "pwm.h"

int x = SCRN_WIDTH/2;
int y = SCRN_HEIGHT/2;

void keyCallBack(KEY_ID key, EDGE edge)
{
	glcd_drawCircle(x, y, 10, OFF);
	switch(key)
	{
		case UP:
			y--;
			seg7_printDigit(1);
			break;

		case DOWN:
			y++;
			seg7_printDigit(2);
			break;

		case SELECT:
			x = SCRN_WIDTH/2;
			y = SCRN_HEIGHT/2;
			seg7_printDigit(3);
			break;

		case LEFT:
			x--;
			seg7_printDigit(4);
			break;

		case RIGHT:
			x++;
			seg7_printDigit(5);
			break;
	}
	glcd_drawCircle(x, y, 10, ON);
}



int main()
{
	glcd_init();
	glcd_clearText();
	glcd_clearScrn();
	_delay_ms(1000);
	seg7_init();
	keypad_init(keyCallBack);
	seg7_printDigit(999);
	pwm_init();
	uint16_t notes[] = {262, 294, 330, 349, 392, 440, 494, 523, 523, 494, 440, 392, 349, 330, 294, 262};
	uint8_t note = 0;		
	pwm_setFrequency(0);
	while(1)
	{
		for(note = 0; note < sizeof(notes)/2; note++)
		{
			seg7_printDigit(notes[note]);
			pwm_setFrequency(notes[note]);
			_delay_ms(1000);
		}
		glcd_loadBuffer();
	}
}
