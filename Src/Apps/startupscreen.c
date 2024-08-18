#include "includes/startupscreen.h"
#include "../../includes/glcd.h"
#include "../../includes/keypad.h"
#include "../../includes/7seg.h"
#include "../../includes/speaker.h"
#include "../common.h"

bool keyWasPressed = false;

static const char startupLogo1[] PROGMEM = "GAME";
static const char startupLogo2[] PROGMEM = "BOX";

const uint16_t introTune[] PROGMEM = {
	SA_M, GA_K_M, PA_M, 0, PA_M, 0, PA_M,
	DHA_K_M, NI_K_M, DHA_K_M, MA_M, RE_M,
	GA_K_M, PA_M, GA_K_M, SA_M, DHA_K_L, NI_K_L, SA_M, 0, SA_M, 0, SA_M
};

const uint16_t introTuneDelay[] PROGMEM = {
	100, 75, 100, 1, 100, 1, 100,
	50, 50, 100, 100, 100,
	50, 75, 100, 100, 100, 100, 100, 1, 100, 1, 100
};


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
	uint8_t tempo = 2;
	uint16_t currDelay = 0;
	uint16_t noteDelay = 0;
	uint16_t currNote = 0;
	uint16_t noteCounter = 0;
	uint16_t segCounter = 0;
	uint16_t segCountDelay = 0;
	bool circleState = false;
	
	/*Initialize keyopad handler and clear display*/
	keypad_init(keyEvent);
	glcd_clearText();
	glcd_clearScrn();
	glcd_loadBuffer();
	/*Print Intro string and logo*/
	strCpyToRam(buff, &startupLogo1[0]);
	glcd_printStr(2, 1, buff);
	strCpyToRam(buff, &startupLogo2[0]);
	glcd_printStr(4, 2, buff);
	glcd_fillCircle(SCRN_WIDTH/2 - 4, SCRN_HEIGHT/2 - 1, 30, ON);
	glcd_loadBuffer();
	/*Play music until a key is pressed*/
	while(!keyWasPressed)
	{
		if(currDelay >= noteDelay)
		{
			/* Change note, note delay and reset currDelay*/
			currNote = pgm_read_word(&introTune[noteCounter]);
			noteDelay = pgm_read_word(&introTuneDelay[noteCounter]);
			noteDelay *= tempo;
			speaker_playTone(currNote);
			noteCounter++;
			if(noteCounter > sizeof(introTune) / sizeof(uint16_t))
			{
				noteCounter = 0;
				speaker_stop();
			}
			currDelay = 0;
		}
		
		if(segCountDelay > 100)
		{

			segCounter = segCounter > 999 ? 0 : segCounter + 1;
			seg7_printDigit(segCounter);
			segCountDelay = 0;
			circleState = !circleState;
			glcd_fillCircle(SCRN_WIDTH/2 - 4, SCRN_HEIGHT/2 - 1, 30, circleState);
			glcd_loadBuffer();
		}

		currDelay++;
		segCountDelay++;
		_delay_ms(1);
	}

	speaker_stop();
	glcd_clearLine(1);
	glcd_clearLine(2);
	glcd_clearScrn();
	glcd_loadBuffer();
	seg7_printDigit(0);
}
