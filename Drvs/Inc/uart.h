/*
 * uart.h
 *
 *  Created on: Jul 30, 2024
 *      Author: tdat
 */

#ifndef __UART_H
#define __UART_H

#include "stm32f1xx_hal.h"

typedef struct {
    uint32_t baudRate;
    uint32_t wordLength;
    uint32_t stopBits;
    uint32_t parity;
} UART_Config;

typedef struct {
    UART_HandleTypeDef huart;
    UART_Config config;
    uint8_t isInitialized;
} UART_Driver;
extern UART_Driver uart1;
extern UART_Driver uart2;
extern UART_Driver uart3;

void UART_SendString(UART_HandleTypeDef *huart, const char *str);
int UART_Init(UART_Driver *uart, UART_Config config);
void send_byte(UART_HandleTypeDef *huart, uint8_t byte);

#endif // __UART_H
