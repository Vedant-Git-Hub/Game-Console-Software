#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "glcd.h"
#include "7seg.h"
#include "keypad.h"
#include "speaker.h"



int main()
{
	uint16_t notes[] = {SA_L, RE_L, GA_L, MA_L, PA_L, DHA_L, NI_L, SA_M, RE_M, GA_M, MA_M, PA_M, DHA_M, NI_M, SA_H, RE_H, GA_H, MA_H, PA_H, DHA_H, NI_H};
	uint8_t note = 0;		
	speaker_init();	
	while(1)
	{
		for(note = 0; note < sizeof(notes)/2; note++)
		{
			speaker_playTone(notes[note]);
			_delay_ms(1000);
		}

		speaker_stop();
	}
}
