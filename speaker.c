#include <stdint.h>
#include "pwm.h"
#include "speaker.h"



void speaker_init()
{
	pwm_init();
	pwm_stop();
}

void speaker_start()
{
	pwm_start();
}

void speaker_playTone(uint16_t note)
{
	pwm_start();
	pwm_setFrequency(note);
}

void speaker_stop()
{
	pwm_stop();
}
