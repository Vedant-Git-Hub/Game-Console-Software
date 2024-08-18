#ifndef H_APP_H
#define H_APP_H


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "common.h"
#include "../includes/glcd.h"
#include "../includes/7seg.h"
#include "../includes/keypad.h"
#include "../includes/speaker.h"
#include "Apps/includes/startupscreen.h"


typedef enum{
	GAMEOVER = 0xFF,
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


void initialize_drivers(void);
void app_run(void);

#endif
