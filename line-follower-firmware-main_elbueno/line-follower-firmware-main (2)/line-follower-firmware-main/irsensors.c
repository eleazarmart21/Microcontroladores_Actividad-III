#include <avr/io.h>
#include "adc.h"
#include "irsensors.h"
#include "leds.h"

// Umbral: Voltaje = ((1.5v * 1023) / 5v) = 306.9 -> 307
const uint16_t SENSOR_THRES = 307; 

void init_irsensors(void) {
    adc_init(); // Asegura que el ADC esté listo
    
    // Configurar los pines PD0 (D0) y PD1 (D1) como ENTRADAS digitales
    DDRD &= ~((1 << PD0) | (1 << PD1));
    
    // Opcional: Desactivar resistencias pull-up si tus sensores entregan voltaje puro (5V/0V)
    PORTD &= ~((1 << PD0) | (1 << PD1));
}

uint8_t read_irsensors(void) {
    uint16_t adc_val;
    uint8_t sensor_byte = 0;

    // --- SENSORS 1 AL 6 (Lectura analógica en A0 a A5) ---
    adc_val = read_adc(0);
    if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 0); ledon(1); } else { ledoff(1); }

    adc_val = read_adc(1);
    if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 1); ledon(2); } else { ledoff(2); }

    adc_val = read_adc(2);
    if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 2); ledon(3); } else { ledoff(3); }

    adc_val = read_adc(3);
    if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 3); ledon(4); } else { ledoff(4); }

    adc_val = read_adc(4);
    if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 4); ledon(5); } else { ledoff(5); }

    adc_val = read_adc(5);
    if (adc_val > SENSOR_THRES) { sensor_byte |= (1 << 5); ledon(6); } else { ledoff(6); }

    // --- SENSOR 7 (Lectura digital en Pin D0 / RX) ---
    // Como es digital, revisamos si el pin está en HIGH (1). 
    // Si tu sensor se activa en bajo (0v en negro), cambia el '!=' por '=='
    if ((PIND & (1 << PD0)) != 0) { 
        sensor_byte |= (1 << 6); 
        ledon(7); 
    } else { 
        ledoff(7); 
    }

    // --- SENSOR 8 (Lectura digital en Pin D1 / TX) ---
    if ((PIND & (1 << PD1)) != 0) { 
        sensor_byte |= (1 << 7); 
        ledon(8); 
    } else { 
        ledoff(8); 
    }

    return sensor_byte; // Retorna el byte completo listo para el main.c [S7 S6 S5 S4 S3 S2 S1 S0]
}