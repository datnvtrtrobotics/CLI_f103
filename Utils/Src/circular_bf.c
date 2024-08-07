/*
 * circular_bf.c
 *
 *  Created on: Jul 30, 2024
 *      Author: tdat
 */

#include "circular_bf.h"

int CircularBuffer_Write(CircularBuffer *cb, uint8_t data) {
    uint16_t next = (cb->head + 1) % BUFFER_SIZE;
    if (next == cb->tail) {
            return 0;
    } else {
            cb->buffer[cb->head] = data;
            cb->head = next;
            return 1;
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


