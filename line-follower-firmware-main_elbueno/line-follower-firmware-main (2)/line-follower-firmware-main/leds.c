#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"

// Nuevo mapeo ordenado para la fila física de LEDs (LED1 a LED8)
static const uint8_t led_masks_D[] = { (1<<PD2), (1<<PD4), (1<<PD7), 0, 0, 0, 0, 0 };
static const uint8_t led_masks_B[] = { 0, 0, 0, (1<<PB0), (1<<PB2), (1<<PB3), (1<<PB4), (1<<PB5) };

void leds_init(void) {
    // Configurar salidas del Puerto D (Pines D2, D4, D7)
    DDRD |= (1<<PD2) | (1<<PD4) | (1<<PD7);
    
    // Configurar salidas del Puerto B (Pines D8, D10, D11, D12, D13)
    DDRB |= (1<<PB0) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5);

    // Apagar todos inicialmente
    PORTD &= ~((1<<PD2) | (1<<PD4) | (1<<PD7));
    PORTB &= ~((1<<PB0) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5));
}

void ledon(uint8_t id) {
    if (id < 1 || id > 8) return; 
    uint8_t idx = id - 1;

    if (led_masks_D[idx])      PORTD |= led_masks_D[idx];
    else if (led_masks_B[idx]) PORTB |= led_masks_B[idx];
}

void ledoff(uint8_t id) {
    if (id < 1 || id > 8) return;
    uint8_t idx = id - 1;

    if (led_masks_D[idx])      PORTD &= ~led_masks_D[idx];
    else if (led_masks_B[idx]) PORTB &= ~led_masks_B[idx];
}

void test_leds(void) {
    for (int i = 0; i < 3; i++) {
        for (uint8_t id = 1; id <= 8; id++) {
            ledon(id);
            _delay_ms(60);
            ledoff(id);
        }
    }
}