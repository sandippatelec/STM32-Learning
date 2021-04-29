################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F2xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
UART4_RxDMA_Intr.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
UART4_RxDMA_Intr.list \

OBJCOPY_BIN += \
UART4_RxDMA_Intr.bin \


# All Target
all: UART4_RxDMA_Intr.elf secondary-outputs

# Tool invocations
UART4_RxDMA_Intr.elf: $(OBJS) $(USER_OBJS) D:\Firmware-Local\STM\UART4_RxDMA_Intr\STM32F207ZGTX_FLASH.ld
	arm-none-eabi-gcc -o "UART4_RxDMA_Intr.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Firmware-Local\STM\UART4_RxDMA_Intr\STM32F207ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="UART4_RxDMA_Intr.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

UART4_RxDMA_Intr.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "UART4_RxDMA_Intr.list"
	@echo 'Finished building: $@'
	@echo ' '

UART4_RxDMA_Intr.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "UART4_RxDMA_Intr.bin"
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
