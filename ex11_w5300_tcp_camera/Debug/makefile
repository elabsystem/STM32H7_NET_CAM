################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/Ethernet/W5300/subdir.mk
-include Core/Src/Ethernet/subdir.mk
-include Core/Src/subdir.mk
-include Core/Debug/Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Debug/Core/Startup/subdir.mk
-include Core/Debug/Core/Src/Ethernet/W5300/subdir.mk
-include Core/Debug/Core/Src/Ethernet/subdir.mk
-include Core/Debug/Core/Src/subdir.mk
-include Core/Debug/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ex11_w5300_tcp_camera
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ex11_w5300_tcp_camera.elf \

MAP_FILES += \
ex11_w5300_tcp_camera.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ex11_w5300_tcp_camera.list \

OBJCOPY_HEX += \
ex11_w5300_tcp_camera.hex \


# All Target
all: main-build

# Main-build Target
main-build: ex11_w5300_tcp_camera.elf secondary-outputs

# Tool invocations
ex11_w5300_tcp_camera.elf ex11_w5300_tcp_camera.map: $(OBJS) $(USER_OBJS) D:\WORK\ARM\stm32h7\STM32H7_RP_master\ex11_w5300_tcp_camera\STM32H743IITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ex11_w5300_tcp_camera.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\WORK\ARM\stm32h7\STM32H7_RP_master\ex11_w5300_tcp_camera\STM32H743IITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ex11_w5300_tcp_camera.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ex11_w5300_tcp_camera.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ex11_w5300_tcp_camera.list"
	@echo 'Finished building: $@'
	@echo ' '

ex11_w5300_tcp_camera.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "ex11_w5300_tcp_camera.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout ex11_w5300_tcp_camera.elf ex11_w5300_tcp_camera.hex ex11_w5300_tcp_camera.list ex11_w5300_tcp_camera.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
