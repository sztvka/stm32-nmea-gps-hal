# STM32 HAL NMEA GPS library
[![CMake](https://github.com/sztvka/stm32-nmea-gps-hal/actions/workflows/cmake.yml/badge.svg)](https://github.com/sztvka/stm32-nmea-gps-hal/actions/workflows/cmake.yml)  
This library allows quick readout of the NMEA sentences from the GPS module. The core idea was to provide freedom with serial readout methods and serial buffer sizing, in contrast to most other libraries, where the whole serial peripheral is controlled by the lib. Tested with the NEO-6M module and STM32 Nucleo F411RE board.  
Parsed NMEA commands:
- [$GPGSA](http://aprs.gids.nl/nmea/#gsa) - GPS active satellites count
- [$GPGLL](http://aprs.gids.nl/nmea/#gll) - GPS position
- [$GPGGA](http://aprs.gids.nl/nmea/#gga) - GPS position with altitude and [HDOP](https://en.wikipedia.org/wiki/Horizontal_dilution_of_precision)  

I plan to add parsing for satellite info commands in the future, but those don't seem to be necessary for most applications.
## Usage
### Initialization
```c
//include the library
#include "nmea_parse.h"
#define BufferSize 512
//create a GPS data structure
GPS myData;

//read serial data to a buffer, 
//serial readout implementation may vary depending on your needs
//the library is able to work with any buffer size, as long as it contains at least one whole NMEA message
uint8_t DataBuffer[BufferSize];

//when enough data is received point it to the parser, 
//do it outside of a UART interrupt to avoid overrun errors
nmea_parse(&myData, DataBuffer);

```

### Data readout
The NMEA library is passing data to the following `GPS` structure:
```c
typedef struct NMEA_DATA {
    double latitude; //latitude in degrees with decimal places
    char latSide;  // N or S
    double longitude; //longitude in degrees with decimal places
    char lonSide; // E or W
    float altitude; //altitude in meters
    float hdop; //horizontal dilution of precision
    int satelliteCount; //number of satellites used in measurement
    int fix; // 1 = fix, 0 = no fix
    char lastMeasure[10]; // hhmmss.ss UTC of last successful measurement; time read from the GPS module
} GPS;
```
Before reading, remember to check if gps has a fix to avoid reading zeroes, or invalid data.
```c
if(myData.fix == 1) {
    //do something with the data
    //at ex.
    double latitude = myData.latitude;
    double longitude = myData.longitude;
}
```

You can also cross-compare `myData.lastMeasure` with a local RTC system to determine whether the data is fresh.  
It is worth noting that the library may miss some messages due to invalid checksums, or the receive buffer not containing a whole NMEA message.

### Usage on chips other than STM32F4
If you plan on using this library on a chip other than STM32F4 you will need to modify the include on line 9 in the `nmea_parse.h` file
```c
//
// Created by sztuka on 22.01.2023.
//

#ifndef STM32_SERIAL_DMA_NEO6M_PARSE_H
#define STM32_SERIAL_DMA_NEO6M_PARSE_H

#endif //STM32_SERIAL_DMA_NEO6M_PARSE_H
#include <stm32f4xx.h> // <--- change this to your chip's library
#include <string.h>
#include <stdlib.h>
```

## Example
The example configured for STM32 Nucleo F411RE is provided in `Core/Src/main.c` It is set to use UART1 as a NMEA GPS serial port and UART2 as a debug serial port. The debug port is used to print the data to the console. UART1 data is received with HAL DMA peripheral.
![Screenshot](https://user-images.githubusercontent.com/47701797/214410931-3d108bf2-82ae-4c61-9fde-fb6cc6d1ce13.png)


## License
This code is licensed under a MIT License. See the LICENSE file for details.
