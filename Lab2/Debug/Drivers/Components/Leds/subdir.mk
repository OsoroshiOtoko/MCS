################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/Leds/leds.c 

OBJS += \
./Drivers/Components/Leds/leds.o 

C_DEPS += \
./Drivers/Components/Leds/leds.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/Leds/%.o Drivers/Components/Leds/%.su Drivers/Components/Leds/%.cyclo: ../Drivers/Components/Leds/%.c Drivers/Components/Leds/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Drivers/Components/Leds" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-Leds

clean-Drivers-2f-Components-2f-Leds:
	-$(RM) ./Drivers/Components/Leds/leds.cyclo ./Drivers/Components/Leds/leds.d ./Drivers/Components/Leds/leds.o ./Drivers/Components/Leds/leds.su

.PHONY: clean-Drivers-2f-Components-2f-Leds
