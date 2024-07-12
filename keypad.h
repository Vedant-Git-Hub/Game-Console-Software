#ifndef H_KEYPAD_H
#define H_KEYPAD_H

#include <avr/io.h>


#define UP_KEY		PC0
#define DOWN_KEY	PC2
#define SELECT_KEY	PC3
#define LEFT_KEY	PC4
#define RIGHT_KEY	PC1

typedef enum{
	UP = 0,
	DOWN,
	SELECT,
	LEFT,
	RIGHT
}KEY_ID;

typedef enum{
	FALLING = 0,
	RISING
}EDGE;


void keypad_init();


#endif
