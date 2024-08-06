/*
 * circular_bf.h
 *
 *  Created on: Jul 30, 2024
 *      Author: tdat
 */
#ifndef CIRCULAR_BF_H
#define CIRCULAR_BF_H
#include <stdint.h>

#define BUFFER_SIZE 256
typedef struct {
	uint8_t buffer[BUFFER_SIZE];
	volatile uint16_t head;
	volatile uint16_t tail;
} CircularBuffer;
extern CircularBuffer rxBuffer;

int CircularBuffer_Write(CircularBuffer *cb, uint8_t data);
int CircularBuffer_Read(CircularBuffer *cb, uint8_t *data);

#endif // CIRCULAR_BF_H

