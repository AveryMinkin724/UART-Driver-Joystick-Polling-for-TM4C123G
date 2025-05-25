#include <stdint.h>

#ifndef JOYSTICK_H
#define JOYSTICK_H

void joystick_init(void);
void poll_adc_samp_seq(void);
void Tiva_UART5_Transmitter_polling(char c);
char* int_2_string(uint32_t x, uint32_t y);
void delay(int volatile iter);

typedef struct {
		uint32_t x;
		uint32_t y;
} adc_value; 

extern adc_value joystick;

#endif 