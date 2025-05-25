#include <stdint.h>
#include "uart.h"
#include "joystick.h"
#include "mcu.h"
#include "tm4c.h"

void delay(int volatile iter);
adc_value joystick = {0,0}; //global variable to store ADC values in

void delay(int volatile iter) {
    while (iter > 0) {  // delay loop
        --iter;
    }
}

int main(void) {

	mcu_init();
	uart_init(); //Initialize UART (section 14.4 datasheet)
	joystick_init();
	
	UART5_check_connection("Tiva C Connected \n");
	delay(10);
	
	/* Non-Blocking Approach to polling keyboard and joystick */
	while(1)
	{
			// 1. Poll the UART for incoming characters (Non-blocking)
      if ((UART5_FR_R & (1U << 4)) == 0) {  // Check if RX FIFO is not empty
				char c = Tiva_UART5_Receiver_polling(); // get character over UART by typing in putty terminal
				Tiva_UART5_Transmitter_polling(c); 
			}
			
			// 2. Read Joystick X & Y Values from ADC
			poll_adc_samp_seq();
			// 3. Format data (int -> string)
			char* string = int_2_string(joystick.x, joystick.y);
			
			while(*string) { // Loop until null terminator '\0' is reached
					Tiva_UART5_Transmitter_polling(*string);
					string++;
			}
			
			delay(10000); // Small delay to avoid flooding the terminal
	}

		return 0;
}