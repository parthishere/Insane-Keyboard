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
 * @file    i2c.c
 * @brief   This file includes the implementation for I2C communication, specifically
 *          designed to interface with the SI7021 temperature sensor.
 *
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 *
 */

#include "i2c.h" // Include the I2C interface header file

// Enables debug logging for this file
#define INCLUDE_LOG_DEBUG 1
#include "log.h" // Includes the logging header for debug messages

// SI7021 sensor I2C address and command definitions
#define SI7021_I2C_ADDRESS 0x40 // I2C address of the SI7021 sensor
#define TEMPRETURE_COMMAND 0xF3 // Command to read temperature

// Timing delays for sensor communication
#define INITIAL_DELAY 80000  // Initial delay in microseconds before reading temperature
#define TRANSFER_DELAY 10800 // Delay in microseconds after initiating the temperature read command

// I2C SCL and SDA pin definitions and their alternate locations
#define SCL_PIN 10
#define SDA_PIN 11
#define PORT_ALTERNATE_LOCATION_SCL 14
#define PORT_ALTERNATE_LOCATION_SDA 16

#define SHIFT_DATA_EIGHT_BIT(x) (uint32_t)((uint32_t)x << 8)
#define MASK_TEMPRATURE_DATA_BITS(x) (uint32_t)((uint32_t)x & 0xfc)
#define CONVERT_TEMP_TO_C(x) (int32_t)((((x * 21965L) >> 13) - 46850) / 1000);

#define LETIMER_IEN_COMP1_ (1 << 1)

#define TEMPERATURE_BUFFER_SIZE 5
#define MANTISSA_MULTIPLIER 1000
#define EXPONENT -3

/* Global variables */
uint8_t cmd_data = TEMPRETURE_COMMAND;         // Command data for reading temperature
I2C_TransferReturn_TypeDef I2C_TransferStatus; // Holds the status of the I2C transfer
uint8_t readData[2];                           // Buffer to hold raw temperature data read from the sensor
int32_t temperature;                           // Variable to hold the calculated temperature

I2C_TransferSeq_TypeDef I2C_TransferSeq; // I2C transfer sequence structure

/**
 * @brief Initializes the I2C interface for communication.
 *
 * This function configures the I2C peripheral settings and GPIO pins used for SCL and SDA lines.
 * It prepares the I2C hardware for communication with I2C devices, specifically the SI7021 temperature sensor in this context.
 */
void init_I2C()
{
  // Configuration structure for I2C initialization
  I2CSPM_Init_TypeDef I2C_Config = {
      .port = I2C0,                                   // Specify the I2C instance
      .sclPort = gpioPortC,                           // GPIO port for SCL line
      .sclPin = SCL_PIN,                              // GPIO pin number for SCL line
      .sdaPort = gpioPortC,                           // GPIO port for SDA line
      .sdaPin = SDA_PIN,                              // GPIO pin number for SDA line
      .portLocationScl = PORT_ALTERNATE_LOCATION_SCL, // Alternate location for SCL
      .portLocationSda = PORT_ALTERNATE_LOCATION_SDA, // Alternate location for SDA
      .i2cRefFreq = 0,                                // Reference frequency for I2C (0 if using peripheral clock)
      .i2cMaxFreq = I2C_FREQ_STANDARD_MAX,            // Maximum I2C frequency
      .i2cClhr = i2cClockHLRStandard                  // Clock low/high ratio
  };

  I2CSPM_Init(&I2C_Config); // Initialize I2C with the specified configuration

  return;
}

/**
 * @brief Waits for the sensor to be ready to send temperature data.
 * Enables the sensor and waits for a specified delay to ensure the sensor is ready for data transmission.
 */
void read_SI7021_timer_wait()
{

  timerWaitUs_irq(INITIAL_DELAY); // Wait for the sensor to be ready
  return;
}

/**
 * @brief Initiates a temperature measurement command to the SI7021 sensor.
 * Sends a command over I2C to the SI7021 sensor to start a temperature measurement.
 */
void read_SI7021_write_initiate()
{

  // Setup I2C transfer for writing the read temperature command to the sensor
  I2C_TransferSeq.addr = SI7021_I2C_ADDRESS << 1; // Set the sensor's I2C address (left shift for write operation)
  I2C_TransferSeq.flags = I2C_FLAG_WRITE;         // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = &cmd_data;        // Point to the command data
  I2C_TransferSeq.buf[0].len = sizeof(cmd_data);  // Set the command data length

  NVIC_EnableIRQ(I2C0_IRQn);

  // Perform the I2C write operation
  I2C_TransferStatus = I2C_TransferInit(I2C0, &I2C_TransferSeq);

  // Check for errors in initiating the I2C transfer
  if (I2C_TransferStatus < 0)
  {
    LOG_ERROR("I2C_TransferInit() Write error = %d", I2C_TransferStatus);
  }
}

/**
 * @brief Reads the measured temperature from the SI7021 sensor.
 * Initiates an I2C read operation to retrieve the temperature measurement from the sensor.
 */
void read_SI7021_MEASUREMENT()
{

  // Setup I2C transfer for reading the temperature data from the sensor
  I2C_TransferSeq.addr = SI7021_I2C_ADDRESS << 1; // Set the sensor's I2C address (left shift for read operation)
  I2C_TransferSeq.flags = I2C_FLAG_READ;          // Indicate that this is a read operation
  I2C_TransferSeq.buf[0].data = readData;         // Point to the buffer to store read data
  I2C_TransferSeq.buf[0].len = 2;                 // Expect to read 2 bytes of data

  NVIC_EnableIRQ(I2C0_IRQn);
  // Perform the I2C read operation
  I2C_TransferStatus = I2C_TransferInit(I2C0, &I2C_TransferSeq);

  // Check for errors in initiating the I2C transfer
  if (I2C_TransferStatus < 0)
  {
    LOG_ERROR("I2C_TransferInit() Write error = %d", I2C_TransferStatus);
  }
}

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
uint16_t read_SI7021()
{

  uint8_t htm_temperature_buffer[TEMPERATURE_BUFFER_SIZE]; // Buffer for holding the temperature data in a format suitable for BLE transmission
  uint8_t *p = htm_temperature_buffer;                     // Pointer for buffer manipulation
  uint32_t htm_temperature_flt;                            // Variable to hold the formatted temperature data
  bool status = false;

  uint8_t flags = 0x00;         // Flags for the BLE temperature measurement characteristic
  UINT8_TO_BITSTREAM(p, flags); // Insert the flags into the buffer

  ble_data_struct_t *ble_data = getBleDataPtr();

  // Calculate temperature from the raw sensor data
  temperature = SHIFT_DATA_EIGHT_BIT(readData[0]) + MASK_TEMPRATURE_DATA_BITS(readData[1]);
  temperature = CONVERT_TEMP_TO_C(temperature);

  // Convert temperature to IEEE 11073-20601 FLOAT-Type
  htm_temperature_flt = INT32_TO_FLOAT((int32_t)(temperature * MANTISSA_MULTIPLIER), EXPONENT); // Convert to FLOAT-Type
  UINT32_TO_BITSTREAM(p, htm_temperature_flt);

  // Log the temperature
  PRINT_LOG("Temperature from Si7021 => %d C\n", temperature); // Log the temperature data

  // Write to server's gattdb
  sl_status_t sc = sl_bt_gatt_server_write_attribute_value(
      gattdb_temperature_measurement, // handle from gatt_db.h
      0,                              // offset
      TEMPERATURE_BUFFER_SIZE,        // length
      &htm_temperature_buffer[0]      // in IEEE-11073 format
  );
  // Check for errors in writing to the GATT database
  if (sc != SL_STATUS_OK)
  {
    LOG_ERROR("Failed to write to local db. Status: 0x%04x", sc);
  }

  // Check if it's appropriate to send an indication or queue it
  if (!ble_data->indication_in_flight)
  {

    // Attempt to send or queue the temperature indication
    attemptToSendOrQueueIndication(htm_temperature_buffer, false);
  }
  else
  {
    // Queue the temperature indication if another indication is in flight
    status = write_queue(gattdb_temperature_measurement, TEMPERATURE_BUFFER_SIZE, htm_temperature_buffer);
    // Check for errors in queuing the indication
    if (status)
    {
      LOG_ERROR("Queue Full and Indication in Flight, Discarding HTM Reading !\n\r");
      return 0;
    }
  }

  return (temperature);
}

/**
 * Attempts to send a temperature/button indication immediately if possible.
 * If an indication is already in-flight, or the queue is not empty, the temperature data
 * is queued for later transmission.
 *
 * @param[in] htm_temperature_buffer The buffer containing the temperature data formatted for BLE transmission.
 * @param[in] is_button is indication is for button?.
 */
void attemptToSendOrQueueIndication(uint8_t *htm_temperature_buffer, bool is_button)
{
  // Access shared BLE data structure to manage indication state and connection details
  ble_data_struct_t *ble_data = getBleDataPtr();

  // Check if an indication is already in flight or if there are items in the queue
  if (!ble_data->indication_in_flight && get_queue_depth() == 0)
  {
    // No indications in flight and queue is empty, proceed to send immediately
    if (!is_button && ble_data->ok_to_send_htm_indications)
    {
      // Send temperature indication if this is not for a button
      send_HTM_Indication(htm_temperature_buffer, TEMPERATURE_BUFFER_SIZE);
    }
    else if (ble_data->ok_to_send_button_indications)
    {
      // Send button indication if allowed and this is for a button
      send_Button_Indication(&ble_data->buttonState);
    }
  }
  else
  {
    // Either an indication is in flight or the queue is not empty, attempt to enqueue the data
    bool status;
    if (is_button && ble_data->ok_to_send_button_indications)
    {
      // Attempt to enqueue button state indication
      status = write_queue(gattdb_button_state, 1, &ble_data->buttonState);
    }
    else
    {
      // Attempt to enqueue temperature data for later transmission
      status = write_queue(gattdb_temperature_measurement, TEMPERATURE_BUFFER_SIZE, htm_temperature_buffer);
    }

    // Check if the queue operation was unsuccessful
    if (status)
    {
      LOG_ERROR("Failed to queue indication. Queue might be full.\n\r");
    }
  }
}

/**
 * Attempts to send the next queued indication for either temperature data or button state. This function is called
 * when the device is ready to send another indication, typically after a previous indication has been sent and
 * acknowledged, or when the device first becomes ready to send indications after a busy period.
 *
 * The function checks the queue for any pending indications. If an indication is found, it determines the type based
 * on the characteristic handle and attempts to send the indication using the appropriate function. This ensures
 * that indications are sent in the order they were queued, maintaining the integrity of the transmitted data.
 */
void send_from_queue()
{
  // Access shared BLE data structure
  ble_data_struct_t *ble_data = getBleDataPtr();
  uint16_t handle;       // Characteristic handle for the queued indication
  uint32_t bufferlength; // Length of the indication data
  uint8_t buffer[5];     // Buffer to hold the indication data

  // Attempt to read the next indication from the queue
  bool status = read_queue(&handle, &bufferlength, buffer);

  // Check if the queue read was unsuccessful (no data to send)
  if (!status)
  {
    // Determine the type of indication to send based on the characteristic handle
    if (handle == gattdb_button_state && ble_data->ok_to_send_button_indications)
    {
      // Send button indication if applicable
      send_Button_Indication(buffer);
    }
    else if (handle == gattdb_temperature_measurement && ble_data->ok_to_send_htm_indications)
    {
      // Send temperature indication if applicable
      send_HTM_Indication(buffer, bufferlength);
    }
  }
}
