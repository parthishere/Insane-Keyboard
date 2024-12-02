################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/keyboard/subdir.mk
-include src/e-ink/subdir.mk
-include src/GUI/subdir.mk
-include src/Fonts/subdir.mk
-include src/subdir.mk
-include build/debug/sdk/util/third_party/mbedtls/library/subdir.mk
-include build/debug/sdk/util/silicon_labs/silabs_core/memory_manager/subdir.mk
-include build/debug/sdk/protocol/bluetooth/src/subdir.mk
-include build/debug/sdk/protocol/bluetooth/bgcommon/src/subdir.mk
-include build/debug/sdk/platform/service/udelay/src/subdir.mk
-include build/debug/sdk/platform/service/system/src/subdir.mk
-include build/debug/sdk/platform/service/sleeptimer/src/subdir.mk
-include build/debug/sdk/platform/service/power_manager/src/subdir.mk
-include build/debug/sdk/platform/service/iostream/src/subdir.mk
-include build/debug/sdk/platform/service/device_init/src/subdir.mk
-include build/debug/sdk/platform/security/sl_component/sl_psa_driver/src/subdir.mk
-include build/debug/sdk/platform/security/sl_component/sl_protocol_crypto/src/subdir.mk
-include build/debug/sdk/platform/security/sl_component/sl_mbedtls_support/src/subdir.mk
-include build/debug/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/subdir.mk
-include build/debug/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/subdir.mk
-include build/debug/sdk/platform/radio/rail_lib/plugin/pa-conversions/subdir.mk
-include build/debug/sdk/platform/emlib/src/subdir.mk
-include build/debug/sdk/platform/emdrv/spidrv/src/subdir.mk
-include build/debug/sdk/platform/emdrv/dmadrv/src/subdir.mk
-include build/debug/sdk/platform/driver/i2cspm/src/subdir.mk
-include build/debug/sdk/platform/driver/debug/src/subdir.mk
-include build/debug/sdk/platform/common/toolchain/src/subdir.mk
-include build/debug/sdk/platform/common/src/subdir.mk
-include build/debug/sdk/platform/bootloader/app_properties/subdir.mk
-include build/debug/sdk/platform/bootloader/api/subdir.mk
-include build/debug/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/subdir.mk
-include build/debug/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/subdir.mk
-include build/debug/sdk/hardware/driver/configuration_over_swo/src/subdir.mk
-include build/debug/sdk/hardware/board/src/subdir.mk
-include build/debug/sdk/app/common/util/app_timer/subdir.mk
-include build/debug/sdk/app/common/util/app_log/subdir.mk
-include build/debug/sdk/app/bluetooth/common/in_place_ota_dfu/subdir.mk
-include build/debug/project/autogen/subdir.mk
-include build/debug/project/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Keyboard_Firmware
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: Keyboard_Firmware.axf

# Tool invocations
Keyboard_Firmware.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -T "Keyboard_Firmware.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="Keyboard_Firmware.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o Keyboard_Firmware.axf "./src/EPD_Test.o" "./src/ImageData.o" "./src/ble.o" "./src/ble_utility.o" "./src/gpio.o" "./src/i2c.o" "./src/irq.o" "./src/llfifo.o" "./src/log.o" "./src/oscillator.o" "./src/rtcc.o" "./src/scheduler.o" "./src/spi.o" "./src/timer.o" "./src/ws2812.o" "./src/Fonts/font12.o" "./src/Fonts/font12CN.o" "./src/Fonts/font16.o" "./src/Fonts/font20.o" "./src/Fonts/font24.o" "./src/Fonts/font24CN.o" "./src/Fonts/font8.o" "./src/GUI/GUI_Paint.o" "./src/e-ink/EPD_1in54_V2.o" "./src/keyboard/layout.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: Keyboard_Firmware.out'
	arm-none-eabi-objcopy "Keyboard_Firmware.axf" "Keyboard_Firmware.out"
	@echo ' '

	@echo 'Building hex file: Keyboard_Firmware.hex'
	arm-none-eabi-objcopy -O ihex "Keyboard_Firmware.axf" "Keyboard_Firmware.hex"
	@echo ' '

	@echo 'Building bin file: Keyboard_Firmware.bin'
	arm-none-eabi-objcopy -O binary "Keyboard_Firmware.axf" "Keyboard_Firmware.bin"
	@echo ' '

	@echo 'Building s37 file: Keyboard_Firmware.s37'
	arm-none-eabi-objcopy -O srec "Keyboard_Firmware.axf" "Keyboard_Firmware.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "Keyboard_Firmware.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(CC_DEPS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C++_DEPS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_UPPER_DEPS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(CXX_DEPS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(CPP_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) Keyboard_Firmware.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
