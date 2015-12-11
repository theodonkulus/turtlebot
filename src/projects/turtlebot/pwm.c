// pwm.c
// Dec 7th 2015
// Theo Themistokleous
//Low level setup and movement control via PWM for ARM freedom board
//Channels are setup to be controlled individually
//If you want to reuse this module for other ports, you must modify Configure_TPM0()
//Note to self
//Make this arbitary in terms boundaries and slope for motors. Saves us from tinkering and having to look at datasheets in the future
#include "pwm.h"

uint16 pulse_width_in_ticks(uint16 period, uint16 duty_cycle)
{//Duty cycle in terms of ticks
		return (period * duty_cycle) / 100;
}

void Configure_TPM0(uint16 period)
{ // All servos set to 
    // Enable the Clock gate to the MODULE!!
    SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTA_MASK;
    
    // Ensure that the module is disabled first
    TPM0_SC = 0x00;
           
    //  PIN CONFIGURATION
    // Configure PTD2 and 3 for TPM functionality
	  PORTA_PCR4 = PORT_PCR_MUX(4); //A4
	  PORTA_PCR5 = PORT_PCR_MUX(4); //A5
    PORTD_PCR2 = PORT_PCR_MUX(4); // D2
    PORTD_PCR3 = PORT_PCR_MUX(4); // D3
	  PORTD_PCR4 = PORT_PCR_MUX(4); // D4
    PORTC_PCR9 = PORT_PCR_MUX(3); //C9
	
    // CLOCK CONFIGURATION
    // Enable the IRCLK
    MCG_C1 |= MCG_C1_IRCLKEN_MASK;
    // Set the IRCLK to fast clock
    MCG_C2 |= MCG_C2_IRCS_MASK;
    
    // Set the TPM clock source to the IRCLK
    SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(3);
    
    // Select a Prescale value of 2 to get a 1us resolution
    TPM0_SC |= TPM_SC_PS(1);
    
    //CHANNEL CONFIGURATIONS   
    // Configure module registers
		TPM0_C0SC = TPM_CnSC_CHF_MASK;
    TPM0_C1SC = TPM_CnSC_CHF_MASK;
    TPM0_C2SC = TPM_CnSC_CHF_MASK;
    TPM0_C3SC = TPM_CnSC_CHF_MASK;
    TPM0_C4SC = TPM_CnSC_CHF_MASK;
		TPM0_C5SC = TPM_CnSC_CHF_MASK;

    // Setup TPM0 Channels for Edge aligned PWM
		TPM0_C0SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
		TPM0_C1SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
    TPM0_C2SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
		TPM0_C3SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
    TPM0_C4SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
		TPM0_C5SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);

    // Initialize Channel value registers
		TPM0_C0V = INIT_VAL;
    TPM0_C1V = INIT_VAL;
    TPM0_C2V = INIT_VAL;
    TPM0_C3V = INIT_VAL;
    TPM0_C4V = INIT_VAL;
		TPM0_C5V = INIT_VAL;
		
    // Configure the MOD register
    TPM0_MOD = period;
    TPM0_CNT = 0;
    
    // Enable TPM0 IRQ (IRQ #17)
    //enable_irq(17);
    
    // Finally Enable the TPM module
    TPM0_SC |= TPM_SC_CMOD(1);
}

uint16 degrees_to_ticks(uint16 degrees)
{
	 if(degrees > 180)
   {
	   return SERVO_MAX;	
	 }
	 return ((10*degrees) + SERVO_MIN);
}

uint16 ticks_to_degrees(uint16 servo_ticks)
{
    uint16 offset_ticks = servo_ticks - SERVO_MIN;

    if(offset_ticks > servo_ticks)
    {//prevent unsigned rollover bugs. 
        offset_ticks = 0;
    }
    
    return (offset_ticks / 10);  
}

//Move servo to desired angle within given bounds. Bounds checking
//is included should we go over the given bounds.
void ch_move(pwm_channel_t * channel, uint16 target_angle)
{
	 uint16 ticks_to_motors = 0;
	 uint16 angle_set = 0;

	 if(target_angle > channel->max_angle)
	 {
	    ticks_to_motors = SERVO_MAX;
      angle_set = channel->max_angle;
	 } 
   else if (target_angle < channel->min_angle) 
   {
	    ticks_to_motors = SERVO_MIN;
      angle_set = channel->min_angle;
   } 
   else 
   {//servo has 0 degrees at 500us , 180 at 2400. y = 10x + 500
      ticks_to_motors = ((10*target_angle) + SERVO_MIN);
      angle_set = target_angle;
	 }

   channel->current_angle = angle_set;
	 *(channel->target_reg) = ticks_to_motors;
   channel->servo_ticks = ticks_to_motors;
}

