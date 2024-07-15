#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "../includes/srdriver.h"

static void sr_setLatch()
{
	PORTD |= (1 << LATCH_PIN);
}

static void sr_resetLatch()
{
	PORTD &= ~(1 << LATCH_PIN);
}

static void sr_setClock()
{
	PORTD |= (1 << CLOCK_PIN);
}

static void sr_resetClock()
{
	PORTD &= ~(1 << CLOCK_PIN);
}

static void sr_setData()
{
	PORTD |= (1 << DATA_PIN);
}

static void sr_resetData()
{
	PORTD &= ~(1 << DATA_PIN);
}

void sr_init()
{
	uint8_t data[] = {0x00, 0x00, 0x00};

	DDRD |= (1 << DATA_PIN) | (1 << LATCH_PIN) | (1 << CLOCK_PIN);
	
	sr_resetLatch();
	sr_resetClock();
	sr_resetData();
	_delay_ms(2);
	sr_shiftOut(data, 3);
}

void sr_shiftOut(uint8_t *data, uint8_t len)
{
	sr_resetLatch();
	sr_resetClock();

	for(uint8_t index = 0; index < len; index++)
	{
		for(int8_t bitNum = 7; bitNum >= 0; bitNum--) /* this loop taught an imp lesson*/
		{
			sr_resetClock();

			if((data[index] >> bitNum) & 0x01) 
				sr_setData(); 
			else	
				sr_resetData();

			sr_setClock();
		}
	}

	sr_setLatch();
	sr_resetClock();
}


