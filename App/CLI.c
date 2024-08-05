/*
 * CLI.c
 *
 *  Created on: Jul 29, 2024
 *      Author: tdat
 */

#include "CLI.h"

UART_Config uartConfig = {
.baudRate = 115200,
.wordLength = UART_WORDLENGTH_8B,
.stopBits = UART_STOPBITS_1,
.parity = UART_PARITY_NONE,
};

void main_loop(void) {
	if (init(&uart1.huart, uartConfig) != 0) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		return;
	}
	HAL_UART_Receive_IT(&uart1.huart, &rxbyte, 1);
    UART_SendString(&uart1.huart, PROMPT);

    while(1) {
    	CheckAndPrintReceivedData();
    }
}

