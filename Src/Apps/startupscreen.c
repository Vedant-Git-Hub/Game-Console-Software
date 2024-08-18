#include "includes/startupscreen.h"
#include "../../includes/glcd.h"
#include "../../includes/keypad.h"
#include "../../includes/7seg.h"
#include "../common.h"

bool keyWasPressed = false;

static const char const startupLogo[] PROGMEM = "GAME BOX";

static void keyEvent(KEY_ID keyId, EDGE edge)
{
	switch(keyId)
	{
		case UP_KEY:
		case DOWN_KEY:
		case SELECT_KEY:
		case LEFT_KEY:
		case RIGHT_KEY:
			keyWasPressed = true;
			break;
	}
}		


void startupScreen()
{
	char buff[20];
	
	/*Initialize keyopad handler and clear display*/
	keypad_init(keyEvent);
	glcd_clearText();
	glcd_clearScrn();
	glcd_loadBuffer();
	/*Print Intro string and logo*/
	glcd_printStr(0, 0, "Test");
	strCpyToRam(buff, &startupLogo);
	glcd_printStr(2, 1, buff);

	while(!keyWasPressed)
	{
	
	}
}
