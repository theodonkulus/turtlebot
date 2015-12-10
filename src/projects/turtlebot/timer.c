// timer.h
// Jan 11 2014
// Theo Themistokleous
// Low level setup of system HW timers with interrupts
// timers can be setup to be controlled individually
//
#include "timer.h"

void setup_life_timer(void)
{ //setup the global HW uptime counter. DO THIS ON STARTUP
  //make sure we turn the module on from the SGC
  if(!(SIM_SCGC6 & SIM_SCGC6_PIT_MASK)) 
  {
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT_MCR = 0x00;
 
    //chain both timer0 and 1 into a lifetime counter
    //Example in the datasheet 
    PIT_LDVAL1 = 0xFFFFFFFF;
    PIT_TCTRL1 = 0x0;
		PIT_TCTRL1 |= PIT_TCTRL_CHN_MASK;
    PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;

    PIT_LDVAL0 = 0xFFFFFFFF;
    PIT_TCTRL0 = PIT_TCTRL_TEN_MASK;
  }
}

unsigned long long get_time(void)
{ //Get the current time from the life counter
	unsigned long long current_uptime = ((PIT_LTMR64H) << 31);
  return (current_uptime + (PIT_LTMR64L));
}

//get absolute time difference in ticks between timeA and timeB
unsigned long long get_time_diff(const unsigned long long * timea,
                                 const unsigned long long * timeb)
{
  if ((*timea) >= (*timeb)) 
  { 
    return ((*timea) - (*timeb));
  } 
  else
  {
    return ((*timeb) - (*timea));
  }
}

//gets time difference between time and current timer 
unsigned long long get_curr_time_diff(const unsigned long long *time)
{
  unsigned long long current_time = get_time();	
  return get_time_diff(&(current_time), time);
}
