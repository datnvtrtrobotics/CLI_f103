/*
 * circular_bf.c
 *
 *  Created on: Jul 30, 2024
 *      Author: tdat
 */

#include "circular_bf.h"

uint16_t myindex = 0;
char buffer[BUFFER_SIZE];
CircularBuffer rxBuffer = { {0}, 0, 0 };

void CircularBuffer_Write(CircularBuffer *cb, uint8_t data) {
    uint16_t next = (cb->head + 1) % BUFFER_SIZE;
    // bo qua du lieu
	if (next != cb->tail) {
		cb->buffer[cb->head] = data;
		cb->head = next;

	}
}
int CircularBuffer_Read(CircularBuffer *cb, uint8_t *data) {
    if (cb->head == cb->tail) {
        return 0; // Buffer empty
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    return 1; // Success
}
void CheckAndPrintReceivedData(void) {
	uint8_t byte;

	while(CircularBuffer_Read(&rxBuffer, &byte)) {
		HAL_UART_Transmit(&uart1.huart, &byte, 1, HAL_MAX_DELAY);
		checkCtrlC(byte);
		if (byte == '\r' || byte == '\n') {
			buffer[myindex] = '\0';
			processCommand(buffer);

			myindex = 0;
		}else if (myindex < BUFFER_SIZE - 1) {
			buffer[myindex++] = byte;
		}
	}
}

void checkCtrlC(uint8_t data){
	if (data == 0x03){
		UART_SendString(&uart1.huart, "^C\n\r");
		UART_SendString(&uart1.huart, PROMPT);
	}
}


