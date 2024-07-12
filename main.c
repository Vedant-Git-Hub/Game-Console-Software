#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "7seg.h"
#include "keypad.h"


void keyCallBack(KEY_ID key, EDGE edge)
{
	static uint8_t count = 0;
	switch(key)
	{
		case UP:
			seg7_printDigit(++count);
			break;

		case DOWN:
			seg7_printDigit(--count);
			break;

		case SELECT:
			count = 0;
			seg7_printDigit(count);
			break;

		case LEFT:
			seg7_printDigit(--count);
			break;

		case RIGHT:
			seg7_printDigit(count++);
			break;
	}
}



int main()
{
	seg7_init();
	keypad_init(keyCallBack);
	seg7_printDigit(999);
	while(1)
	{

	}
}
