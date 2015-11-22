################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/ft5336/ft5336.c 

OBJS += \
./Utilities/Components/ft5336/ft5336.o 

C_DEPS += \
./Utilities/Components/ft5336/ft5336.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/ft5336/%.o: ../Utilities/Components/ft5336/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746G_DISCO -DSTM32F746NGHx -DSTM32F7 -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/aesca/workspace/Blink/inc" -I"C:/Users/aesca/workspace/Blink/CMSIS/core" -I"C:/Users/aesca/workspace/Blink/CMSIS/device" -I"C:/Users/aesca/workspace/Blink/HAL_Driver/Inc/Legacy" -I"C:/Users/aesca/workspace/Blink/HAL_Driver/Inc" -I"C:/Users/aesca/workspace/Blink/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/aesca/workspace/Blink/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/aesca/workspace/Blink/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/ampire480272" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/ampire640480" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/Common" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/exc7200" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/ft5336" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/mfxstm32l152" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/n25q128a" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/n25q512a" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/ov9655" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/rk043fn48h" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/s5k5cag" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/stmpe811" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/ts3510" -I"C:/Users/aesca/workspace/Blink/Utilities/Components/wm8994" -I"C:/Users/aesca/workspace/Blink/Utilities/Fonts" -I"C:/Users/aesca/workspace/Blink/Utilities/Log" -I"C:/Users/aesca/workspace/Blink/Utilities" -I"C:/Users/aesca/workspace/Blink/Utilities/STM32746G-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


