#include <avr/io.h>
#include "adc.h"
#include "irsensors.h"
#include "leds.h"

// Umbral para detectar la línea (Ajustable dependiendo de la luz)
const uint16_t SENSOR_THRES = 280; 

void init_irsensors(void) {
    adc_init(); 
}

uint8_t read_irsensors(void) {
    uint16_t adc_val;
    uint8_t sensor_byte = 0;

    adc_val = read_adc(0); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 0); ledon(1); } else { ledoff(1); }
    adc_val = read_adc(1); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 1); ledon(2); } else { ledoff(2); }
    adc_val = read_adc(2); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 2); ledon(3); } else { ledoff(3); }
    adc_val = read_adc(3); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 3); ledon(4); } else { ledoff(4); }
    adc_val = read_adc(4); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 4); ledon(5); } else { ledoff(5); }
    adc_val = read_adc(5); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 5); ledon(6); } else { ledoff(6); }
    adc_val = read_adc(6); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 6); ledon(7); } else { ledoff(7); }
    adc_val = read_adc(7); if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 7); ledon(8); } else { ledoff(8); }

    return sensor_byte;
}