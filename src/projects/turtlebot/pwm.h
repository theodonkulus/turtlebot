// pwm.h
// Jan 3 2014
// Theo Themistokleous
//Low level setup and movement control via PWM for ARM freedom board
//Channels are setup to be controlled individually
//If you want to reuse this module for other ports, you must modify Configure_TPM0()
//This header contains defines for servo mins and max based on 1us ticks

#ifndef _PWM_H_
#define _PWM_H_

#include "common.h"

//values in terms of uSec
#define SERVO_PERIOD 20000  //20ms in terms of 1us ticks 
#define SERVO_MAX 2400
#define SERVO_MIN 500
#define INIT_VAL 1400

//Quick and dirty way to map register to channels without runtime waste
//Dear future Ted, I'm sorry, once you find a better way to do this

typedef struct pwm_channel_s
{
    uint16 channel_num; //
    uint16 servo_ticks; //useful for debug info
    uint16 current_angle; //state of where the fuck we are
    uint16 max_angle; //bounds for safety
    uint16 min_angle;
    volatile uint32_t * target_reg;//ptr to reg we want to write to
} pwm_channel_t;

uint16 pulse_width_in_ticks(uint16 period, uint16 duty_cycle);
void Configure_clock(void);
void Configure_TPM0(const uint16 period);
void Configure_TPM1(const uint16 period);

uint16 degrees_to_ticks(uint16 degrees);
uint16 ticks_to_degrees(uint16 servo_ticks);
void ch_move(pwm_channel_t * channel, uint16 target_angle);

#endif
