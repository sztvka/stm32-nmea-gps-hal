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

                   char lat_d[2];
                   char lat_m[8];
                   lat_d[0] = values [1][0];
                   lat_d[1] = values [1][1];
                   lat_m[0] = values [1][2];
                   lat_m[1] = values [1][3];
                   lat_m[2] = values [1][4];
                   lat_m[3] = values [1][5];
                   lat_m[4] = values [1][6];
                   lat_m[5] = values [1][7];
                   lat_m[6] = values [1][8];

                   int lat_deg_strtol = strtol(lat_d, NULL, 10);
//                 int lat_deg_int = atoi(lat_d);
                   float lat_min_strtof = strtof(lat_m, NULL);
//                 double lat_min = atof(lat_m);
                   double lat_deg = lat_deg_strtol + lat_min_strtof/60;
                    //   0123456789
                   //lat ddmm.mmmm
                   //lon  dddmm.mmmm
           }

       }
    }

}