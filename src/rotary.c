#include "rotary.h"
#include <libopencm3/stm32/gpio.h>

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};

RotaryEncoder rotary_init(uint32_t gpioport, uint16_t pin1, uint16_t pin2) {
	RotaryEncoder encoder;
	encoder.state = R_START;
	encoder.gpioport = gpioport;
	encoder.pin1 = pin1;
	encoder.pin2 = pin2;
	gpio_mode_setup(gpioport, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, pin1 | pin2);

	return encoder;
}

unsigned char rotary_process(RotaryEncoder *re) {
	uint16_t pin_values = gpio_get(re->gpioport, re->pin1 | re->pin2);
	// Grab state of input pins.
	unsigned char pinstate = ((pin_values & re->pin2 ? 1 : 0) << 1) | (pin_values & re->pin1 ? 1 : 0);
	// Determine new state from the pins and state table.
	re->state = ttable[re->state & 0xf][pinstate];
	// Return emit bits, ie the generated event.
	return re->state & 0x30;
}
