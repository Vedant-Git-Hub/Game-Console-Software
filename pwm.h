#ifndef H_PWM_H
#define H_PWM_H

#include <stdint.h>


#define PRE_SCALAR	1024
#define F_CPU		16000000UL

void pwm_init(void);
void pwm_start(void);
void pwm_setFrequency(uint16_t);
void pwm_stop(void);


#endif
