#ifndef H_SR_DRIVER_H
#define H_SR_DRIVER_H

#include <stdint.h>
#include <avr/io.h>


#define LATCH_PIN       PD3
#define DATA_PIN        PD2
#define CLOCK_PIN       PD4


void sr_init(void);
void sr_shiftOut(uint8_t *, uint8_t);

#endif
