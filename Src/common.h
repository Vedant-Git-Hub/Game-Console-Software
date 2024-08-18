#ifndef H_COMMON_H
#define H_COMMOM_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <avr/pgmspace.h>
#include <util/delay.h>


void strCpyToRam(char *, const char *const);
void delay(unsigned int);




#endif
