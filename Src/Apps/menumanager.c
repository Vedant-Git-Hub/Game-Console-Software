#include "includes/menumanager.h"
#include "../common.h"
#include "../../includes/glcd.h"
#include "../../includes/keypad.h"
#include "../../includes/7seg.h"

static KEY_ID keyPressed = NO_KEY;

const char menu[] PROGMEM = "MENU";


static void keypadEvent(KEY_ID keyId, EDGE edge)
{	
	switch(keyId)
	{
		case UP:
			keyPressed = UP;
			break;

		case DOWN:
			keyPressed = DOWN;
			break;

		case SELECT:
			keyPressed = SELECT;	
			break;

		case LEFT:
			keyPressed = LEFT;
			break;

		case RIGHT:
			keyPressed = RIGHT;
			break;
	}
}

uint8_t menuManager(uint16_t *menuTable, uint8_t listLength)
{
	char ramBuff[20];
	int8_t currPageNumber = 0;
	uint8_t currPageSize = 0;
	uint8_t totalPages = listLength % MENU_PAGE_SIZE == 0 ? listLength / MENU_PAGE_SIZE : (listLength / MENU_PAGE_SIZE) + 1;
	int8_t currElement = 0;
	int8_t menuBarPosY = 1;
	/*Initialize keypad handler, print "MENU" string*/
	glcd_clearScrn();
	glcd_loadBuffer();
	keypad_init(keypadEvent);
	strCpyToRam(ramBuff, &menu[0]);
	glcd_printStr(3, 0, ramBuff);
	keyPressed = NO_KEY;
	/*Display menu and take user selection*/
	while(1)
	{

		currPageSize = (currPageNumber == (totalPages - 1)) ? listLength % MENU_PAGE_SIZE : MENU_PAGE_SIZE;
		glcd_clearLine(1);
		glcd_clearLine(2);
		glcd_clearLine(3);

		for(currElement = 0; currElement < currPageSize; currElement++)
		{
			strCpyToRam(ramBuff, (char *)pgm_read_word(&menuTable[currElement + (currPageNumber * MENU_PAGE_SIZE)]));
			glcd_printStr(0, currElement + 1, ramBuff);
		}
	
		if(keyPressed == UP)
		{
			glcd_fillRectangle(MENUBAR_X, MENUBAR_Y * menuBarPosY, MENUBAR_W, MENUBAR_H, OFF);
			menuBarPosY--;

			if(menuBarPosY < 1 && (currPageNumber == 0))
			{
				menuBarPosY = 1;
			}
			else if(menuBarPosY < 1 && (currPageNumber > 0))
			{
				menuBarPosY = 3;
				currPageNumber--;
			}
			keyPressed = NO_KEY;
		}
		else if(keyPressed == DOWN)
		{
			glcd_fillRectangle(MENUBAR_X, MENUBAR_Y * menuBarPosY, MENUBAR_W, MENUBAR_H, OFF);
			menuBarPosY++;
		
			if(menuBarPosY > currPageSize && (currPageNumber == totalPages - 1))
			{
				menuBarPosY = currPageSize;
			}
			else if(menuBarPosY > currPageSize && (currPageNumber < totalPages - 1))
			{
				menuBarPosY = 1;
				currPageNumber++;
			}

			keyPressed = NO_KEY;
		}
		else if(keyPressed == SELECT)
		{
			return (menuBarPosY + (MENU_PAGE_SIZE * currPageNumber)) - 1;
			keyPressed = NO_KEY;
		}
		else
		{
			/*Do nothing*/
			keyPressed = NO_KEY;
		}

		glcd_fillRectangle(MENUBAR_X, MENUBAR_Y * menuBarPosY, MENUBAR_W, MENUBAR_H, ON);
		glcd_loadBuffer();
	}

	return 0;
}
