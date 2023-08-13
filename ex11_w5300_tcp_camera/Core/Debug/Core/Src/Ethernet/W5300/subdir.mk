################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Ethernet/W5300/w5300.c 

OBJS += \
./Core/Src/Ethernet/W5300/w5300.o 

C_DEPS += \
./Core/Src/Ethernet/W5300/w5300.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Ethernet/W5300/%.o Core/Src/Ethernet/W5300/%.su: ../Core/Src/Ethernet/W5300/%.c Core/Src/Ethernet/W5300/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/src/Ethernet -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Ethernet-2f-W5300

clean-Core-2f-Src-2f-Ethernet-2f-W5300:
	-$(RM) ./Core/Src/Ethernet/W5300/w5300.d ./Core/Src/Ethernet/W5300/w5300.o ./Core/Src/Ethernet/W5300/w5300.su

.PHONY: clean-Core-2f-Src-2f-Ethernet-2f-W5300

