################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/CLI.c \
../App/Src/GPIO_handle.c 

OBJS += \
./App/Src/CLI.o \
./App/Src/GPIO_handle.o 

C_DEPS += \
./App/Src/CLI.d \
./App/Src/GPIO_handle.d 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su App/Src/%.cyclo: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/App" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs/Src" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils/Src" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/App/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/App/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/CLI.cyclo ./App/Src/CLI.d ./App/Src/CLI.o ./App/Src/CLI.su ./App/Src/GPIO_handle.cyclo ./App/Src/GPIO_handle.d ./App/Src/GPIO_handle.o ./App/Src/GPIO_handle.su

.PHONY: clean-App-2f-Src

