################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/keyboard/layout.c 

OBJS += \
./src/keyboard/layout.o 

C_DEPS += \
./src/keyboard/layout.d 


# Each subdirectory must supply rules for building sources it contributes
src/keyboard/layout.o: ../src/keyboard/layout.c src/keyboard/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/keyboard/layout.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


