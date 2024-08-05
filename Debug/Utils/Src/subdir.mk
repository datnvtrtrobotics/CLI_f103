################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utils/Src/circular_bf.c \
../Utils/Src/process.c 

OBJS += \
./Utils/Src/circular_bf.o \
./Utils/Src/process.o 

C_DEPS += \
./Utils/Src/circular_bf.d \
./Utils/Src/process.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/Src/%.o Utils/Src/%.su Utils/Src/%.cyclo: ../Utils/Src/%.c Utils/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/App" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Drvs/Src" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils/Inc" -I"/home/tdat/STM32CubeIDE/workspace_1.15.1/CLI_103/Utils/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Utils-2f-Src

clean-Utils-2f-Src:
	-$(RM) ./Utils/Src/circular_bf.cyclo ./Utils/Src/circular_bf.d ./Utils/Src/circular_bf.o ./Utils/Src/circular_bf.su ./Utils/Src/process.cyclo ./Utils/Src/process.d ./Utils/Src/process.o ./Utils/Src/process.su

.PHONY: clean-Utils-2f-Src

