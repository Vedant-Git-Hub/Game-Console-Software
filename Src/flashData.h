#ifndef H_FLASH_DATA_H
#define H_FLASH_DATA_H

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

const char const gameStr[] PROGMEM = "GAME";
const char const overStr[] PROGMEM = "OVER";
 
const char *const gameIntro[] PROGMEM = {
        gameStr,
        overStr
 };

const uint16_t introTune1[] PROGMEM = {
	GA_M, NI_L, SA_M, RE_M, SA_M,  NI_L, DHA_L,
	DHA_L, SA_M, GA_M, RE_M, SA_M, NI_L,
	SA_M, RE_M, GA_M, SA_M, DHA_M, DHA_M,
	RE_M, MA_M, DHA_M, PA_M, MA_M, GA_M,
	SA_M, GA_M, RE_M, SA_M, NI_L,
	NI_L, SA_M, RE_M, GA_M, SA_M, DHA_L, DHA_L,

	GA_M, SA_M, RE_M, NI_L, SA_M, DHA_L, DHA_K_L, NI_L,
	GA_M, SA_M, RE_M, NI_L, SA_M, GA_M, DHA_M, DHA_K_M
};

const uint16_t introTune1Delay[] PROGMEM = {
	100, 50, 50, 100, 50, 50, 100,
	100, 50, 100, 100, 50, 50,
        25, 25, 25, 100, 100, 100,
	100, 50, 50, 100, 50, 100,
	100, 50, 50, 50, 100,
	100, 50, 50, 100, 100, 100, 100,

	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 100, 100, 200, 200	
};

const uint16_t introTune2[] PROGMEM = {
	DHA_L, SA_M, GA_M, 0, GA_M, 0, GA_M,
	MA_T_M, PA_M, MA_T_M, RE_M, NI_L,
	SA_M, GA_M, SA_M, DHA_L, 0, DHA_K_L, 0, DHA_K_L, 0, DHA_K_L, 0
};

const uint16_t introTune2Delay[] PROGMEM = {
	50, 75, 100, 1, 100, 1, 100,
	50, 75, 75, 100, 100,
	50, 75, 100, 100, 0, 100, 1, 100, 1, 100, 1 
};


const uint16_t introTune3[] PROGMEM = {
	GA_M, 0, GA_M, 0, GA_M, 0, GA_M, NI_M,
	MA_T_M, PA_M, MA_T_M, GA_M, RE_M, MA_T_M,
	GA_M, MA_T_M, GA_M, RE_M, GA_M, MA_T_M, PA_M, MA_T_M, GA_M, RE_M, NI_L,
	GA_H, NI_M, RE_H, NI_M, 0, NI_M, DHA_M, PA_M, GA_M,

	PA_M, DHA_M, NI_M, SA_H, DHA_M, PA_M, MA_T_M,
	GA_M, 0, GA_M, 0, GA_M, 0, GA_M, NI_M,
	MA_T_M, PA_M, MA_T_M, GA_M, RE_M, MA_T_M,
	GA_M, MA_T_M, GA_M, RE_M, GA_M, MA_T_M, PA_M, MA_T_M, GA_M, RE_M, NI_L
};

const uint16_t introTune3Delay[] PROGMEM = {
	100, 1, 50, 1, 100, 1, 100, 100,
	50, 50, 50, 50, 50, 100,
	100, 100, 100, 100, 100, 100, 150, 100, 100, 100, 100,
	100, 100, 100, 100, 1, 100, 100, 100, 100,

	100, 100, 100, 100, 150, 50, 50,
	100, 1, 50, 1, 100, 1, 100, 100,
	100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 150, 100, 100, 100, 100
};


#endif
