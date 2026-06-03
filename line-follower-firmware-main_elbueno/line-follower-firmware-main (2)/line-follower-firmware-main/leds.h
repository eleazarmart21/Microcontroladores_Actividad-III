#ifndef leds_h_
#define leds_h_
#include <avr/io.h>

    void leds_init();
    void test_leds();
    void ledon(uint8_t id);
    void ledoff(uint8_t id);
#endif /* leds_h_ */