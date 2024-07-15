#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "../includes/speaker.h"
#include "../includes/glcd.h"



int main()
{
	speaker_init();	
	while(1)
	{
		speaker_playTone(SA_H);
		_delay_ms(1000);
		speaker_stop();
		_delay_ms(1000);	
	}
}
