#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "pwm.h"
#include "7seg.h"

static uint8_t ocr0bValue;

void pwm_init()
{
	DDRD |= (1 << PD5);
	TCCR0A |= (1 << WGM01) | (1 << COM0B0);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0B);
	OCR0B = 0;
	sei();
}

void pwm_start()
{
	DDRD |= (1 << PD5);
}

void pwm_setFrequency(uint16_t freq)
{
	uint32_t denominator = ((uint32_t)freq * (uint32_t)2 * (uint32_t)PRE_SCALAR);
	uint32_t numerator = (uint32_t)F_CPU;
	ocr0bValue = (uint8_t) ((numerator/denominator) - (uint32_t)1);	
}

void pwm_stop()
{
	DDRD &= ~(1 << PD5);
}

ISR(TIMER0_COMPB_vect)
{
	TCNT0 = 0;
	OCR0B = ocr0bValue;
}

