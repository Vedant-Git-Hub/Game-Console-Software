#include "app.h"
#include "flashData.h"


const char menuElement1[] PROGMEM = "1.Snake";
const char menuElement2[] PROGMEM = "2.Pong";
const char menuElement3[] PROGMEM = "3.Tetris";
const char menuElement4[] PROGMEM = "4.XO";
const char menuElement5[] PROGMEM = "5.Chess";

static const char *const menuTable[] PROGMEM = {
	(const char *const)menuElement1,
	(const char *const)menuElement2,
	(const char *const)menuElement3,
	(const char *const)menuElement4,
	(const char *const)menuElement5,
};

static void dummygame1();
static void dummygame2();
static void dummygame3();
static void dummygame4();

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
	void (*gameEntryPoint[4])(void) = {dummygame1, dummygame2, dummygame3, dummygame4};

	/*Display startup screen, this will be executed only once.*/
	startupScreen();
	/*Start menumanager and run the game according to user selection*/
	while(1)
	{
		gameId = menuManager((uint16_t *)menuTable, 5);

		gameEntryPoint[gameId]();
	}

	/*Should not come here ever*/
}


static void dummygame1()
{
	glcd_clearScrn();
	glcd_fillRectangle(0,10,30,30, ON);
	glcd_loadBuffer();
	_delay_ms(2000);
}
static void dummygame2()
{
	glcd_clearScrn();
	glcd_fillRectangle(0,20,30,30, ON);
	glcd_loadBuffer();
	_delay_ms(2000);
}
static void dummygame3()
{
	glcd_clearScrn();
	glcd_fillRectangle(0,30,30,30, ON);
	glcd_loadBuffer();
	_delay_ms(2000);
}
static void dummygame4()
{
	glcd_clearScrn();
	glcd_fillRectangle(40,0,30,30, ON);
	glcd_loadBuffer();
	_delay_ms(2000);
}
