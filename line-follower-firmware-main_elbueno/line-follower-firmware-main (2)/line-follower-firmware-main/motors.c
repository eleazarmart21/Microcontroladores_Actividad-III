#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

const uint8_t ROBO_SPEED = 100; // Máximo 255

void init_motors(void)
{
    // --- TIMER 0 (Configura PD5 y PD6) ---
    // Fast PWM, Modo No Invertido para OC0A y OC0B
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64 (~1kHz)

    // --- TIMER 1 (Configura PB1 / Pin D9) ---
    // Fast PWM de 8 bits (Modo 5), Modo No Invertido para OC1A
    TCCR1A = (1 << COM1A1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler 64 (~1kHz)

    // --- TIMER 2 (Configura PD3 / Pin D3) ---
    // Fast PWM, Modo No Invertido para OC2B
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22); // Prescaler 64 (~1kHz)

    // --- CONFIGURAR PINES COMO SALIDAS ---
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6); // D3, D5, D6
    DDRB |= (1 << PB1);                           // D9

    // Inicializar todo apagado
    OCR0A = 0; // D6  (IN1)
    OCR0B = 0; // D5  (IN3)
    OCR1A = 0; // D9  (IN2)
    OCR2B = 0; // D3  (IN4)
}

void motor_right(uint8_t dir, uint8_t speed) 
{
    uint8_t duty = (uint8_t)(((float)speed / 255.0) * ROBO_SPEED);
    uint8_t sreg = SREG;
    cli(); 

    if (dir == MOTOR_STOP) {
        OCR0A = 0; // D6
        OCR1A = 0; // D9
    }
    else if (dir == MOTOR_FORWARD) {
        OCR0A = duty; // PWM en IN1
        OCR1A = 0;
    }
    else if (dir == MOTOR_BACKWARD) {
        OCR0A = 0;
        OCR1A = duty; // PWM en IN2
    }
    SREG = sreg; 
}

void motor_left(uint8_t dir, uint8_t speed)
{
    uint8_t duty = (uint8_t)(((float)speed / 255.0) * ROBO_SPEED);
    uint8_t sreg = SREG;
    cli(); 

    if (dir == MOTOR_STOP) {
        OCR0B = 0; // D5
        OCR2B = 0; // D3
    }
    else if (dir == MOTOR_FORWARD) {
        OCR0B = duty; // PWM en IN3
        OCR2B = 0;
    }
    else if (dir == MOTOR_BACKWARD) {
        OCR0B = 0;
        OCR2B = duty; // PWM en IN4
    }
    SREG = sreg; 
}

void set_motors(uint8_t speed_L, uint8_t speed_R) {
    if (speed_L == 0) motor_left(MOTOR_STOP, 0);
    else motor_left(MOTOR_FORWARD, speed_L);

    if (speed_R == 0) motor_right(MOTOR_STOP, 0);
    else motor_right(MOTOR_FORWARD, speed_R);
}