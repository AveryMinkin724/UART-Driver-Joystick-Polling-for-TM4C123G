#include <stdint.h>
#include "uart.h"
#include "tm4c.h"

void delay(int volatile iter);

static void mcu_init(void) {
		//stop watchdog timer
		SYSCTL_RCGCWD_R &= ~(1U << 0); // Disable WDT0 clock
		SYSCTL_RCGCWD_R &= ~(1U << 1); // Disable WDT1 clock

		//Initialize UART (section 14.4 datasheet)
		uart_init();
}

int main(void) {

	mcu_init();

	UART5_check_connection("Tiva C Connected \n");
	delay(10);
	while(1)
	{
		char c = Tiva_UART5_Receiver_polling(); // get character over UART by typing in putty terminal
		Tiva_UART5_Transmitter_polling(c); 
	}

		return 0;
}

void delay(int volatile iter) {
    
    while (iter > 0) {  // delay loop
        --iter;
    }
}