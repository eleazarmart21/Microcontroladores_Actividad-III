#ifndef MOTORS_H_
#define MOTORS_H_

#include <stdint.h>

// Definiciones de dirección comunes para el proyecto
#define MOTOR_STOP     0
#define MOTOR_FORWARD  1
#define MOTOR_BACKWARD 2

// Prototipos de funciones
void init_motors(void);
void motor_right(uint8_t dir, uint8_t speed);
void motor_left(uint8_t dir, uint8_t speed);
void set_motors(uint8_t speed_L, uint8_t speed_R);

#endif