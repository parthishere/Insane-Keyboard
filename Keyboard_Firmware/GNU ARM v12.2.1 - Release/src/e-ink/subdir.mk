################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/e-ink/EPD_1in54_V2.c 

OBJS += \
./src/e-ink/EPD_1in54_V2.o 

C_DEPS += \
./src/e-ink/EPD_1in54_V2.d 


# Each subdirectory must supply rules for building sources it contributes
src/e-ink/EPD_1in54_V2.o: ../src/e-ink/EPD_1in54_V2.c src/e-ink/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -Os -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/e-ink/EPD_1in54_V2.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


