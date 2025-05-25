#include "tm4c.h"
#include "mcu.h"

void mcu_init(void) {
		//stop watchdog timer
		SYSCTL_RCGCWD_R &= ~(1U << 0); // Disable WDT0 clock
		SYSCTL_RCGCWD_R &= ~(1U << 1); // Disable WDT1 clock
	
		/* Config for Main OSC -> PLL -> System CLk */
		/* maybe some overkill in clearing bits */
		/* Use SYSDIV as source */
		//SYSCTL_RCC_R &= ~(0xF << 23); //clear 4 bits in register
		//SYSCTL_RCC_R |= (0xB << 23); //set divisor to 12, (200Mhz / 12 = 16.67 MHz)
		//SYSCTL_RCC_R |= (1U << 22); //USESYSDIV
		SYSCTL_RCC_R |= (1U << 11); // SET BYPASS bit
		SYSCTL_RCC_R &= ~(0x1F << 6); // Clear XTAL bits
		SYSCTL_RCC_R |= (0x15 << 6); // Crystal Value to 16MHz (we are configuing this to go into PLL but we could alternatvely bypass the PLL, divide by 1 and use this straight up)
		SYSCTL_RCC_R &= ~(0x3 << 4); // slect main OSC by clearing bits 4&5
		SYSCTL_RCC_R &= ~(1U << 0); //enable main oscillator

}