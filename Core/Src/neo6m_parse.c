//
// Created by sztuka on 22.01.2023.
//
#include "neo6m_parse.h"



char *data[15];

void neo6m_parse(GPS *gps_data, uint8_t *buffer){
    char * token = strtok(buffer, "$");
    int cnt = 0;
    while(token !=NULL){
        data[cnt++] = malloc(strlen(token)+1); //free later!!!!!
        strcpy(data[cnt-1], token);
        token = strtok(NULL, "$");
    }
    for(int i = 0; i<cnt; i++){
       if(strstr(data[i], "\r\n")!=NULL){
           char* values[25];
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
                   char *marker = strtok(data[i], ",");
                   while (marker!=NULL){
                       values[counter++] = malloc(strlen(marker)+1); //free later!!!!!!
                       strcpy(values[counter-1], marker);
                       marker = strtok(NULL, ",");
                   }
           }

       }
    }

}