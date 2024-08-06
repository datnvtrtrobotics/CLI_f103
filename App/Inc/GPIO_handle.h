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
extern int count;
extern uint8_t pins[3];
extern ADC_HandleTypeDef hadc1;

void handleLedOnCommand(char *args);
void handleLedOffCommand(char *args);
void handleLedBlinkCommand(char *args);
void handleAdcGetCommand(char *args);
void handleInfoCommand(char *args);
void handleInvalidCommand(char *args);

#endif // GPIO_HANDLE_H
