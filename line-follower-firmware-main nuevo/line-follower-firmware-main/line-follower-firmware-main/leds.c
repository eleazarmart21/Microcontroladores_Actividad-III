#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motors.h"
#include "irsensors.h"
#include "leds.h"

// Velocidad base suave para las primeras pruebas
#define BASE_SPEED 130  

// Constantes PID (Se ajustan en la pista)
float kp = 3.0;       
float kd = 3.0;       
float ki = 1.0;        

int32_t eInteg = 0;    
int32_t ePrev = 0;     

float pid_controller(float cur_position, float set_point) {
    float error = set_point - cur_position; 
    
    float p_term = kp * error;
    float i_term = ki * eInteg;
    float d_term = kd * (error - ePrev);
    
    eInteg += error; 
    ePrev = error;   
    
    if (eInteg > 500)  eInteg = 500;
    if (eInteg < -500) eInteg = -500;
    
    return (p_term + i_term + d_term);
}

int main(void) {
    leds_init();
    init_motors();
    init_irsensors();
    
    uint8_t sensors_byte;
    float current_position = 4.5;
    float previous_position = 4.5;
    
    while (1) {
        sensors_byte = read_irsensors();
        
        // Si no detecta nada (fuera de línea), se detiene
        if (sensors_byte == 0x00) {
            set_motors(0, 0); 
            eInteg = 0;       
            continue;
        }
        
        float sum_positions = 0.0;
        uint8_t active_sensors_count = 0;
        
        // Calcular centro de masa
        for (uint8_t i = 0; i < 8; i++) {
            if (sensors_byte & (1 << i)) {
                sum_positions += (float)(i + 1); 
                active_sensors_count++;
            }
        }
        
        if (active_sensors_count > 0) {
            current_position = sum_positions / (float)active_sensors_count;
            previous_position = current_position; 
        } else {
            current_position = previous_position; 
        }
        
        float control_signal = pid_controller(current_position, 4.5);
        
        // Tracción Diferencial
        int16_t motor_L_speed = BASE_SPEED - (int16_t)control_signal;
        int16_t motor_R_speed = BASE_SPEED + (int16_t)control_signal;
        
        // Límites estrictos de motor para evitar inversiones raras
        if (motor_L_speed < 0)   motor_L_speed = 0;
        if (motor_R_speed < 0)   motor_R_speed = 0;
        if (motor_L_speed > 255) motor_L_speed = 255;
        if (motor_R_speed > 255) motor_R_speed = 255;
        
        set_motors((uint8_t)motor_L_speed, (uint8_t)motor_R_speed);
        
        _delay_ms(6); 
    }
    
    return 0;
}