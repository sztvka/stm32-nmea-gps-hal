//
// Created by sztuka on 22.01.2023.
//
#include "neo6m_parse.h"



char *data[15];

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
       if(strstr(data[i], "\r\n")!=NULL){
           int counter = 0;
           if(strstr(data[i], "GPGSA")!=NULL){
               char *marker = strtok(data[i], ",");
               while (marker!=NULL){
                     values[counter++] = malloc(strlen(marker)+1); //free later!!!!!!
                     strcpy(values[counter-1], marker);
                     marker = strtok(NULL, ",");
               }
           }
           else if(strstr(data[i], "GPGLL")!=NULL){
                   memset(values, 0, sizeof(values));
                   char *marker = strtok(data[i], ",");
                   while (marker!=NULL){
                       values[counter++] = malloc(strlen(marker)+1); //free later!!!!!!
                       strcpy(values[counter-1], marker);
                       marker = strtok(NULL, ",");
                   }
                   char latSide = values[2][0];
                   if(latSide == 'S' || latSide == 'N'){ //check if data is sorta intact
                       char lat_d[2];
                       char lat_m[8];
                       for(int z = 0; z<2; z++) lat_d[z] = values[1][z];
                       for(int z = 0; z<7; z++) lat_m[z] = values[1][z+2];

                       int lat_deg_strtol = strtol(lat_d, NULL, 10);

                       float lat_min_strtof = strtof(lat_m, NULL);
                       double lat_deg = lat_deg_strtol + lat_min_strtof/60;
                       //   0123456789
                       //lat ddmm.mmmm
                       //lon dddmm.mmmm


                       char lon_d[3];
                       char lon_m[8];
                       char lonSide = values[4][0];
                       for(int z = 0; z<3; z++) lon_d[z] = values[3][z];
                       for(int z = 0; z<7; z++) lon_m[z] = values[3][z+3];

                       int lon_deg_strtol = strtol(lon_d, NULL, 10);
                       float lon_min_strtof = strtof(lon_m, NULL);
                       double lon_deg = lon_deg_strtol + lon_min_strtof/60;

                       gps_data->latitude = lat_deg;
                       gps_data->longitude = lon_deg;
                       gps_data->latSide = latSide;
                       gps_data->lonSide = lonSide;
                   }


           }

       }
    }

}