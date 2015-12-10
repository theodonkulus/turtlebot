// timer.h
// Jan 11 2014
// Theo Themistokleous
// Low level setup of system timers with interrupts
// timers can be setup to be controlled individually
//
#include "common.h"
#define MAX_TIMER 4

void setup_life_timer(void);
unsigned long long get_time(void);
unsigned long long get_time_diff(const unsigned long long * timea,
                                 const unsigned long long * timeb);
unsigned long long get_curr_time_diff(const unsigned long long * time);
