//
// Created by sztuka on 22.01.2023.
//

#include "neo6m.h"
#define RxBuffer_SIZE 256
#define DataBuffer_SIZE 512
int oldPos = 0;
int newPos = 0;
uint8_t RxBuffer[RxBuffer_SIZE];
uint8_t DataBuffer[DataBuffer_SIZE];
struct __DMA_HandleTypeDef global_dma_usart;
struct __UART_HandleTypeDef global_huart;
char* data_combined[15];

void ParseGPRS(){
    int dataStartArrayPos = 0;
    int dataEndArrayPos = 0;
    /*   for(int i =0; i<DataBuffer_SIZE; i++){
           if(DataBuffer[i] == '$'){
               dataStart[dataStartArrayPos++] = i;
           }
           else if(DataBuffer[i] == '\n'){
               dataEnd[dataEndArrayPos++] = i;
           }
       }
   */
    char * token = strtok(DataBuffer, "$");
    int cnt = 0;
    while(token !=NULL){
        data_combined[cnt++] = malloc(strlen(token)+1);
        strcpy(data_combined[cnt-1], token);
        token = strtok(NULL, "$");
    }
}



void neo6m_init(struct __DMA_HandleTypeDef dma_usart, struct __UART_HandleTypeDef *huart) {
   // HAL_UARTEx_ReceiveToIdle_DMA(huart, RxBuffer, RxBuffer_SIZE);
   // __HAL_DMA_DISABLE_IT(&dma_usart, DMA_IT_HT);
    global_dma_usart = dma_usart;
    global_huart = *huart;
}
void neo6m_interrupt_handle(UART_HandleTypeDef *huart, uint16_t Size){
        oldPos = newPos;
        if(oldPos + Size > DataBuffer_SIZE){
            ParseGPRS();
            memset(DataBuffer, 0, DataBuffer_SIZE);
            oldPos = 0;

            memcpy((uint8_t *)DataBuffer+oldPos, RxBuffer, Size);
            newPos = Size+oldPos;
        }
        else{
            memcpy((uint8_t *)DataBuffer+oldPos, RxBuffer, Size);
            newPos = Size+oldPos;

        }
        for(int i=0; i<Size; i++){

        }
        HAL_UARTEx_ReceiveToIdle_DMA(&global_huart, RxBuffer, RxBuffer_SIZE);
        __HAL_DMA_DISABLE_IT(&global_dma_usart, DMA_IT_HT);

}
