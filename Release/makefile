################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/GLOBAL_INT/subdir.mk
-include MCAL/EXT_INT/subdir.mk
-include MCAL/EEPROM/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/SOLENOID/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/BUZZER/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
test2_final_project.lss \

FLASH_IMAGE += \
test2_final_project.hex \

EEPROM_IMAGE += \
test2_final_project.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: test2_final_project.elf secondary-outputs

# Tool invocations
test2_final_project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,test2_final_project.map -mmcu=atmega32 -o "test2_final_project.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

test2_final_project.lss: test2_final_project.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S test2_final_project.elf  >"test2_final_project.lss"
	@echo 'Finished building: $@'
	@echo ' '

test2_final_project.hex: test2_final_project.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex test2_final_project.elf  "test2_final_project.hex"
	@echo 'Finished building: $@'
	@echo ' '

test2_final_project.eep: test2_final_project.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex test2_final_project.elf  "test2_final_project.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: test2_final_project.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 test2_final_project.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) test2_final_project.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
