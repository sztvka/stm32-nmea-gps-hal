//
// Created by sztuka on 22.01.2023.
//

#ifndef STM32_SERIAL_DMA_NEO6M_H
#define STM32_SERIAL_DMA_NEO6M_H

#endif //STM32_SERIAL_DMA_NEO6M_H
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <string.h>
void neo6m_init(struct __DMA_HandleTypeDef dma_usart, struct __UART_HandleTypeDef *huart);
void neo6m_interrupt_handle(UART_HandleTypeDef *huart, uint16_t Size);