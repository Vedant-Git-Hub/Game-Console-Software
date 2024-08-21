#include "includes/menumanager.h"
#include "../common.h"
#include "../../includes/glcd.h"
#include "../../includes/keypad.h"

static KEY_ID keyPressed;

const char menu[] PROGMEM = "MENU";


static void keypadEvent(KEY_ID keyId, EDGE edge)
{
	switch(keyId)
	{
		case UP_KEY:
			keyPressed = UP_KEY;
			break;

		case DOWN_KEY:
			keyPressed = DOWN_KEY;
			break;

		case SELECT_KEY:
			keyPressed = SELECT_KEY;	
			break;

		case LEFT_KEY:
			keyPressed = LEFT_KEY;
			break;

		case RIGHT_KEY:
			keyPressed = RIGHT_KEY;
			break;
	}
}

uint8_t menuManager(uint16_t *menuTable, uint8_t listLength)
{
	char ramBuff[20];
	int8_t currPageNumber = 0;
	uint8_t currPageSize = 3;
	int8_t elementsPerPage = 0;
	int8_t currElement = 0;
	/*Initialize keypad handler, print "MENU" string*/
	keypad_init(keypadEvent);
	strCpyToRam(ramBuff, &menu[0]);
	glcd_printStr(3, 0, ramBuff);
	/*Display menu and take user selection*/
//	strCpyToRam(ramBuff, (char *)pgm_read_word(&menuTable[0]));
//	glcd_printStr(0, 1, ramBuff);
//	strCpyToRam(ramBuff, (const char*)pgm_read_word(&menuTable[1]));
//	glcd_printStr(0, 1, ramBuff);
//	strCpyToRam(ramBuff, (char *)pgm_read_word(&menuTable[2]));
//	glcd_printStr(0, 3, ramBuff);
	while(1)
	{
		for(currElement = 0; currElement < currPageSize; currElement++)
		{
			strCpyToRam(ramBuff, (char *)pgm_read_word(&menuTable[currElement]));
			glcd_printStr(0, currElement + 1, ramBuff);
		}
	}

	return 0;
}
