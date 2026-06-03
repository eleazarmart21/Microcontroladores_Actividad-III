#ifndef adc_h_
#define adc_h_
#include <avr/io.h>

void adc_init();
uint16_t read_adc(uint8_t ch);

#endif /* adc_h_ */