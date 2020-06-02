################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include user/subdir.mk
-include sys/subdir.mk
-include misis/subdir.mk
-include fwlib/src/subdir.mk
-include Startup/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
stm32f4-mk.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
stm32f4-mk.list \

OBJCOPY_BIN += \
stm32f4-mk.bin \


# All Target
all: stm32f4-mk.elf secondary-outputs

# Tool invocations
stm32f4-mk.elf: $(OBJS) $(USER_OBJS) /home/share/samba/tuya/my_prj/stm32f4-prj/STM32CubeIDE/STM32F407ZGTX_FLASH.ld
	arm-none-eabi-gcc -o "stm32f4-mk.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/share/samba/tuya/my_prj/stm32f4-prj/STM32CubeIDE/STM32F407ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="stm32f4-mk.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

stm32f4-mk.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "stm32f4-mk.list"
	@echo 'Finished building: $@'
	@echo ' '

stm32f4-mk.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "stm32f4-mk.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
