#include <stdint.h>
#include "pwm.h"
#include "speaker.h"



void speaker_init()
{
	pwm_init();
}

void speaker_playTone(uint16_t note)
{
	pwm_setFrequency(note);
}

void speaker_stop()
{
	pwm_setFrequency(0);
}
