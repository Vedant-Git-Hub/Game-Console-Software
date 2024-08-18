#include "common.h"





void strCpyToRam(char *ram, const char *const flash)
{
        memset(ram, 0, 20);
//        char *strPtr = (char *) pgm_read_word(flash);
        strcpy_P(ram, (char *)flash);
}

void delay(unsigned int n)
{
        while(n--)
        {
              _delay_ms(1);
        }
}

