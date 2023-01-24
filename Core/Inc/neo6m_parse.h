//
// Created by sztuka on 22.01.2023.
//

#ifndef STM32_SERIAL_DMA_NEO6M_PARSE_H
#define STM32_SERIAL_DMA_NEO6M_PARSE_H

#endif //STM32_SERIAL_DMA_NEO6M_PARSE_H
#include <stm32f4xx.h>
#include <string.h>
#include <stdlib.h>


/*******************************************************************************
 * @brief GPS data structure for storing parsed data
 ******************************************************************************/
typedef struct NEO6M_DATA {
    double latitude;
    char latSide;
    double longitude;
    char lonSide;
    float altitude;
    float hdop;
    int satelliteCount;
    int fix;
} GPS;
/*******************************************************************************
 * @brief Parses NMEA data from the GPS module
 * @param gps_data Pointer to GPS struct, writes data to it
 * @param buffer Pointer to buffer string with NMEA data
 ******************************************************************************/
void neo6m_parse(GPS *gps_data, uint8_t *buffer);