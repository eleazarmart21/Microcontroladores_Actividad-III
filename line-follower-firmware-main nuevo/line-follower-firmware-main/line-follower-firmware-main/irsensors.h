#ifndef irsensors_H_
#define irsensors_H_

#define SENSOR1 0 // Extrema Derecha
#define SENSOR2 1
#define SENSOR3 2
#define SENSOR4 3 // Centro Derecha
#define SENSOR5 4 // Centro Izquierda
#define SENSOR6 5
#define SENSOR7 6
#define SENSOR8 7 // Extrema Izquierda

void read_all_qtr(uint8_t *arreglo_sensores);

#endif