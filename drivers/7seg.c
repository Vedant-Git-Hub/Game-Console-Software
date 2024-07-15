#include <stdint.h> 
#include <avr/pgmspace.h>
#include "../includes/7seg.h"
#include "../includes/srdriver.h"


const uint8_t digiArray[] PROGMEM = {
	0x3F, //0
	0x06, //1
	0x5B, //2
	0x4F, //3
	0x66, //4
	0x6D, //5
	0x7D, //6
	0x07, //7
	0x7F, //8
	0x6F  //9
};


void seg7_init()
{
	sr_init();
	/*Add some animation on display*/
}

void seg7_printDigit(uint16_t num)
{
	if(num > 999)
		return;

	uint8_t digits[3] = {0x00, 0x00, 0x00};
	uint8_t count = 2;
	do
	{
		digits[count] = num % 10;
		digits[count] = pgm_read_byte(&digiArray[digits[count]]);
		num = num / 10;
		count--;
	}while(num);	
	sr_shiftOut(digits, sizeof(digits));
}


