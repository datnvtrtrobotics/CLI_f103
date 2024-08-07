/*
 * CLI.c
 *
 *  Created on: Jul 29, 2024
 *      Author: tdat
 */

#include "CLI.h"
#include "uart.h"
#include "circular_bf.h"
#include "GPIO_handle.h"
#include "process.h"
uint8_t byte;
uint16_t myindex = 0;
char buffer[BUFFER_SIZE];

UART_Config uartConfig = {
.baudRate = 115200,
.wordLength = UART_WORDLENGTH_8B,
.stopBits = UART_STOPBITS_1,
.parity = UART_PARITY_NONE,
};

CommandMapping commandMap[] = {
    {"led-on", handleLedOnCommand},
    {"led-off", handleLedOffCommand},
    {"led-blink", handleLedBlinkCommand},
    {"adc-get", handleAdcGetCommand},
    {"info", handleInfoCommand},
    {NULL, handleInvalidCommand}
};
void main_loop(void) {
	if (UART_Init(&uart1,uartConfig) !=0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		return;
	}
	HAL_UART_Receive_IT(&uart1.huart, &byte, 1);

    while(1) {

		while(CircularBuffer_Read(&rxBuffer, &byte)) {
			send_byte(&uart1.huart,byte);
			checkCtrlC(byte);
			if (byte == '\r' || byte == '\n') {
				buffer[myindex] = '\0';
				processCommand(commandMap, buffer);
				myindex = 0;
			}else if (myindex < BUFFER_SIZE - 1) {
				buffer[myindex++] = byte;
			}
		}
    }
}

