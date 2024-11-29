####################################################################
# Automatically-generated file. Do not edit!                       #
# Makefile Version 15                                              #
####################################################################

BASE_SDK_PATH = /home/parth/SimplicityStudio/SDKs/gecko_sdk
UNAME:=$(shell $(POSIX_TOOL_PATH)uname -s | $(POSIX_TOOL_PATH)sed -e 's/^\(CYGWIN\).*/\1/' | $(POSIX_TOOL_PATH)sed -e 's/^\(MINGW\).*/\1/')
ifeq ($(UNAME),MINGW)
# Translate "C:/super" into "/C/super" for MinGW make.
SDK_PATH := /$(shell $(POSIX_TOOL_PATH)echo $(BASE_SDK_PATH) | sed s/://)
endif
SDK_PATH ?= $(BASE_SDK_PATH)
COPIED_SDK_PATH ?= gecko_sdk_4.4.4

# This uses the explicit build rules below
PROJECT_SOURCE_FILES =

C_SOURCE_FILES   += $(filter %.c, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cpp, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cc, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.s, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.S, $(PROJECT_SOURCE_FILES))
LIB_FILES        += $(filter %.a, $(PROJECT_SOURCE_FILES))

C_DEFS += \
 '-DDEBUG_EFM=1' \
 '-DEFR32BG13P632F512GM48=1' \
 '-DSL_APP_PROPERTIES=1' \
 '-DSL_BOARD_NAME="BRD4104A"' \
 '-DSL_BOARD_REV="A02"' \
 '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' \
 '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' \
 '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' \
 '-DHFXO_FREQ=38400000' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1' \
 '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' \
 '-DMBEDTLS_PSA_CRYPTO_CLIENT=1' \
 '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' \
 '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' \
 '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>'

ASM_DEFS += \
 '-DDEBUG_EFM=1' \
 '-DEFR32BG13P632F512GM48=1' \
 '-DSL_APP_PROPERTIES=1' \
 '-DSL_BOARD_NAME="BRD4104A"' \
 '-DSL_BOARD_REV="A02"' \
 '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' \
 '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' \
 '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' \
 '-DHFXO_FREQ=38400000' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1' \
 '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' \
 '-DMBEDTLS_PSA_CRYPTO_CLIENT=1' \
 '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' \
 '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' \
 '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>'

INCLUDES += \
 -Iautogen \
 -Iconfig \
 -Iconfig/btconf \
 -I. \
 -I$(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Include \
 -I$(SDK_PATH)/app/common/util/app_assert \
 -I$(SDK_PATH)/app/common/util/app_log \
 -I$(SDK_PATH)/app/common/util/app_timer \
 -I$(SDK_PATH)/protocol/bluetooth/inc \
 -I$(SDK_PATH)/platform/common/inc \
 -I$(SDK_PATH)/protocol/bluetooth/bgcommon/inc \
 -I$(SDK_PATH)/protocol/bluetooth/bgstack/ll/inc \
 -I$(SDK_PATH)/hardware/board/inc \
 -I$(SDK_PATH)/platform/bootloader \
 -I$(SDK_PATH)/platform/bootloader/api \
 -I$(SDK_PATH)/platform/CMSIS/Core/Include \
 -I$(SDK_PATH)/hardware/driver/configuration_over_swo/inc \
 -I$(SDK_PATH)/platform/driver/debug/inc \
 -I$(SDK_PATH)/platform/service/device_init/inc \
 -I$(SDK_PATH)/platform/emdrv/dmadrv/inc \
 -I$(SDK_PATH)/platform/emdrv/common/inc \
 -I$(SDK_PATH)/platform/emlib/inc \
 -I$(SDK_PATH)/app/bluetooth/common/gatt_service_device_information \
 -I$(SDK_PATH)/platform/driver/i2cspm/inc \
 -I$(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu \
 -I$(SDK_PATH)/platform/service/iostream/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/config \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/config/preset \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/inc \
 -I$(SDK_PATH)/util/third_party/mbedtls/include \
 -I$(SDK_PATH)/util/third_party/mbedtls/library \
 -I$(SDK_PATH)/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart \
 -I$(SDK_PATH)/platform/service/power_manager/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_psa_driver/inc \
 -I$(SDK_PATH)/platform/radio/rail_lib/common \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/ble \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/ieee802154 \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/wmbus \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/zwave \
 -I$(SDK_PATH)/platform/radio/rail_lib/chip/efr32/efr32xg1x \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/sidewalk \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/efr32xg1x \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init \
 -I$(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager \
 -I$(SDK_PATH)/platform/common/toolchain/inc \
 -I$(SDK_PATH)/platform/service/system/inc \
 -I$(SDK_PATH)/platform/service/sleeptimer/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src \
 -I$(SDK_PATH)/platform/emdrv/spidrv/inc \
 -I$(SDK_PATH)/platform/service/udelay/inc

GROUP_START =-Wl,--start-group
GROUP_END =-Wl,--end-group

PROJECT_LIBS = \
 -lgcc \
 -lc \
 -lm \
 -lnosys \
 $(SDK_PATH)/protocol/bluetooth/lib/EFR32XG13/GCC/binapploader.o \
 $(SDK_PATH)/protocol/bluetooth/bgcommon/lib/libbgcommon_efr32xg13_gcc_release.a \
 $(SDK_PATH)/protocol/bluetooth/bgstack/ll/lib/libbluetooth_controller_efr32xg13_gcc_release.a \
 $(SDK_PATH)/protocol/bluetooth/lib/libbluetooth_host_efr32xg13_gcc_release.a \
 $(SDK_PATH)/protocol/bluetooth/lib/EFR32XG13/GCC/libpsstore.a \
 $(SDK_PATH)/platform/radio/rail_lib/autogen/librail_release/librail_efr32xg13_gcc_release.a

LIBS += $(GROUP_START) $(PROJECT_LIBS) $(GROUP_END)

LIB_FILES += $(filter %.a, $(PROJECT_LIBS))

C_FLAGS += \
 -mcpu=cortex-m4 \
 -mthumb \
 -mfpu=fpv4-sp-d16 \
 -mfloat-abi=softfp \
 -std=c99 \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -imacros sl_gcc_preinclude.h \
 --specs=nano.specs \
 -g

CXX_FLAGS += \
 -mcpu=cortex-m4 \
 -mthumb \
 -mfpu=fpv4-sp-d16 \
 -mfloat-abi=softfp \
 -std=c++11 \
 -fno-rtti \
 -fno-exceptions \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -imacros sl_gcc_preinclude.h \
 --specs=nano.specs \
 -g

ASM_FLAGS += \
 -mcpu=cortex-m4 \
 -mthumb \
 -mfpu=fpv4-sp-d16 \
 -mfloat-abi=softfp \
 -imacros sl_gcc_preinclude.h \
 -x assembler-with-cpp

LD_FLAGS += \
 -mcpu=cortex-m4 \
 -mthumb \
 -mfpu=fpv4-sp-d16 \
 -mfloat-abi=softfp \
 -T"autogen/linkerfile.ld" \
 --specs=nano.specs \
 -Xlinker -Map=$(OUTPUT_DIR)/$(PROJECTNAME).map \
 -Wl,--gc-sections \
 -Wl,--no-warn-rwx-segments


####################################################################
# Pre/Post Build Rules                                             #
####################################################################
pre-build:
	# No pre-build defined

post-build: $(OUTPUT_DIR)/$(PROJECTNAME).out
	# No post-build defined

####################################################################
# SDK Build Rules                                                  #
####################################################################
$(OUTPUT_DIR)/sdk/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.o: $(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.o

$(OUTPUT_DIR)/sdk/app/common/util/app_log/app_log.o: $(SDK_PATH)/app/common/util/app_log/app_log.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/common/util/app_log/app_log.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/common/util/app_log/app_log.c
CDEPS += $(OUTPUT_DIR)/sdk/app/common/util/app_log/app_log.d
OBJS += $(OUTPUT_DIR)/sdk/app/common/util/app_log/app_log.o

$(OUTPUT_DIR)/sdk/app/common/util/app_timer/app_timer.o: $(SDK_PATH)/app/common/util/app_timer/app_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/common/util/app_timer/app_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/common/util/app_timer/app_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/app/common/util/app_timer/app_timer.d
OBJS += $(OUTPUT_DIR)/sdk/app/common/util/app_timer/app_timer.o

$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o: $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o

$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o: $(SDK_PATH)/hardware/board/src/sl_board_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/board/src/sl_board_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/board/src/sl_board_init.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o

$(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.o: $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.o

$(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o: $(SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o

$(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface.o: $(SDK_PATH)/platform/bootloader/api/btl_interface.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/bootloader/api/btl_interface.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/bootloader/api/btl_interface.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface.d
OBJS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface.o

$(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface_storage.o: $(SDK_PATH)/platform/bootloader/api/btl_interface_storage.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/bootloader/api/btl_interface_storage.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/bootloader/api/btl_interface_storage.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface_storage.d
OBJS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface_storage.o

$(OUTPUT_DIR)/sdk/platform/bootloader/app_properties/app_properties.o: $(SDK_PATH)/platform/bootloader/app_properties/app_properties.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/bootloader/app_properties/app_properties.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/bootloader/app_properties/app_properties.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/bootloader/app_properties/app_properties.d
OBJS += $(OUTPUT_DIR)/sdk/platform/bootloader/app_properties/app_properties.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.o: $(SDK_PATH)/platform/common/src/sl_assert.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_assert.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_assert.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.o: $(SDK_PATH)/platform/common/src/sl_slist.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_slist.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_slist.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_string.o: $(SDK_PATH)/platform/common/src/sl_string.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_string.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_string.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_string.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_string.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.o: $(SDK_PATH)/platform/common/src/sl_syscalls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_syscalls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_syscalls.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.o

$(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.o: $(SDK_PATH)/platform/common/toolchain/src/sl_memory.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/toolchain/src/sl_memory.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/toolchain/src/sl_memory.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/startup_efr32bg13p.o: $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Source/startup_efr32bg13p.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Source/startup_efr32bg13p.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Source/startup_efr32bg13p.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/startup_efr32bg13p.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/startup_efr32bg13p.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.o: $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG13P/Source/system_efr32bg13p.o

$(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.o: $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.o

$(OUTPUT_DIR)/sdk/platform/driver/i2cspm/src/sl_i2cspm.o: $(SDK_PATH)/platform/driver/i2cspm/src/sl_i2cspm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/i2cspm/src/sl_i2cspm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/i2cspm/src/sl_i2cspm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/i2cspm/src/sl_i2cspm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/i2cspm/src/sl_i2cspm.o

$(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.o: $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.o

$(OUTPUT_DIR)/sdk/platform/emdrv/spidrv/src/spidrv.o: $(SDK_PATH)/platform/emdrv/spidrv/src/spidrv.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/spidrv/src/spidrv.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/spidrv/src/spidrv.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/spidrv/src/spidrv.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/spidrv/src/spidrv.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_acmp.o: $(SDK_PATH)/platform/emlib/src/em_acmp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_acmp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_acmp.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_acmp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_acmp.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_adc.o: $(SDK_PATH)/platform/emlib/src/em_adc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_adc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_adc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_adc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_adc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o: $(SDK_PATH)/platform/emlib/src/em_cmu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_cmu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_cmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o: $(SDK_PATH)/platform/emlib/src/em_core.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_core.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_core.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_cryotimer.o: $(SDK_PATH)/platform/emlib/src/em_cryotimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_cryotimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_cryotimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cryotimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cryotimer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_crypto.o: $(SDK_PATH)/platform/emlib/src/em_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_crypto.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_csen.o: $(SDK_PATH)/platform/emlib/src/em_csen.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_csen.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_csen.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_csen.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_csen.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.o: $(SDK_PATH)/platform/emlib/src/em_dbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_dbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_dbg.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o: $(SDK_PATH)/platform/emlib/src/em_emu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_emu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_emu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o: $(SDK_PATH)/platform/emlib/src/em_gpcrc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_gpcrc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_gpcrc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o: $(SDK_PATH)/platform/emlib/src/em_gpio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_gpio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.o: $(SDK_PATH)/platform/emlib/src/em_i2c.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_i2c.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_i2c.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_idac.o: $(SDK_PATH)/platform/emlib/src/em_idac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_idac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_idac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_idac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_idac.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o: $(SDK_PATH)/platform/emlib/src/em_ldma.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_ldma.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_ldma.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_lesense.o: $(SDK_PATH)/platform/emlib/src/em_lesense.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_lesense.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_lesense.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_lesense.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_lesense.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.o: $(SDK_PATH)/platform/emlib/src/em_letimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_letimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_letimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_leuart.o: $(SDK_PATH)/platform/emlib/src/em_leuart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_leuart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_leuart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_leuart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_leuart.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.o: $(SDK_PATH)/platform/emlib/src/em_msc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_msc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_msc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_opamp.o: $(SDK_PATH)/platform/emlib/src/em_opamp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_opamp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_opamp.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_opamp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_opamp.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_pcnt.o: $(SDK_PATH)/platform/emlib/src/em_pcnt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_pcnt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_pcnt.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pcnt.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pcnt.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o: $(SDK_PATH)/platform/emlib/src/em_prs.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_prs.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_prs.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.o: $(SDK_PATH)/platform/emlib/src/em_rmu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_rmu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_rmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_rtcc.o: $(SDK_PATH)/platform/emlib/src/em_rtcc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_rtcc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_rtcc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rtcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rtcc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o: $(SDK_PATH)/platform/emlib/src/em_system.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_system.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_system.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o: $(SDK_PATH)/platform/emlib/src/em_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o: $(SDK_PATH)/platform/emlib/src/em_usart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_usart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_usart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_vdac.o: $(SDK_PATH)/platform/emlib/src/em_vdac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_vdac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_vdac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_vdac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_vdac.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.o: $(SDK_PATH)/platform/emlib/src/em_wdog.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_wdog.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_wdog.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/crypto_aes.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/crypto_aes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/crypto_aes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/crypto_aes.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/crypto_aes.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/crypto_aes.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/crypto_ecp.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/crypto_ecp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/crypto_ecp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/crypto_ecp.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/crypto_ecp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/crypto_ecp.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_crypto.o: $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_crypto.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/crypto_management.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/crypto_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/crypto_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/crypto_management.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/crypto_management.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/crypto_management.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_driver_trng.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_driver_trng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_driver_trng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_driver_trng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_driver_trng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_driver_trng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_aead.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_aead.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_aead.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_cipher.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_hash.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_hash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_hash.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_mac.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_mac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_crypto_transparent_driver_mac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s1.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s1.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s1.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s1.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s1.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s1.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s1.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s1.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s1.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s1.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s1.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s1.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s1.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s1.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s1.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s1.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s1.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s1.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s1.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s1.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s1.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s1.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s1.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s1.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_retarget_stdio.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_retarget_stdio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_retarget_stdio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_retarget_stdio.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_retarget_stdio.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_retarget_stdio.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_stdlib_config.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_stdlib_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_stdlib_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_stdlib_config.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_stdlib_config.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_stdlib_config.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_uart.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_uart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_uart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_uart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_uart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_uart.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_usart.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_usart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_usart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_usart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_usart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_usart.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s0_s1.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s0_s1.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s0_s1.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s0_s1.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s0_s1.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s0_s1.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o: $(SDK_PATH)/platform/service/system/src/sl_system_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/system/src/sl_system_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/system/src/sl_system_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.o: $(SDK_PATH)/platform/service/system/src/sl_system_process_action.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/system/src/sl_system_process_action.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/system/src/sl_system_process_action.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o: $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o: $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(ASMFLAGS) -c -o $@ $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
ASMDEPS_S += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/bgcommon/src/sl_bt_mbedtls_context.o: $(SDK_PATH)/protocol/bluetooth/bgcommon/src/sl_bt_mbedtls_context.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/bgcommon/src/sl_bt_mbedtls_context.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/bgcommon/src/sl_bt_mbedtls_context.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/bgcommon/src/sl_bt_mbedtls_context.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/bgcommon/src/sl_bt_mbedtls_context.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_apploader_util_s1.o: $(SDK_PATH)/protocol/bluetooth/src/sl_apploader_util_s1.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sl_apploader_util_s1.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sl_apploader_util_s1.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_apploader_util_s1.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_apploader_util_s1.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.o: $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_adv_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_adv_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_adv_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_adv_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_adv_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_adv_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.o

$(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/sl_malloc.o: $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/sl_malloc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/sl_malloc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/sl_malloc.c
CDEPS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/sl_malloc.d
OBJS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/sl_malloc.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/aes.o: $(SDK_PATH)/util/third_party/mbedtls/library/aes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/aes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/aes.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/aes.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/aes.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_core.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum_core.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum_core.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum_core.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_core.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_core.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod_raw.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod_raw.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod_raw.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod_raw.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod_raw.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod_raw.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.o: $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.o: $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cmac.o: $(SDK_PATH)/util/third_party/mbedtls/library/cmac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cmac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cmac.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cmac.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cmac.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.o: $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ctr_drbg.o: $(SDK_PATH)/util/third_party/mbedtls/library/ctr_drbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ctr_drbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ctr_drbg.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ctr_drbg.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ctr_drbg.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdh.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecdh.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecdh.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecdh.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdh.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdh.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecp.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves_new.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves_new.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves_new.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves_new.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves_new.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves_new.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy.o: $(SDK_PATH)/util/third_party/mbedtls/library/entropy.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/entropy.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/entropy.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy_poll.o: $(SDK_PATH)/util/third_party/mbedtls/library/entropy_poll.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/entropy_poll.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/entropy_poll.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy_poll.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy_poll.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/hmac_drbg.o: $(SDK_PATH)/util/third_party/mbedtls/library/hmac_drbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/hmac_drbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/hmac_drbg.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/hmac_drbg.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/hmac_drbg.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/md.o: $(SDK_PATH)/util/third_party/mbedtls/library/md.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/md.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/md.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/md.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/md.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.o: $(SDK_PATH)/util/third_party/mbedtls/library/platform.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/platform.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/platform.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.o: $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/sha256.o: $(SDK_PATH)/util/third_party/mbedtls/library/sha256.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/sha256.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/sha256.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/sha256.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/sha256.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.o: $(SDK_PATH)/util/third_party/mbedtls/library/threading.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/threading.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/threading.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.o

$(OUTPUT_DIR)/project/app.o: app.c
	@$(POSIX_TOOL_PATH)echo 'Building app.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ app.c
CDEPS += $(OUTPUT_DIR)/project/app.d
OBJS += $(OUTPUT_DIR)/project/app.o

$(OUTPUT_DIR)/project/autogen/gatt_db.o: autogen/gatt_db.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/gatt_db.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/gatt_db.c
CDEPS += $(OUTPUT_DIR)/project/autogen/gatt_db.d
OBJS += $(OUTPUT_DIR)/project/autogen/gatt_db.o

$(OUTPUT_DIR)/project/autogen/sl_bluetooth.o: autogen/sl_bluetooth.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_bluetooth.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_bluetooth.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_bluetooth.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_bluetooth.o

$(OUTPUT_DIR)/project/autogen/sl_board_default_init.o: autogen/sl_board_default_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_board_default_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_board_default_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.o

$(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.o: autogen/sl_device_init_clocks.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_device_init_clocks.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_device_init_clocks.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.o

$(OUTPUT_DIR)/project/autogen/sl_event_handler.o: autogen/sl_event_handler.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_event_handler.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_event_handler.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.o

$(OUTPUT_DIR)/project/autogen/sl_i2cspm_init.o: autogen/sl_i2cspm_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_i2cspm_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_i2cspm_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_i2cspm_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_i2cspm_init.o

$(OUTPUT_DIR)/project/autogen/sl_iostream_handles.o: autogen/sl_iostream_handles.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_iostream_handles.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_iostream_handles.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_iostream_handles.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_iostream_handles.o

$(OUTPUT_DIR)/project/autogen/sl_iostream_init_usart_instances.o: autogen/sl_iostream_init_usart_instances.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_iostream_init_usart_instances.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_iostream_init_usart_instances.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_iostream_init_usart_instances.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_iostream_init_usart_instances.o

$(OUTPUT_DIR)/project/autogen/sl_power_manager_handler.o: autogen/sl_power_manager_handler.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_power_manager_handler.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_power_manager_handler.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_power_manager_handler.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_power_manager_handler.o

$(OUTPUT_DIR)/project/autogen/sl_spidrv_init.o: autogen/sl_spidrv_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_spidrv_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_spidrv_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_spidrv_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_spidrv_init.o

$(OUTPUT_DIR)/project/main.o: main.c
	@$(POSIX_TOOL_PATH)echo 'Building main.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ main.c
CDEPS += $(OUTPUT_DIR)/project/main.d
OBJS += $(OUTPUT_DIR)/project/main.o

$(OUTPUT_DIR)/project/sl_gatt_service_device_information.o: sl_gatt_service_device_information.c
	@$(POSIX_TOOL_PATH)echo 'Building sl_gatt_service_device_information.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ sl_gatt_service_device_information.c
CDEPS += $(OUTPUT_DIR)/project/sl_gatt_service_device_information.d
OBJS += $(OUTPUT_DIR)/project/sl_gatt_service_device_information.o

# Automatically-generated Simplicity Studio Metadata
# Please do not edit or delete these lines!
# SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA
# END OF METADATA