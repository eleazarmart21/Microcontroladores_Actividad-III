#ifndef IRSENSORS_H_
#define IRSENSORS_H_

#include <stdint.h>

void init_irsensors(void);
uint8_t read_irsensors(void);

#endif