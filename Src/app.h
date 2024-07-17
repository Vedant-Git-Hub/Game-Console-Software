#ifndef H_APP_H
#define H_APP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../includes/glcd.h"
#include "../includes/7seg.h"
#include "../includes/keypad.h"
#include "../includes/speaker.h"

#define GAME_INTRO_CIRCLE_X	SCRN_WIDTH/2
#define GAME_INTRO_CIRCLE_Y	SCRN_HEIGHT/2
#define GAME_INTRO_CIRCLE_R	20

#define GAMEBOX_X		2
#define GAMEBOX_Y		1
#define GAMEBOX_RECT_X		30
#define GAMEBOX_RECT_Y		13
#define GAMEBOX_RECT_W		70
#define GAMEBOX_RECT_H		20

#define MENU_PAGE_SIZE		3
#define MENUBAR_X		0
#define MENUBAR_Y		16
#define MENUBAR_W		128
#define MENUBAR_H		15

#define PONG_X			3
#define PONG_Y			1
#define PONG_RECT_X		0
#define PONG_RECT_Y		0
#define PONG_RECT_W		128
#define PONG_RECT_H		64
#define PONG_BAR_Y		52
#define PONG_BAR_W		20
#define PONG_BAR_H		4
#define PONG_BALL_R		2


typedef enum{
	NONE = 0,
	STARTUP,
	MENU,
	SNAKE,
	PONG,
	TETRIS,
	PIANO,
	SETTINGS,
	SPARE1,
	SPARE2,
	SPARE3,
	MAXID
}APP_ID;

#define GAME_START_INDEX	SNAKE

void initialize_drivers(void);
void app_run(void);

void keypadHandler(KEY_ID, EDGE);

void startupScreen(void);
void menuScreen(void);
void pongGame(void);

#endif
