
#include "GPIO_handle.h"
#include "process.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

int count = 0;
uint8_t pins[3];
char msg[50];
char response[100];
uint32_t previous_time = 0;

void startBlinking(uint8_t *pins, int count) {
	while(Setstop){
		if((HAL_GetTick()- previous_time) >200){
			for (int i = 0; i < count; i++) {
				HAL_GPIO_TogglePin(GPIOA, 1 << pins[i]);
			}
			previous_time = HAL_GetTick();
		}
	}
	for (int i = 0; i < count; i++) {
		HAL_GPIO_WritePin(GPIOA, 1 << pins[i], GPIO_PIN_RESET);
	}
}
void handleLedOnCommand(char *args) {
	for (int i = 0; i < count; i++) {
		HAL_GPIO_WritePin(GPIOA, 1 << pins[i], GPIO_PIN_SET);
	}
}

void handleLedOffCommand(char *args) {
	for (int i = 0; i < count; i++) {
		HAL_GPIO_WritePin(GPIOA, 1 << pins[i], GPIO_PIN_RESET);
	}
}
void handleLedBlinkCommand(char *args) {
	Setstop = 1;
	UART_SendString(&uart1.huart, "\r\n");
	startBlinking(pins, count);
}

void handleAdcGetCommand(char *args) {
    ADC_ChannelConfTypeDef sConfig = {0};
    for(int i; i< count; i++){
		if (pins[i]==0||pins[i] ==1){
			sConfig.Channel = (pins[i] == 0) ? ADC_CHANNEL_0 : ADC_CHANNEL_1;
			sConfig.Rank = ADC_REGULAR_RANK_1;
			sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

			if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
				UART_SendString(&uart1.huart, "\r\nError: Failed to configure ADC channel.");
				return;
			}
			Setstop = 1;
			while(Setstop){
				if((HAL_GetTick()- previous_time) >1000){
					HAL_ADC_Start(&hadc1);
					HAL_ADC_PollForConversion(&hadc1, 100);
					uint32_t value = HAL_ADC_GetValue(&hadc1);

					snprintf(msg, sizeof(msg), "\r\nADC Value (PA%d): %lu", pins[i], value);
					HAL_UART_Transmit(&uart1.huart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
					previous_time = HAL_GetTick();
				}
			}
		} else {
			UART_SendString(&uart1.huart, "\r\nError: Invalid pin. Only PA0 and PA1 are allowed.");
		}
    }
}
void handleInfoCommand(char *args) {
	if (args != NULL) {
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

