################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EPD_Test.c \
../src/ImageData.c \
../src/ble.c \
../src/ble_utility.c \
../src/gpio.c \
../src/i2c.c \
../src/irq.c \
../src/llfifo.c \
../src/log.c \
../src/oscillator.c \
../src/rtcc.c \
../src/scheduler.c \
../src/spi.c \
../src/timer.c \
../src/ws2812.c 

OBJS += \
./src/EPD_Test.o \
./src/ImageData.o \
./src/ble.o \
./src/ble_utility.o \
./src/gpio.o \
./src/i2c.o \
./src/irq.o \
./src/llfifo.o \
./src/log.o \
./src/oscillator.o \
./src/rtcc.o \
./src/scheduler.o \
./src/spi.o \
./src/timer.o \
./src/ws2812.o 

C_DEPS += \
./src/EPD_Test.d \
./src/ImageData.d \
./src/ble.d \
./src/ble_utility.d \
./src/gpio.d \
./src/i2c.d \
./src/irq.d \
./src/llfifo.d \
./src/log.d \
./src/oscillator.d \
./src/rtcc.d \
./src/scheduler.d \
./src/spi.d \
./src/timer.d \
./src/ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
src/EPD_Test.o: ../src/EPD_Test.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/EPD_Test.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ImageData.o: ../src/ImageData.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/ImageData.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ble.o: ../src/ble.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/ble.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ble_utility.o: ../src/ble_utility.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/ble_utility.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gpio.o: ../src/gpio.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/i2c.o: ../src/i2c.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/i2c.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/irq.o: ../src/irq.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/irq.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/llfifo.o: ../src/llfifo.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/llfifo.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/log.o: ../src/log.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/log.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/oscillator.o: ../src/oscillator.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/oscillator.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/rtcc.o: ../src/rtcc.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/rtcc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/scheduler.o: ../src/scheduler.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/scheduler.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/spi.o: ../src/spi.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/spi.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/timer.o: ../src/timer.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/timer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ws2812.o: ../src/ws2812.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' -O3 -Wall -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/ws2812.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


