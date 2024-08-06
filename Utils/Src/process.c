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
        	char *token = strtok(NULL, " ");
			count = 0;
			while (token != NULL) {
				uint8_t pin = atoi(token);
				if (pin >= MIN_PINLED && pin <= MAX_PINLED) {
					if (count < MAX_COUNT) {
						pins[count] = pin;
					}
					count++;
				} else {
					UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA4, PA5, PA6, PA7, and PA8 are allowed.");
				}
				token = strtok(NULL, " ");
			}
			if (count > MAX_COUNT) {
				UART_SendString(&uart1.huart, "\r\nError: Too many arguments.");
			}
        	mapping->handler(strtok(NULL, ""));	//strtok(NULL, "" chính là phần còn lại sau khi tách lệnh, phần này là phần đối số
        	prompt();
            return;
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

