/*
 * process.c
 *
 *  Created on: Jul 31, 2024
 *      Author: tdat
 */

#include "process.h"
#include "uart.h"
#include "GPIO_handle.h"
#include <stdlib.h>
#include <string.h>

#define PROMPT "#your-name:~ "
#define MAX_COUNT	3
#define MIN_PINLED	0
#define MAX_PINLED	8

int check_arg(char *args);
void processCommand(CommandMapping *ptr, char *cmd){
    char *token = strtok(cmd, " ");

    for (CommandMapping *mapping = ptr; mapping->command != NULL; mapping++) {
        if (strcmp(token, mapping->command) == 0) {
        	if (strcmp(token, "info") == 0){
        		handleInfoCommand(strtok(NULL, " "));
        		prompt();
        	}else{
        		char *token = strtok(NULL, " ");
        		uint8_t argvalue[MAX_COUNT] = {0};
        		uint8_t argcount = 0;
            	while (token != NULL) {
				uint8_t pin = atoi(token);
				if (pin >= MIN_PINLED && pin <= MAX_PINLED) {
					if (argcount < MAX_COUNT) {
						argvalue[argcount] = pin;
					}
					argcount++;
				} else {
					UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA4, PA5, PA6, PA7, and PA8 are allowed.");
				}
				token = strtok(NULL, " ");
			}
			if (argcount > MAX_COUNT) {
				UART_SendString(&uart1.huart, "\r\nError: Too many arguments.");
			}
        	mapping->handler(argvalue, argcount);
        	prompt();
        	return;
        	}
        }
    }
    handleInvalidCommand(NULL);
}
void checkCtrlC(uint8_t data){
	if (data == 0x03){
		UART_SendString(&uart1.huart, "^C\n\r"PROMPT);
	}
}
void prompt(){
	UART_SendString(&uart1.huart, "\n\r"PROMPT);
}

