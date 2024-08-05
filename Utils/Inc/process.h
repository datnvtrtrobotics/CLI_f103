/*
 * process.h
 *
 *  Created on: Jul 31, 2024
 *      Author: tdat
 */


#ifndef PROCESS_H
#define PROCESS_H

#include "uart.h"
#include <stdlib.h>

typedef struct {
    char *command;
    void (*handler)(char *);
} CommandMapping;

extern CommandMapping commandMap[];

extern volatile uint8_t stopBlink;
extern ADC_HandleTypeDef hadc1;
#define PROMPT "#your-name:~ "

void processCommand(char *cmd);
void prompt(void);
void handleLedOnCommand(char *args);
void handleLedOffCommand(char *args);
void handleLedBlinkCommand(char *args);
void handleAdcGetCommand(char *args);
void handleInfoCommand(char *args);
void handleInvalidCommand(char *args);

#endif /* PROCESS_H */
