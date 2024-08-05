/*
 * uart.c
 *
 *  Created on: Jul 30, 2024
 *      Author: tdat
 */

#include "uart.h"

uint8_t rxbyte;
UART_Driver uart1 = { .huart.Instance = USART1, .isInitialized = 0 };
UART_Driver uart2 = { .huart.Instance = USART2, .isInitialized = 0 };
UART_Driver uart3 = { .huart.Instance = USART3, .isInitialized = 0 };

static void UART_MspInit(UART_HandleTypeDef *huart) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (huart->Instance == USART1) {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_9 ;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    if (huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    if (huart->Instance == USART3) {
        __HAL_RCC_USART3_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

int UART_Init(UART_Driver *uart, UART_Config config) {
    if (uart->isInitialized) {
        return -1; // UART đã được khởi tạo trước đó
    }
    uart->config = config;

    uart->huart.Init.BaudRate = config.baudRate;
    uart->huart.Init.WordLength = config.wordLength;
    uart->huart.Init.StopBits = config.stopBits;
    uart->huart.Init.Parity = config.parity;
    uart->huart.Init.Mode = UART_MODE_TX_RX;
    uart->huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart->huart.Init.OverSampling = UART_OVERSAMPLING_16;

    UART_MspInit(&uart->huart);

    if (HAL_UART_Init(&uart->huart) != HAL_OK) {
        return 1; // Khởi tạo thất bại
    }
    uart->isInitialized = 1;
    return 0; // Khởi tạo thành công
}

int init(UART_HandleTypeDef *huart, UART_Config config) {
	if (huart->Instance == USART1) {
		return UART_Init(&uart1, config);
	} else if (huart->Instance == USART2) {
		return UART_Init(&uart2, config);
	} else if (huart->Instance == USART3) {
		return UART_Init(&uart3, config);
    } else {
        return 1; // Không tìm thấy UART phù hợp
    }
}

void UART_SendString(UART_HandleTypeDef *huart, const char *str) {
    HAL_UART_Transmit(huart, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
  if (huart->Instance == USART1) {

	  if (stopBlink){
		  if (rxbyte == 0x03) {  // Kiểm tra lệnh Ctrl+C
			  stopBlink = 0;
		  }
		  else {
			  HAL_UART_Transmit(&uart1.huart, &rxbyte, 1, HAL_MAX_DELAY);
		  }
	  }
	  CircularBuffer_Write(&rxBuffer, rxbyte);
	  HAL_UART_Receive_IT(&uart1.huart, &rxbyte, 1);
  }
}

