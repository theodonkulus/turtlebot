// movement.c
// Dec 7th 2015
//  Theo Themistokleous
//Used to define movements for this robot
//All movement functions of robot go in and are called from here

#include "movement.h"
#include "pwm.h"
#include "timer.h"

volatile uint32_t * servo_regmap[NUM_OF_SERVOS] = 
{&TPM0_C3V, &TPM0_C2V, &TPM0_C4V, &TPM0_C5V, &TPM0_C0V, &TPM0_C1V, &TPM1_C0V, &TPM1_C1V};

//pwm structure that holds data about servos and stuff
pwm_channel_t channels[NUM_OF_SERVOS];

#define NUM_OF_CHANNELS 8
void init_movement(void)
{  //Put servos to neutral
	 uint16 i = 0;
	 uint16 neut_ticks =  degrees_to_ticks(90);
	 
	 Configure_TPM0(SERVO_PERIOD);
   Configure_TPM1(SERVO_PERIOD);
	 //Configure_clock();
	 //NEUTRAL_POSITION;

   memset(channels, 0, sizeof(channels));
   for (i = 0; i < NUM_OF_CHANNELS; i++)
   {
       channels[i].channel_num = i;
       channels[i].max_angle = 180;
       channels[i].min_angle = 0;
       channels[i].target_reg = servo_regmap[i];
		   //ch_move(&channels[i], 0);
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
uint16 front_left_hip_angle = 0;
uint16 front_left_knee_angle = 0;
uint16 front_right_hip_angle = 0;
uint16 front_right_knee_angle = 0;
uint16 back_left_hip_angle = 0;
uint16 back_left_knee_angle = 0;
uint16 back_right_hip_angle = 0;
uint16 back_right_knee_angle = 0;


void test_action(const char ch)
{
   //walkState(move_state);
	 switch(ch)
	 {
     //FRONT LEFT HIP TESTS
		 case 0x71: // q     
			  front_left_hip_angle += 5;
        printf("\n\r\n\r Front_left_hip state set %d NUM%d ticks %d angle %d\n\r", 
           front_left_hip_angle, 
           channels[FRONT_LEFT_HIP].channel_num, 
           channels[FRONT_LEFT_HIP].servo_ticks, 
           channels[FRONT_LEFT_HIP].current_angle);
				break;
		 case 0x77: // w
			  front_left_hip_angle -= 5;
        printf("\n\r\n\r Front_left_hip state set %d NUM%d ticks %d angle %d\n\r", 
           front_left_hip_angle, 
           channels[FRONT_LEFT_HIP].channel_num, 
           channels[FRONT_LEFT_HIP].servo_ticks, 
           channels[FRONT_LEFT_HIP].current_angle);
				break;
     //FRONT LEFT KNEE TESTS
		 case 0x65: // e
			  front_left_knee_angle += 5; 
        printf("\n\r\n\r Front_left_knee state set %d NUM%d ticks %d angle %d\n\r", 
           front_left_knee_angle, 
           channels[FRONT_LEFT_KNEE].channel_num, 
           channels[FRONT_LEFT_KNEE].servo_ticks, 
           channels[FRONT_LEFT_KNEE].current_angle);

				break;
		 case 0x72: // r
        front_left_knee_angle -= 5; 
        printf("\n\r\n\r Front_left_knee state set %d NUM%d ticks %d angle %d\n\r", 
           front_left_knee_angle, 
           channels[FRONT_LEFT_KNEE].channel_num, 
           channels[FRONT_LEFT_KNEE].servo_ticks, 
           channels[FRONT_LEFT_KNEE].current_angle);
				break;
     //FRONT RIGHT HIP TESTS   
		 case 0x61: //a
			  front_right_hip_angle += 5; 
        printf("\n\r\n\r Front_right_hip state set %d NUM%d ticks %d angle %d\n\r", 
           front_right_hip_angle, 
           channels[FRONT_RIGHT_HIP].channel_num, 
           channels[FRONT_RIGHT_HIP].servo_ticks, 
           channels[FRONT_RIGHT_HIP].current_angle);
			 break;
		 case 0x73: // s
			  front_right_hip_angle -= 5; 
        printf("\n\r\n\r Front_right_hip state set %d NUM%d ticks %d angle %d\n\r", 
           front_right_hip_angle, 
           channels[FRONT_RIGHT_HIP].channel_num, 
           channels[FRONT_RIGHT_HIP].servo_ticks, 
           channels[FRONT_RIGHT_HIP].current_angle);
			 break;
		 case 0x64: // d
     //FRONT RIGHT KNEE TESTS   
		     front_right_knee_angle += 5; 
        printf("\n\r\n\r Front_right_kne state set %d NUM%d ticks %d angle %d\n\r", 
           front_right_knee_angle, 
           channels[FRONT_RIGHT_KNEE].channel_num, 
           channels[FRONT_RIGHT_KNEE].servo_ticks, 
           channels[FRONT_RIGHT_KNEE].current_angle);
				break;
		 case 0x66: // f
			  front_right_knee_angle -= 5; 
        printf("\n\r\n\r Front_right_kne state set %d NUM%d ticks %d angle %d\n\r", 
           front_right_knee_angle, 
           channels[FRONT_RIGHT_KNEE].channel_num, 
           channels[FRONT_RIGHT_KNEE].servo_ticks, 
           channels[FRONT_RIGHT_KNEE].current_angle);
				break;
		      //BACK LEFT HIP TESTS
		 case 0x79: // y 
			  back_left_hip_angle += 5;
        printf("\n\r\n\r Back_left_hip state set %d NUM%d ticks %d angle %d\n\r", 
           back_left_hip_angle, 
           channels[BACK_LEFT_HIP].channel_num, 
           channels[BACK_LEFT_HIP].servo_ticks, 
           channels[BACK_LEFT_HIP].current_angle);
				break;
		 case 0x75: // u
			  back_left_hip_angle -= 5;
        printf("\n\r\n\r Back_left_hip state set %d NUM%d ticks %d angle %d\n\r", 
           back_left_hip_angle, 
           channels[BACK_LEFT_HIP].channel_num, 
           channels[BACK_LEFT_HIP].servo_ticks, 
           channels[BACK_LEFT_HIP].current_angle);
				break;
     //BACK LEFT KNEE TESTS
		 case 0x69: // i
			  back_left_knee_angle += 5; 
        printf("\n\r\n\r Back_left_knee state set %d NUM%d ticks %d angle %d\n\r", 
           back_left_knee_angle, 
           channels[BACK_LEFT_KNEE].channel_num, 
           channels[BACK_LEFT_KNEE].servo_ticks, 
           channels[BACK_LEFT_KNEE].current_angle);

				break;
		 case 0x6F: // o
        back_left_knee_angle -= 5; 
        printf("\n\r\n\r Back_left_knee state set %d NUM%d ticks %d angle %d\n\r", 
           back_left_knee_angle, 
           channels[BACK_LEFT_KNEE].channel_num, 
           channels[BACK_LEFT_KNEE].servo_ticks, 
           channels[BACK_LEFT_KNEE].current_angle);
				break;
     //FRONT RIGHT HIP TESTS   
		 case 0x68: //h
			  back_right_hip_angle += 5; 
        printf("\n\r\n\r Back_right_hip state set %d NUM%d ticks %d angle %d\n\r", 
           back_right_hip_angle, 
           channels[BACK_RIGHT_HIP].channel_num, 
           channels[BACK_RIGHT_HIP].servo_ticks, 
           channels[BACK_RIGHT_HIP].current_angle);
			 break;
		 case 0x6A: // j
			  back_right_hip_angle -= 5; 
        printf("\n\r\n\r Back_right_hip state set %d NUM%d ticks %d angle %d\n\r", 
           back_right_hip_angle, 
           channels[BACK_RIGHT_HIP].channel_num, 
           channels[BACK_RIGHT_HIP].servo_ticks, 
           channels[BACK_RIGHT_HIP].current_angle);
			 break;
		 case 0x6B: // k
     //Back RIGHT KNEE TESTS   
		    back_right_knee_angle += 5; 
        printf("\n\r\n\r Back_right_kne state set %d NUM%d ticks %d angle %d\n\r", 
           back_right_knee_angle, 
           channels[BACK_RIGHT_KNEE].channel_num, 
           channels[BACK_RIGHT_KNEE].servo_ticks, 
           channels[BACK_RIGHT_KNEE].current_angle);
				break;
		 case 0x6C: // l
			  back_right_knee_angle -= 5; 
        
        printf("\n\r\n\r Back_right_kne state set %d NUM%d ticks %d angle %d\n\r", 
           back_right_knee_angle, 
           channels[BACK_RIGHT_KNEE].channel_num, 
           channels[BACK_RIGHT_KNEE].servo_ticks, 
           channels[BACK_RIGHT_KNEE].current_angle);
				break;
		 default:
				break;
	 }
	 
	 front_right_knee_angle = ch_move(&channels[FRONT_RIGHT_KNEE], front_right_knee_angle);
	 back_right_knee_angle = ch_move(&channels[BACK_RIGHT_KNEE], back_right_knee_angle);
	 front_right_hip_angle = ch_move(&channels[FRONT_RIGHT_HIP], front_right_hip_angle);
	 back_right_hip_angle = ch_move(&channels[BACK_RIGHT_HIP], back_right_hip_angle);
	 
	 front_left_knee_angle = ch_move(&channels[FRONT_LEFT_KNEE], front_left_knee_angle);
	 back_left_knee_angle = ch_move(&channels[BACK_LEFT_KNEE], back_left_knee_angle);
	 front_left_hip_angle = ch_move(&channels[FRONT_LEFT_HIP], front_left_hip_angle);
	 back_left_hip_angle = ch_move(&channels[BACK_LEFT_HIP], back_left_hip_angle);
}



