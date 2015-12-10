// movement.h
// Jan 3 2014
//  Theo Themistokleous
//Used to define movements for this robot
//Use macros to map channels to actuators and 
#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

#include "pwm.h"
#include "timer.h"


typedef enum servo_item_e
{
    FRONT_LEFT_HIP = 0,
    FRONT_LEFT_KNEE,
    FRONT_RIGHT_HIP,
    FRONT_RIGHT_KNEE,
    BACK_LEFT_HIP,
    BACK_LEFT_KNEE,
	  BACK_RIGHT_HIP,
    BACK_RIGHT_KNEE,
    NUM_OF_SERVOS
}servo_item_t;


#define NEUTRAL_POSITION test_action(0x30);

typedef enum direction_state_e {
   DIRECTION_STOP = 0,
   DIRECTION_FORWARD,
   DIRECTION_BACK,
   DIRECTION_LEFT,
   DIRECTION_RIGHT,
} direction_state_t;

//init and test
void init_movement(void);
void test_action(const char ch);

#endif
