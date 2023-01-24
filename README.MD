# STM32 HAL NMEA GPS library
This library allows quick readout of the NMEA sentences from the GPS module. Tested with the NEO-6M module and STM32 Nucleo F411RE board.

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

//when the data is received point it to the parser, then reset the data buffer
neo6m_parse(&myData, DataBuffer);
memset(DataBuffer, 0, BufferSize);
```

### Data readout
The NMEA library is passing data to the following `GPS` structure:
```c
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
It is worth noting that the library may miss some messages due to invalid checksums, or the receive buffer not containing a whole NMEA message.
## Example
The example configured for STM32 Nucleo F411RE is provided in `Core/Src/main.c` It is set to use UART1 as a NMEA GPS serial port and UART2 as a debug serial port. The debug port is used to print the data to the console. UART1 data is received with HAL DMA peripheral.

## License
This code is licensed under a MIT License. See the LICENSE file for details.