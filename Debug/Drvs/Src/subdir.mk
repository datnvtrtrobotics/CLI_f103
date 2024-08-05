################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drvs/Src/uart.c 

OBJS += \
./Drvs/Src/uart.o 

C_DEPS += \
./Drvs/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drvs/Src/%.o Drvs/Src/%.su Drvs/Src/%.cyclo: ../Drvs/Src/%.c Drvs/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/App" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs/Src" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drvs-2f-Src

clean-Drvs-2f-Src:
	-$(RM) ./Drvs/Src/uart.cyclo ./Drvs/Src/uart.d ./Drvs/Src/uart.o ./Drvs/Src/uart.su

.PHONY: clean-Drvs-2f-Src

