################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Fonts/font12.c \
../src/Fonts/font12CN.c \
../src/Fonts/font16.c \
../src/Fonts/font20.c \
../src/Fonts/font24.c \
../src/Fonts/font24CN.c \
../src/Fonts/font8.c 

OBJS += \
./src/Fonts/font12.o \
./src/Fonts/font12CN.o \
./src/Fonts/font16.o \
./src/Fonts/font20.o \
./src/Fonts/font24.o \
./src/Fonts/font24CN.o \
./src/Fonts/font8.o 

C_DEPS += \
./src/Fonts/font12.d \
./src/Fonts/font12CN.d \
./src/Fonts/font16.d \
./src/Fonts/font20.d \
./src/Fonts/font24.d \
./src/Fonts/font24CN.d \
./src/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
src/Fonts/font12.o: ../src/Fonts/font12.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font12.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Fonts/font12CN.o: ../src/Fonts/font12CN.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font12CN.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Fonts/font16.o: ../src/Fonts/font16.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font16.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Fonts/font20.o: ../src/Fonts/font20.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font20.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Fonts/font24.o: ../src/Fonts/font24.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font24.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Fonts/font24CN.o: ../src/Fonts/font24CN.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font24CN.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Fonts/font8.o: ../src/Fonts/font8.c src/Fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/Fonts/font8.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


