#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "7seg.h"
#include "keypad.h"
#include "speaker.h"



int main()
{
	speaker_init();	
	while(1)
	{
		speaker_playTone(GA_K_M);
		_delay_ms(1000);
		speaker_stop();
		_delay_ms(1000);	
	}
}
