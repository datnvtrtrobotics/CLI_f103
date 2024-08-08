/*
 * GPIO_handle.h
 *
 *  Created on: Aug 6, 2024
 *      Author: tdat
 */


#ifndef GPIO_HANDLE_H
#define GPIO_HANDLE_H
#include "stm32f1xx_hal.h"

extern volatile uint8_t Setstop;
extern ADC_HandleTypeDef hadc1;

void handleLedOnCommand(uint8_t *argvalue, uint8_t argcount);
void handleLedOffCommand(uint8_t *argvalue, uint8_t argcount);
void handleLedBlinkCommand(uint8_t *argvalue, uint8_t argcount);
void handleAdcGetCommand(uint8_t *argvalue, uint8_t argcount);
void handleInfoCommand(uint8_t *argvalue, uint8_t argcount);
void handleInvalidCommand(uint8_t *argvalue, uint8_t argcount);

#endif // GPIO_HANDLE_H
