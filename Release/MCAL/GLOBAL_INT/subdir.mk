################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GLOBAL_INT/GLOB_INT_Program.c 

OBJS += \
./MCAL/GLOBAL_INT/GLOB_INT_Program.o 

C_DEPS += \
./MCAL/GLOBAL_INT/GLOB_INT_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GLOBAL_INT/%.o: ../MCAL/GLOBAL_INT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


