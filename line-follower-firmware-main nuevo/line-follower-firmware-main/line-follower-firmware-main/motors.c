#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

const uint8_t ROBO_SPEED = 255; // Límite global (0 a 255)

void init_motors(void)
{
    // Fast PWM de 8 bits en Canales A y B (Timer 1)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler 64 (~1kHz)

    // Configuración de Pines del Nano
    DDRB |= (1 << PB1) | (1 << PB2);              // D9 y D10 (PWM)
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD7); // D4, D5, D7 (Dir)
    DDRB |= (1 << PB0);                           // D8 (Dir)

    OCR1A = 0; 
    OCR1B = 0; 

    // Forzar tierras estáticas para el DRV8833
    PORTD &= ~(1 << PD5); // D5 a GND
    PORTB &= ~(1 << PB0); // D8 a GND
}

void motor_right(uint8_t dir, uint8_t speed) 
{
    uint8_t duty = (uint8_t)(((float)speed / 255.0) * ROBO_SPEED);
    uint8_t sreg = SREG; cli(); 

    if (dir == MOTOR_STOP) {
        OCR1A = 0;
        PORTD &= ~(1 << PD4);
    }
    else if (dir == MOTOR_FORWARD) {
        OCR1A = duty;         
        PORTD &= ~(1 << PD4); 
    }
    else if (dir == MOTOR_BACKWARD) {
        OCR1A = 0;
        PORTD |= (1 << PD4);  
    }
    SREG = sreg; 
}

void motor_left(uint8_t dir, uint8_t speed)
{
    uint8_t duty = (uint8_t)(((float)speed / 255.0) * ROBO_SPEED);
    uint8_t sreg = SREG; cli(); 

    if (dir == MOTOR_STOP) {
        OCR1B = 0;
        PORTD &= ~(1 << PD7);
    }
    else if (dir == MOTOR_FORWARD) {
        OCR1B = duty;         
        PORTD &= ~(1 << PD7); 
    }
    else if (dir == MOTOR_BACKWARD) {
        OCR1B = 0;
        PORTD |= (1 << PD7);  
    }
    SREG = sreg; 
}

void set_motors(uint8_t speed_L, uint8_t speed_R) 
{
    if (speed_L == 0) motor_left(MOTOR_STOP, 0);
    else motor_left(MOTOR_FORWARD, speed_L);

    if (speed_R == 0) motor_right(MOTOR_STOP, 0);
    else motor_right(MOTOR_FORWARD, speed_R);
}