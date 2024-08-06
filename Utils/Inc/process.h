/*
 * process.h
 *
 *  Created on: Jul 31, 2024
 *      Author: tdat
 */


#ifndef PROCESS_H
#define PROCESS_H
#include "stm32f1xx_hal.h"

typedef struct {
    char *command;
    void (*handler)(char *);
} CommandMapping;

void processCommand(CommandMapping *ptr,char *cmd);
void checkCtrlC(uint8_t data);
void prompt();
#endif /* PROCESS_H */
