// movement.c
// Dec 7th 2015
//  Theo Themistokleous
//Used to define movements for this robot
//All movement functions of robot go in and are called from here

#include "movement.h"
#include "pwm.h"
#include "timer.h"

volatile uint32_t * servo_regmap[NUM_OF_SERVOS] = 
{&TPM0_C3V, &TPM0_C2V, &TPM0_C4V, &TPM0_C5V, &TPM0_C5V, &TPM0_C5V, &TPM0_C5V, &TPM0_C5V};

//pwm structure that holds data about servos and stuff
pwm_channel_t channels[NUM_OF_SERVOS];

#define NUM_OF_CHANNELS 8
void init_movement(void)
{  //Put servos to neutral
	 uint16 i = 0;
	 uint16 neut_ticks =  degrees_to_ticks(90);
	 Configure_TPM0(SERVO_PERIOD);
   //Confiure_TPM1(SERVO_PERIOD);
	 //NEUTRAL_POSITION;

   memset(channels, 0, sizeof(channels));
   for (i = 0; i < NUM_OF_CHANNELS; i++)
   {
       channels[i].channel_num = i;
       channels[i].max_angle = SERVO_MAX;
       channels[i].min_angle = SERVO_MIN;
       channels[i].target_reg = servo_regmap[i];
   }
}

////check whether we need to transition to the next frame
//static unsigned int walkState(movement_state_t * move_state)
//{
//  if(get_curr_time_diff(&(move_state->frame_start)) >= move_state->frame_delay)
//  {
//     move_state->current_frame++;
//     if(move_state->current_frame >= move_state->max_frames)
//     {
//        move_state->current_frame = 0;
//     }
//     move_state->frame_start = get_time();
//  }
//  return move_state->current_frame;
//}

//Incrimental movement functions
//incriment a joint based on our sub frame delay parameters
//static void _incriment_move(uint16 *current_state, 
//                      const uint16 target_position,
//                      unsigned long long * start, 
//                      const unsigned long long * delay)
//{ //either returns how much to tick by or 0.      
//  if((get_curr_time_diff(start)) >= (*delay))
//  {
//     if(*current_state > target_position)
//		 {
//        (*current_state)-= 1;
//     } else if (*current_state < target_position) {
//			  (*current_state)+= 1;
//		 }
//     *start = get_time();
//  }
//}

//static void _inc_neutral_position(movement_state_t * move_state)
//{

//}
uint16 front_left_hip_angle = SERVO_MIN;
uint16 front_left_knee_angle = SERVO_MIN;
uint16 front_right_hip_angle = SERVO_MIN;
uint16 front_right_knee_angle = SERVO_MIN;

void test_action(const char ch)
{
   //walkState(move_state);
	 switch(ch)
	 {
		 case 0x30: // 0
				break;
		 case 0x31: // 1
				break;
		 case 0x32: // 2
				break;
		 case 0x33: // 3
				break;
		 case 0x34: // 4
				break;
		 case 0x35: // 5
				break;
		 case 0x36: // 6
				break;
		 case 0x37: // 7
				break;
		 case 0x38: // 8
				break;
     //FRONT LEFT HIP TESTS
		 case 0x71: // q
        printf("\n\r\n\r Front_left_hip move +++ \n\r");
        front_left_hip_angle += 5; 
        ch_move(&channels[FRONT_LEFT_HIP], front_left_hip_angle);
				break;
		 case 0x77: // w
        printf("\n\r\n\r Front_left_hip move --- \n\r"); 
        front_left_hip_angle -= 5; 
        ch_move(&channels[FRONT_LEFT_HIP], front_left_hip_angle);
				break;
     //FRONT LEFT KNEE TESTS
		 case 0x65: // e
        printf("\n\r\n\r Front_left_knee move +++ \n\r"); 
        front_left_knee_angle += 5; 
        ch_move(&channels[FRONT_LEFT_KNEE], front_left_knee_angle);
				break;
		 case 0x72: // r
        front_left_knee_angle -= 5; 
        ch_move(&channels[FRONT_LEFT_KNEE], front_left_knee_angle);
        printf("\n\r\n\r Front_left_knee move --- \n\r"); 
				break;
     //FRONT RIGHT HIP TESTS   
		 case 0x61: //a
        printf("\n\r\n\r Front_right_hip move +++ \n\r"); 
        front_right_hip_angle += 5; 
        ch_move(&channels[FRONT_RIGHT_HIP], front_right_hip_angle);
			 break;
		 case 0x73: // s
       printf("\n\r\n\r Front_right_hip move --- \n\r"); 
        front_right_hip_angle -= 5; 
        ch_move(&channels[FRONT_RIGHT_HIP], front_right_hip_angle);
			 break;
		 case 0x64: // d
     //FRONT RIGHT KNEE TESTS   
        printf("\n\r\n\r Front_right_knee move +++ \n\r"); 
        front_right_knee_angle += 5; 
        ch_move(&channels[FRONT_RIGHT_KNEE], front_right_knee_angle);
				break;
		 case 0x66: // f
        printf("\n\r\n\r Front_right_knee move --- \n\r"); 
        front_right_knee_angle -= 5; 
        ch_move(&channels[FRONT_RIGHT_KNEE], front_right_knee_angle);
				break;
		 case 0x67: //g
			 break;
		 case 0x68: //h
			 break;
		 case 0x6A: //j
				break;
		 case 0x7A: //z
				break;
		 case 0x78: //x 
				break;
		 case 0x63: //c 
				break;
		 case 0x76: //v
				break;
		 case 0x62: //b 
				break;
		 case 0x6e: //n 
	      break;
		 case 0x6d: //m 
				break;
		 case 0x3C: //< 
				break;
		 default:
				break;
	 }
}



