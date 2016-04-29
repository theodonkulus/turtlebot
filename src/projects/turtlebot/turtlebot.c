/*
 * File:		ziggy.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "movement.h"
#include "timer.h"

#ifdef CMSIS
#include "start.h"
#endif 
/********************************************************************/
int main (void)
{
  char ch = 0x00;
//	char action_done = 0x00;
	//unsigned int current_frame = 0;
	unsigned long long current_time = 0;
	
#ifdef CMSIS  // If we are conforming to CMSIS, we need to call start here
    start();
#endif
  setup_life_timer();      
	printf("\n\r\n\r*** Turtlebot v0.5 ***\n\r");
	init_movement();
	ch = 0x30;
	default_state();
	while(1)
	{
	  current_time = get_time();
		if(char_present()) {
		  ch = in_char();
		  out_char(ch);
      test_action(ch);
			printf("\r\n\r*** Current time  %llu***\n\r", current_time);
			//action_done = 0;
	  }
    /*if(ch == 0x20) {		
			if(!action_done) {
				  position.current_frame = 0;
				  action_done = 1;
			 }
		   walk_forward(&position);
			 if(current_frame!= position.current_frame) {
          printf("\n\r frame %d %llu \n\r", position.current_frame, current_time);
				  current_frame  = position.current_frame;
       }
		} else {
			 if(!action_done) {
			    test_action(ch);
				  action_done = 1;
			 }
		} */
	} 
}
/********************************************************************/
