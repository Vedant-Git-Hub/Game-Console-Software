#include "app.h"


static APP_ID appId = NONE;
static volatile KEY_ID keyId = NO_KEY;

const char const gameboxStr[] PROGMEM = "GAME BOX";
const char const spacesStr[] PROGMEM  = "        ";

const char *const startupStr[] PROGMEM = {
	gameboxStr,
	spacesStr
};

const char const menuStr[] PROGMEM     = "MENU";
const char const snakeStr[] PROGMEM    = "1.SNAKE";
const char const pongStr[] PROGMEM     = "2.PONG";
const char const tetrisStr[] PROGMEM   = "3.TETRIS";
const char const pianoStr[] PROGMEM    = "4.PIANO";
const char const settingsStr[] PROGMEM = "5.SETTINGS";
const char const spare1Str[] PROGMEM   = "6.SPARE 1";
const char const spare2Str[] PROGMEM   = "7.SPARE 2";
const char const spare3Str[] PROGMEM   = "8.SPARE 3";

const char *const menuOptions[] PROGMEM = {
	menuStr,
	snakeStr,
	pongStr,
	tetrisStr,
	pianoStr,
	settingsStr,
	spare1Str,
	spare2Str,
	spare3Str,
};

static void strCpyToRam(char *ram, const char *const flash)
{
	memset(ram, 0, 20);
	char *strPtr = (char *) pgm_read_word(flash);
	strcpy_P(ram, strPtr);	
}


void initialize_drivers()
{
	glcd_init();
	glcd_clearText();
	_delay_ms(500);
	glcd_clearScrn();
	glcd_loadBuffer();
	seg7_init();
	seg7_printDigit(555);
	keypad_init(keypadHandler);
	speaker_init();
	appId = STARTUP;
	for(uint8_t i = 0; i < 4; i++)
		glcd_clearLine(i);
}


void app_run()
{
	while(1)
	{
		switch(appId)
		{
			case NONE:
				appId = STARTUP;
				break;

			case STARTUP:
				startupScreen();
				break;
				
			case MENU:
				menuScreen();
				break;
		}
	}
}


void keypadHandler(KEY_ID key, EDGE edge)
{
	keyId = key;
	switch(key)
	{
		case UP:
			break;

		case DOWN:
			break;

		case SELECT:
			break;

		case RIGHT:
			break;

		case LEFT:
			break;
	}

}

void startupScreen()
{
	char ramBuffer[20];
	strCpyToRam(ramBuffer, (const char *const)&startupStr[0]);
	glcd_printStr(GAMEBOX_X, GAMEBOX_Y, ramBuffer);
	while(keyId == NO_KEY)
	{
		glcd_fillRectangle(GAMEBOX_RECT_X, GAMEBOX_RECT_Y, GAMEBOX_RECT_W, GAMEBOX_RECT_H, ON);
		glcd_loadBuffer();
		_delay_ms(200);
	}
	strCpyToRam(ramBuffer, (const char *const)&startupStr[1]);
	glcd_printStr(GAMEBOX_X, GAMEBOX_Y, ramBuffer);
	glcd_clearScrn();
	glcd_loadBuffer();
	keyId = NO_KEY;
	appId = MENU;
}

void menuScreen()
{
	glcd_clearText();
	_delay_ms(10);
	glcd_clearScrn();
	glcd_loadBuffer();
	
	char ramBuffer[20];

	strCpyToRam(ramBuffer,(const char *const) &menuOptions[0]);
	glcd_printStr(3, 0, ramBuffer);

	volatile int8_t currentPage = 0;
	int8_t menubarY = MENUBAR_Y;
        uint8_t totalPages = (MAXID - 3) / MENU_PAGE_SIZE;
	totalPages = (totalPages % MENU_PAGE_SIZE) == 0 ? totalPages : totalPages + 1;
	uint8_t currentPageSize = 0;	
	uint8_t options;
	keyId = NO_KEY;
		
	while(appId == MENU)
	{
		currentPageSize = (currentPage == (totalPages - 1)) ? (MAXID - 3) % MENU_PAGE_SIZE : MENU_PAGE_SIZE;

		glcd_fillRectangle(MENUBAR_X, menubarY, MENUBAR_W, MENUBAR_H, ON);

		for(options = 1; options <= currentPageSize; options++)
		{
			strCpyToRam(ramBuffer, (const char *const)&menuOptions[options + (currentPage * MENU_PAGE_SIZE)]);
			glcd_printStr(MENUBAR_X, options, ramBuffer);
		}

		switch(keyId)
		{
			case UP:
				glcd_fillRectangle(MENUBAR_X, menubarY, MENUBAR_W, MENUBAR_H, OFF);
				keyId = NO_KEY;
				menubarY -= MENUBAR_Y;
				if(menubarY < MENUBAR_Y)
				{
					if(currentPage == 0)
					{
						menubarY = MENUBAR_Y;
					}
					else if (currentPage > 0)
					{
						menubarY = MENUBAR_Y * MENU_PAGE_SIZE;
						currentPage--;
						glcd_clearLine(1);
						glcd_clearLine(2);
						glcd_clearLine(3);
					}
					else
					{
						/*Should not come here ever*/
					}
				}
				break;

			case DOWN:
				glcd_fillRectangle(MENUBAR_X, menubarY, MENUBAR_W, MENUBAR_H, OFF);
				keyId = NO_KEY;
				menubarY += MENUBAR_Y;
				if(menubarY > MENUBAR_Y * currentPageSize)
				{
					if(currentPage == (totalPages - 1))
					{
						menubarY = MENUBAR_Y * currentPageSize;
					}
					else if(currentPage < (totalPages - 1) && currentPage >= 0)
					{
						menubarY = MENUBAR_Y;
						currentPage++;
						glcd_clearLine(1);
						glcd_clearLine(2);
						glcd_clearLine(3);
					}
					else
					{
						/*should not come here ever*/
					}
				}
				break;

			case SELECT:
				appId = (menubarY / MENUBAR_Y) + (currentPage * currentPageSize);
				appId = appId - 1;
				appId = GAME_START_INDEX + appId;
				glcd_fillRectangle(MENUBAR_X, menubarY, MENUBAR_W, MENUBAR_H, OFF);
				keyId = NO_KEY;
				break;
		}

		glcd_loadBuffer();
	}	

	glcd_clearLine(0);
	glcd_clearLine(1);
	glcd_clearLine(2);
	glcd_clearLine(3);
	glcd_clearScrn();
	keyId = NO_KEY;
	glcd_loadBuffer();
}
