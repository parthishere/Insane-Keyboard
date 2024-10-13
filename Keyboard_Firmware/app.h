/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef APP_H
#define APP_H

#include "sl_power_manager.h"
#include "src/oscillator.h"
#include "src/gpio.h"
#include "src/display.h"
#include "src/i2c.h"
#include "src/spi.h"
#include "src/timers.h"

#define EM3_MODE 3
#define EM1_MODE 1
// 0 = highest energy mode, 3 = lowest energy mode
// #define LOWEST_ENERGY_MODE 0
// #define LOWEST_ENERGY_MODE 1
#define LOWEST_ENERGY_MODE 2
// #define LOWEST_ENERGY_MODE 3

// If PRINT_LOG_STATEMENTS is set to 1, PRINT_LOG macro will use LOG_INFO for logging.
#define PRINT_LOG_STATEMENTS 0

// If PRINT_LOG_STATEMENTS is set to 1, PRINT_LOG macro will use LOG_INFO for logging.
// Otherwise, PRINT_LOG is defined as an empty macro, effectively disabling logging.
#if (PRINT_LOG_STATEMENTS == 1)
#define PRINT_LOG LOG_INFO
#else
#define PRINT_LOG(...)
#endif


/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void);

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);

#endif  // APP_H
