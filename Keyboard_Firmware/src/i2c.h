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
#include "timers.h"    // Timers header
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

/**
 * @brief Waits for the sensor to be ready to send temperature data.
 * Enables the sensor and waits for a specified delay to ensure the sensor is ready for data transmission.
 */
void read_SI7021_write_initiate();

/**
 * @brief Initiates a temperature measurement command to the SI7021 sensor.
 * Sends a command over I2C to the SI7021 sensor to start a temperature measurement.
 */
void read_SI7021_timer_wait();

/**
 * @brief Reads the measured temperature from the SI7021 sensor.
 * Initiates an I2C read operation to retrieve the temperature measurement from the sensor.
 */
void read_SI7021_MEASUREMENT();

/**
 * @brief Reads temperature data from the SI7021 sensor, formats it for BLE transmission,
 * and manages the indication sending and queuing based on the BLE connection state.
 * 
 * The function reads raw temperature data from the SI7021 sensor, converts it to Celsius,
 * formats it according to the IEEE 11073-20601 FLOAT-Type format for BLE transmission,
 * writes the formatted data to the local GATT database, and manages the sending of 
 * indications or queuing them if another indication is currently in flight.
 * 
 * @return uint16_t The temperature in Celsius.
 */
uint16_t read_SI7021();



/**
 * Attempts to send a temperature/button indication immediately if possible.
 * If an indication is already in-flight, or the queue is not empty, the temperature data
 * is queued for later transmission.
 *
 * @param[in] htm_temperature_buffer The buffer containing the temperature data formatted for BLE transmission.
 * @param[in] is_button is indication is for button?.
 */
void attemptToSendOrQueueIndication(uint8_t *htm_temperature_buffer, bool is_button);


/**
 * Attempts to send the next queued indication for either temperature data or button state. This function is called
 * when the device is ready to send another indication, typically after a previous indication has been sent and
 * acknowledged, or when the device first becomes ready to send indications after a busy period.
 *
 * The function checks the queue for any pending indications. If an indication is found, it determines the type based
 * on the characteristic handle and attempts to send the indication using the appropriate function. This ensures
 * that indications are sent in the order they were queued, maintaining the integrity of the transmitted data.
 */
void send_from_queue();

#endif // !__I2C_h__
