/*******************************************************************************
 * Copyright (C) 2023 by Parth Thakkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Parth Thakkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    i2c.h
 * @brief   Function definition for I2C sensors(Temperature sensor)
 *
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 *
 */
/* Header Guard */
#ifndef __I2C_h__
#define __I2C_h__

/* Includes */
#include "em_cmu.h"    // Clock management unit headers, necessary for configuring clock settings for I2C
#include "em_i2c.h"    // I2C peripheral library, provides low-level functions to interact with I2C hardware
#include "sl_i2cspm.h" // Simplified I2C SPM (Signal Path Module) library for easier I2C configuration
#include "gpio.h"      // General Purpose Input/Output header, for configuring I2C pins
#include "timer.h"    // Timers header
#include "scheduler.h"
#include "ble.h"
#include "sl_status.h"

/* Function Prototypes */
/**
 * @brief Initializes the I2C interface for communication.
 *
 * This function configures the I2C peripheral settings and GPIO pins used for SCL and SDA lines.
 * It prepares the I2C hardware for communication with I2C devices, specifically the SI7021 temperature sensor in this context.
 */
void init_I2C();


uint16_t read_SI7021();


int io_expander_readByte(void);

#endif // !__I2C_h__
