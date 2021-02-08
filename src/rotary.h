#ifndef rotary_h
#define rotary_h

#include <libopencm3/stm32/gpio.h>

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

typedef struct rotary_encoder {
	unsigned char	state;
	uint32_t		gpioport;
	uint16_t		pin1;
	uint16_t	 	pin2;
} RotaryEncoder;

RotaryEncoder rotary_init(uint32_t gpioport, uint16_t pin1, uint16_t pin2);
unsigned char rotary_process(RotaryEncoder *re);

#endif
