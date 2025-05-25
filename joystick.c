#include <stdint.h>
#include <stdio.h>
#include "joystick.h"
#include "tm4c.h"


void joystick_init(void)
{
		/* Enable Clock */
		SYSCTL_RCGCADC_R |= (1U << 0); // to ADC0 module
		SYSCTL_RCGCGPIO_R |= (1U << 4);// to GPIO PORT E
		/* Config Alternate Funtion for : PE3(Vx - analog), PE2(Vy - anolog), PE1(SW - digital) */
		GPIO_PORTE_AFSEL_R |= (1U << 3) | (1U << 2) | (1U << 1);
		/* Digital Enable/Disable */
		GPIO_PORTE_DEN_R &= ~((1U << 3) | (1U << 2)); // Disable  PE3 & PE2
		GPIO_PORTE_DEN_R |= (1U << 1); // Enable PE1
		//config pins for Analog
		GPIO_PORTE_AMSEL_R |= (1U << 3) | (1U << 2);
		
		/* Config ADCs to Anolog pins */
		ADC0_ACTSS_R &= ~(1U << 1); //disable ADC0 SS1 (FIFO Depth 4) so we can configure it
		/* Select Event(trigger) that initiates sampling */
		ADC0_EMUX_R &= ~0xF0; // Processor (PSSI) clear all bits in 7:4 field
		/* Select Analog Channel for Sequencer (AIN0, AIN1, ...) */
		ADC0_SSMUX1_R = (0U << 0) | (1U << 4); //The AINn channel pin you select depends on what bit you write to each bitfield (MUX0-3). (5U << 8) = AIN5 to mux2 (i think)
		/* Mark second sample as end of sequence */
		ADC0_SSCTL1_R = (1U << 2) | (1U << 5) | (1U << 6); //2nd sample last (1U << 5); // Interrupt enable for both samples:(1U << 2) | (1U << 6);
		//ADC0_IM_R |= (1U << 1);  ??   // Enable SS1 interrupt
		/* ADC Sampling rate */
		ADC0_PC_R = 0x3; // 250ksps
		/* Enable ADC0 SS1 */
		ADC0_ACTSS_R |= (1U << 1);
		
		//config pin direction? don't think its needed
		//GPIODIR
		
		//Config Digital Pin?
	
}

void poll_adc_samp_seq(void)
{	
		ADC0_PSSI_R |= (1U << 1); // Begin sampling on Sample Sequencer 1
		while((ADC0_RIS_R & 2) == 0); //Wait until sample conversion completed
		joystick.x = ADC0_SSFIFO1_R;
		while (ADC0_SSFSTAT1_R & (1U << 8)) { } // Wait for FIFO to have next sample. need this or //delay(10000);
		joystick.y = ADC0_SSFIFO1_R;
		ADC0_ISC_R = 2; //clear conversion flag bit		
}

char* int_2_string(uint32_t x, uint32_t y)
{
		/* Declare str array where chars making up the string produced by sprintf will be stored */
		static char str[40]; // 10 digits for uint32 + 1 for null terminator // static so str[0] is stored in peristant memory not stack (local memory thaqt will be wiped away after function is exited)
		snprintf(str, sizeof(str), "Joystick X: %d, Y: %d\r\n", x, y); //stdio.h funct: integer to string
		return str;
}

