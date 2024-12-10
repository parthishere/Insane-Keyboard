################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/GUI/GUI_Paint.c 

OBJS += \
./src/GUI/GUI_Paint.o 

C_DEPS += \
./src/GUI/GUI_Paint.d 


# Each subdirectory must supply rules for building sources it contributes
src/GUI/GUI_Paint.o: ../src/GUI/GUI_Paint.c src/GUI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/GUI/GUI_Paint.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


