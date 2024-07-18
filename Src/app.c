#include "app.h"
#include "flashData.h"


static APP_ID appId = NONE;
static volatile KEY_ID keyId = NO_KEY;


static void strCpyToRam(char *ram, const char *const flash)
{
	memset(ram, 0, 20);
	char *strPtr = (char *) pgm_read_word(flash);
	strcpy_P(ram, strPtr);	
}

static inline void delay(unsigned int n)
{
	while(n--)
	{
		_delay_ms(1);
	}
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

			case PONG:
				pongGame();
				break;

			case GAMEOVER:
				gameOver();
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
	glcd_fillRectangle(GAMEBOX_RECT_X, GAMEBOX_RECT_Y, GAMEBOX_RECT_W, GAMEBOX_RECT_H, ON);
	glcd_loadBuffer();
	uint16_t counter = 0;
	while(keyId == NO_KEY)
	{
		if(counter >= 100)
			counter = 100;
		seg7_printDigit(counter++);
		
		for(uint16_t i = 0; i < sizeof(introTune3) / sizeof(uint16_t); i++)
		{
			uint16_t note = pgm_read_word(&introTune3[i]);
			speaker_playTone(note);
			delay(pgm_read_word(&introTune3Delay[i]) * 5);
			speaker_stop();
		}
	}
	speaker_stop();
	seg7_printDigit(0);
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

void pongGame()
{
	char ramBuffer[20];
	strCpyToRam(ramBuffer, (const char *const)&menuOptions[2]);
	glcd_printStr(PONG_X, PONG_Y, &ramBuffer[2]);
	strCpyToRam(ramBuffer, (const char *const)&gameIntro[0]);
	glcd_printStr(PONG_X, PONG_Y + 1, ramBuffer);
	glcd_fillCircle(GAME_INTRO_CIRCLE_X, GAME_INTRO_CIRCLE_Y, GAME_INTRO_CIRCLE_R, ON);
	glcd_loadBuffer();

	while(keyId == NO_KEY);

	keyId = NO_KEY;
	glcd_clearLine(1);
	glcd_clearLine(2);
	glcd_clearScrn();

	glcd_drawRectangle(PONG_RECT_X, PONG_RECT_Y, PONG_RECT_W, PONG_RECT_H, ON);
	glcd_drawRectangle(PONG_RECT_X + 1, PONG_RECT_Y + 1, PONG_RECT_W - 2, PONG_RECT_H - 2, ON);
	glcd_loadBuffer();

	int16_t barX = ((SCRN_WIDTH/2) - (PONG_BAR_W/2)), ballX = (SCRN_WIDTH/2), ballY = (SCRN_HEIGHT/2);
	uint16_t score = 0;
	int16_t ballVelX = 5;
	int16_t ballVelY = -ballVelX/2;

	while(appId == PONG)
	{
		if(keyId == LEFT)
		{
			keyId = NO_KEY;
			glcd_fillRectangle(barX, PONG_BAR_Y, PONG_BAR_W, PONG_BAR_H, OFF);
			barX -= 4;
			if(barX < 2)
				barX = 2;
		}

		else if(keyId == RIGHT)
		{
			keyId = NO_KEY;
			glcd_fillRectangle(barX, PONG_BAR_Y, PONG_BAR_W, PONG_BAR_H, OFF);
			barX += 4;
			if((barX + PONG_BAR_W) > (PONG_RECT_W - 2))
				barX = (PONG_RECT_W - 2) - (PONG_BAR_W);
		}

		if(ballX - PONG_BALL_R < 2)
		{
			glcd_fillCircle(ballX, ballY, PONG_BALL_R, OFF);
			ballVelX = -ballVelX;
		}

		else if((ballX + PONG_BALL_R) >= (PONG_RECT_W - 3))
		{
			glcd_fillCircle(ballX, ballY, PONG_BALL_R, OFF);
			ballVelX = -ballVelX;
		}

		else if(ballY - PONG_BALL_R < 2)
		{
			glcd_fillCircle(ballX, ballY, PONG_BALL_R, OFF);
			ballVelY = -ballVelY;
		}

		else if((ballY + PONG_BALL_R) > (PONG_RECT_H - 2)) 
		{	
			appId = GAMEOVER;
			break;
		}

		else if(((ballY + PONG_BALL_R) == PONG_BAR_Y))
		{
			if(ballX >= barX && ballX <= (barX + PONG_BAR_W/2))
			{
				ballVelY = -ballVelY;
				ballVelX = (int16_t)abs((int)ballVelX) * (-1);
				score++;
			}

			else if(ballX >= (barX + PONG_BAR_W/2) && ballX <= (barX + PONG_BAR_W))
			{
				ballVelY = -ballVelY;
				ballVelX = (int16_t)abs((int)ballVelX);
				score++;
			}
		}

		glcd_fillCircle(ballX, ballY, PONG_BALL_R, OFF);
		ballX = ballX + ballVelX;
		ballY = ballY + ballVelY;
		glcd_fillRectangle(barX, PONG_BAR_Y, PONG_BAR_W, PONG_BAR_H, ON);
		glcd_fillCircle(ballX, ballY, PONG_BALL_R, ON);
		glcd_drawRectangle(PONG_RECT_X, PONG_RECT_Y, PONG_RECT_W, PONG_RECT_H, ON);
		glcd_drawRectangle(PONG_RECT_X + 1, PONG_RECT_Y + 1, PONG_RECT_W - 2, PONG_RECT_H - 2, ON);
		glcd_loadBuffer();
		seg7_printDigit(score);
	}

	glcd_clearScrn();
	glcd_loadBuffer();
	keyId = NO_KEY;
}

void gameOver()
{
	char ramBuffer[20];

	strCpyToRam(ramBuffer, (const char *const)&gameIntro[0]);
	glcd_printStr(3, 1, ramBuffer);
	strCpyToRam(ramBuffer, (const char *const)&gameIntro[1]);
	glcd_printStr(3, 2, ramBuffer);
	glcd_drawRectangle(40, 15, 50, 32, ON);
	glcd_loadBuffer();

	while(keyId == NO_KEY)
	{
		speaker_playTone(SA_M);
		_delay_ms(50);
		speaker_playTone(PA_M);
		_delay_ms(50);
		speaker_playTone(RE_M);
		_delay_ms(50);
		speaker_playTone(MA_M);
		_delay_ms(50);
	}
	
	speaker_stop();
	glcd_clearLine(1);
	glcd_clearLine(2);
	glcd_clearScrn();
	glcd_loadBuffer();
	keyId = NO_KEY;
	seg7_printDigit(0);
	appId = MENU;
}
