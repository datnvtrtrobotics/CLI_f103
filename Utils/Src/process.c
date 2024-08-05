/*
 * process.c
 *
 *  Created on: Jul 31, 2024
 *      Author: tdat
 */

#include "process.h"

volatile uint8_t stopBlink = 0;
uint8_t stopCmd;
CommandMapping commandMap[] = {
    {"led-on", handleLedOnCommand},
    {"led-off", handleLedOffCommand},
    {"led-blink", handleLedBlinkCommand},
    {"adc-get", handleAdcGetCommand},
    {"info", handleInfoCommand},
    {NULL, handleInvalidCommand}
};

void processCommand(char *cmd)
{
    char *token = strtok(cmd, " ");
    for (int i = 0; commandMap[i].command != NULL; i++) {
        if (strcmp(token, commandMap[i].command) == 0) {
            commandMap[i].handler(strtok(NULL, ""));	//strtok(NULL, "" chính là phần còn lại sau khi tách lệnh, phần này là phần đối số
            prompt();
            return;
        }
    }
    handleInvalidCommand(NULL);
}

void handleLedOnCommand(char *args) {
	char *token = strtok(args, " ");
	int count = 0;
	while (token != NULL) {
		uint8_t pin = atoi(token);
		if (pin >= 4 && pin <= 8) {
			HAL_GPIO_WritePin(GPIOA, 1 << pin, GPIO_PIN_SET);
			count++;
		}else {
			UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA4, PA5, PA6, PA7, and PA8 are allowed.");
			return;
		}
		if (count > 3){
			UART_SendString(&uart1.huart, "\r\nError: Too many arguments");
			return;
		}
		token = strtok(NULL, " ");
	}
}

void handleLedOffCommand(char *args) {
	char *token = strtok(args, " ");
	int count = 0;

	while (token != NULL) {
		uint8_t pin = atoi(token);
		if (pin >= 4 && pin <= 8) {
			HAL_GPIO_WritePin(GPIOA, 1 << pin, GPIO_PIN_RESET);
		} else {
			UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA4, PA5, PA6, PA7, and PA8 are allowed.");
			return;
		}
		if (count > 3){
			UART_SendString(&uart1.huart, "\r\nError: Too many arguments");
			return;
		}
		token = strtok(NULL, " ");
	}
}
void handleLedBlinkCommand(char *args) {
	uint8_t pins[3];  // Mảng để lưu trữ các giá trị pin
	int count = 0;
	char *token = strtok(args, " ");
	while (token != NULL) {
		uint8_t pin = atoi(token);
		if (pin >= 4 && pin <= 8) {
			pins[count++] = pin;
		} else {
			UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA4, PA5, PA6, PA7, and PA8 are allowed.");
			return;
		}
		if (count > 3) {
			UART_SendString(&uart1.huart, "\r\nError: Too many arguments");
			return;
		}
		token = strtok(NULL, " ");
	}
	stopBlink = 1;
	UART_SendString(&uart1.huart, "\r\n");
	startBlinking(pins, count);
}
void startBlinking(uint8_t *pins, int count) {
	while (stopBlink) {
		for (int i = 0; i < count; i++) {
			HAL_GPIO_WritePin(GPIOA, 1 << pins[i], GPIO_PIN_SET);
		}
		HAL_Delay(200);
		for (int i = 0; i < count; i++) {
			HAL_GPIO_WritePin(GPIOA, 1 << pins[i], GPIO_PIN_RESET);
		}
		HAL_Delay(200);
	}
}
void handleAdcGetCommand(char *args) {
	uint8_t pin = atoi(args);

    ADC_ChannelConfTypeDef sConfig = {0};
    if (pin == 0 || pin == 1) {
        // Cấu hình kênh ADC tương ứng với chân PA0 hoặc PA1
        sConfig.Channel = (pin == 0) ? ADC_CHANNEL_0 : ADC_CHANNEL_1;
        sConfig.Rank = ADC_REGULAR_RANK_1;
        sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

        if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
            UART_SendString(&uart1.huart, "\r\nError: Failed to configure ADC channel.");
            return;
        }
        stopBlink = 1;
        while (stopBlink) {
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 100);
            uint32_t value = HAL_ADC_GetValue(&hadc1);
            HAL_ADC_Stop(&hadc1);

            char msg[50];
            sprintf(msg, "\r\nADC Value (PA%d): %lu", pin, value);
            HAL_UART_Transmit(&uart1.huart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

            HAL_Delay(1000);
        }
    } else {
        UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA0 and PA1 are allowed.");
    }
}

void handleInfoCommand(char *args) {
	if (args != NULL) {
		char response[100];
		snprintf(response, sizeof(response), "\r\nSample text: %s", args);
		HAL_UART_Transmit(&uart1.huart, (uint8_t*)response, strlen(response), HAL_MAX_DELAY);
	} else {
		HAL_UART_Transmit(&uart1.huart, (uint8_t*)"Sample text: \r\n", 15, HAL_MAX_DELAY);
	}
}
void handleInvalidCommand(char *args) {
    UART_SendString(&uart1.huart, "\n\rInvalid Command");
    prompt();

}

void prompt(){
	UART_SendString(&uart1.huart, "\n\r");
	UART_SendString(&uart1.huart, PROMPT);
}

