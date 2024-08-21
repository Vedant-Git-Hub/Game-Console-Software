#include "app.h"
#include "flashData.h"


const char menuElement1[] PROGMEM = "1.Snake";
const char menuElement2[] PROGMEM = "2.Pong";
const char menuElement3[] PROGMEM = "3.Tetris";

static const char *const menuTable[] PROGMEM = {
	(const char *const)menuElement1,
	(const char *const)menuElement2,
	(const char *const)menuElement3
};



void initialize_drivers()
{
	glcd_init();
	glcd_clearText();
	_delay_ms(500);
	glcd_clearScrn();
	glcd_loadBuffer();
	seg7_init();
	speaker_init();
	for(uint8_t i = 0; i < 4; i++)
		glcd_clearLine(i);
}


void app_run()
{
        uint8_t gameId = 0;
	void (*gameEntryPoint[4])(void) = {NULL, NULL, NULL, NULL};

	/*Display startup screen, this will be executed only once.*/
	startupScreen();
	/*Start menumanager and run the game according to user selection*/
	while(1)
	{
		gameId = menuManager((uint16_t *)menuTable, 3);

		gameEntryPoint[gameId]();
	}

	/*Should not come here ever*/
}
