#include "app.h"
#include "flashData.h"




void initialize_drivers()
{
	glcd_init();
	glcd_clearText();
	_delay_ms(500);
	glcd_clearScrn();
	glcd_loadBuffer();
	seg7_init();
	speaker_init();
	for(uint8_t i = 0; i < 4; i++)
		glcd_clearLine(i);
}


void app_run()
{
	startupScreen();
	while(1)
	{

		
	}
}
