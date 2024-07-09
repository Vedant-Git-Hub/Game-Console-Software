#include "spi.h"
#include <avr/io.h>
#include <stdint.h> 



void spi_init()
{
        SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << CPOL) | (1 << CPHA);
	DDRB |= (1 << PB2);
        DDRB |= (1 << MOSI_DIR);
	DDRB |= (1 << SCK_DIR); 
	DDRB |= (1 << CS);
        DDRB &= ~(1 << MISO_DIR);
}

void spi_writeByte(uint8_t data)
{
        SPDR = data;

        while(!(SPSR & (1 << SPIF)));
}

void spi_setCS()
{
       PORTB |= (1 << CS);
}

void spi_resetCS()
{
       PORTB &= ~(1 << CS);
}

