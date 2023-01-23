//
// Created by sztuka on 22.01.2023.
//

#ifndef STM32_SERIAL_DMA_NEO6M_PARSE_H
#define STM32_SERIAL_DMA_NEO6M_PARSE_H

#endif //STM32_SERIAL_DMA_NEO6M_PARSE_H
#include <stm32f4xx.h>
#include <string.h>
#include <stdlib.h>

typedef struct NEO6M_DATA {
    float latitude;
    float longitude;
    float altitude;
    float speed;
    float course;
    int satellites;
    int fix;
    int fix_quality;
    int fix_mode;
    int fix_type;
} GPS;
void neo6m_parse(GPS *gps_data, uint8_t *buffer);