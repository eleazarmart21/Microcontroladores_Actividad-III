#include <avr/io.h>
#include "adc.h"

void adc_init()
{
    // REFS0 = 1 -> Referencia de voltaje AVcc (5V), Alineación a la derecha
    ADMUX = (1 << REFS0);   
    
    // ADEN = 1 -> Habilitar módulo ADC
    // Prescaler de 128 (16MHz / 128 = 125kHz de muestreo estable)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_adc(uint8_t ch)
{
    // Asegurar que el canal esté estrictamente entre 0 y 7
    ch = ch & 0x07;
    
    // Limpiar los bits de canal anteriores y cargar el nuevo
    ADMUX &= 0xF0;
    ADMUX |= ch;
    
    // Iniciar la conversión
    ADCSRA |= (1 << ADSC);
    
    // Esperar a que la conversión termine
    while (ADCSRA & (1 << ADSC));
    
    // Regresar el registro unificado de 10 bits
    return ADC;
}