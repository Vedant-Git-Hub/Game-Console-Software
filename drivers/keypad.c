#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../includes/keypad.h"

typedef void (*CallBack)(KEY_ID, EDGE);

CallBack keyPressInterrupt;

void keypad_init(CallBack func)
{
	DDRC &= ~(1 << UP_KEY);
        DDRC &= ~(1 << DOWN_KEY); 
	DDRC &= ~(1 << SELECT_KEY);
	DDRC &= ~(1 << LEFT_KEY);
	DDRC &= ~(1 << RIGHT_KEY);
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11) | (1 << PCINT12);
	keyPressInterrupt = func;
	sei();
}

ISR(PCINT1_vect)
{
	PCMSK1 &= ~(1 << PCINT8) & ~(1 << PCINT9) & ~(1 << PCINT10) & ~(1 << PCINT11) & ~(1 << PCINT12);

	_delay_ms(70);

	if(PINC & (1 << UP_KEY))
		keyPressInterrupt(UP, RISING);

	if(PINC & (1 << DOWN_KEY))
		keyPressInterrupt(DOWN, RISING);

	if(PINC & (1 << SELECT_KEY))
		keyPressInterrupt(SELECT, RISING);

	if(PINC & (1 << LEFT_KEY))
		keyPressInterrupt(LEFT, RISING);

	if(PINC & (1 << RIGHT_KEY))
		keyPressInterrupt(RIGHT, RISING);

	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11) | (1 << PCINT12);
}
