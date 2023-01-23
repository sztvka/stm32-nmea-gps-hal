//
// Created by sztuka on 22.01.2023.
//
#include "neo6m_parse.h"



char *data[15];

int gps_checksum(char *nmea_data)
{
    char recv_crc[2];
    recv_crc[0] = nmea_data[strlen(nmea_data) - 4];
    recv_crc[1] = nmea_data[strlen(nmea_data) - 3];
    int crc = 0;
    int i;
    //exclude the $ sign from the start and the CRLF plus CRC with an * from the end
    for (i = 1; i < strlen(nmea_data) - 5; i ++) {
        crc ^= nmea_data[i];
    }
    int receivedHash = strtol(recv_crc, NULL, 16);
    if (crc == receivedHash) {
        return 1;
    }
    else{
        return 0;
    }
}

int neo6m_GPGLL(GPS *gps_data, char*inputString) {

    char *values[25];
    int counter = 0;
    memset(values, 0, sizeof(values));
    char *marker = strtok(inputString, ",");
    while (marker != NULL) {
        values[counter++] = malloc(strlen(marker) + 1); //free later!!!!!!
        strcpy(values[counter - 1], marker);
        marker = strtok(NULL, ",");
    }
    char latSide = values[2][0];
    if (latSide == 'S' || latSide == 'N') { //check if data is sorta intact
        char lat_d[2];
        char lat_m[8];
        for (int z = 0; z < 2; z++) lat_d[z] = values[1][z];
        for (int z = 0; z < 7; z++) lat_m[z] = values[1][z + 2];

        int lat_deg_strtol = strtol(lat_d, NULL, 10);

        float lat_min_strtof = strtof(lat_m, NULL);
        double lat_deg = lat_deg_strtol + lat_min_strtof / 60;

        char lon_d[3];
        char lon_m[8];
        char lonSide = values[4][0];
        for (int z = 0; z < 3; z++) lon_d[z] = values[3][z];
        for (int z = 0; z < 7; z++) lon_m[z] = values[3][z + 3];

        int lon_deg_strtol = strtol(lon_d, NULL, 10);
        float lon_min_strtof = strtof(lon_m, NULL);
        double lon_deg = lon_deg_strtol + lon_min_strtof / 60;

        gps_data->latitude = lat_deg;
        gps_data->longitude = lon_deg;
        gps_data->latSide = latSide;
        gps_data->lonSide = lonSide;
        for(int i = 0; i<counter; i++) free(values[i]);

        return 1;
    }
}

void neo6m_parse(GPS *gps_data, uint8_t *buffer){
    memset(data, 0, sizeof(data));
    char * token = strtok(buffer, "$");
    int cnt = 0;
    while(token !=NULL){
        data[cnt++] = malloc(strlen(token)+1); //free later!!!!!
        strcpy(data[cnt-1], token);
        token = strtok(NULL, "$");
    }
    for(int i = 0; i<cnt; i++){
       char* values[25];
       if(strstr(data[i], "\r\n")!=NULL && gps_checksum(data[i])){
           if(strstr(data[i], "GPGLL")!=NULL){
               neo6m_GPGLL(gps_data, data[i]);
           }

       }

    }


}