#ifndef motors_h_
#define motors_h_

#include <avr/io.h>

#define MOTOR_STOP 	0 
#define MOTOR_BACKWARD	1
#define MOTOR_FORWARD	2

void motors_init();
void motor_right(uint8_t dir,uint8_t speed);
void motor_left(uint8_t dir,uint8_t speed);

#endif /* motors_h_ */