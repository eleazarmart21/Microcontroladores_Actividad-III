#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"
#include "irsensors.h"

// Definición de velocidades (Rango de 0 a 255)
#define VEL_ALTA   250
#define VEL_MEDIA  180
#define VEL_BAJA   120
#define VEL_MINIMA 80

int main(void) {
    // Inicializar periféricos
    init_motors();
    init_irsensors();

    uint8_t sensors;

    while (1) {
        // Lee el byte con el estado de los 8 sensores [S7 S6 S5 S4 S3 S2 S1 S0]
        sensors = read_irsensors(); 

        // Caso: Todos los sensores en blanco (00000000) -> Detener motores
        if (sensors == 0x00) {
            set_motors(0, 0);
        } 
        else {
            uint8_t speed_L = 0;
            uint8_t speed_R = 0;

            // --- LADO IZQUIERDO (Sensores 7, 6, 5, 4) ---
            if (sensors & (1 << 4)) {
                speed_L = VEL_ALTA;   // Centro-izquierda
            } else if (sensors & (1 << 5)) {
                speed_L = VEL_MEDIA;
            } else if (sensors & (1 << 6)) {
                speed_L = VEL_BAJA;
            } else if (sensors & (1 << 7)) {
                speed_L = VEL_MINIMA; // Extremo izquierdo
            }

            // --- LADO DERECHO (Sensores 3, 2, 1, 0) ---
            if (sensors & (1 << 3)) {
                speed_R = VEL_ALTA;   // Centro-derecha
            } else if (sensors & (1 << 2)) {
                speed_R = VEL_MEDIA;
            } else if (sensors & (1 << 1)) {
                speed_R = VEL_BAJA;
            } else if (sensors & (1 << 0)) {
                speed_R = VEL_MINIMA; // Extremo derecho
            }

            // Aplicar velocidades a los motores
            set_motors(speed_L, speed_R);
        }

        _delay_ms(10); // Pausa de estabilidad
    }

    return 0;
}