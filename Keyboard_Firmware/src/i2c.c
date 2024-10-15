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



#define TCA6408_ADDR1                           0x20
#define TCA6408_ADDR2                           0x21

#define TCA6408_INPUT                           0x00
#define TCA6408_OUTPUT                          0x01
#define TCA6408_POLARITY_INVERSION              0x02
#define TCA6408_CONFIGURATION                   0x03






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

/* Global variables */
uint8_t cmd_data = TEMPRETURE_COMMAND;         // Command data for reading temperature
I2C_TransferReturn_TypeDef I2C_TransferStatus; // Holds the status of the I2C transfer
uint8_t readData[2];                           // Buffer to hold raw temperature data read from the sensor
int32_t temprature;                            // Variable to hold the calculated temperature

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
 * @brief Reads temperature data from the SI7021 sensor.
 *
 * This function sends a command to the SI7021 temperature sensor to initiate a temperature measurement,
 * then reads the measurement result from the sensor over I2C. The raw sensor data is processed to calculate
 * the temperature value, which is then returned.
 *
 * @return uint16_t The calculated temperature value from the sensor data.
 */
uint16_t read_SI7021()
{
  //sensor_Enable();            // Enable the sensor pin
  timerWaitUs_polled(INITIAL_DELAY); // Wait for the sensor to be ready

  // Setup I2C transfer for writing the read temperature command to the sensor
  I2C_TransferSeq.addr = SI7021_I2C_ADDRESS << 1; // Set the sensor's I2C address (left shift for write operation)
  I2C_TransferSeq.flags = I2C_FLAG_WRITE;         // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = &cmd_data;        // Point to the command data
  I2C_TransferSeq.buf[0].len = sizeof(cmd_data);  // Set the command data length

  // Perform the I2C write operation
  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);
  timerWaitUs_polled(TRANSFER_DELAY); // Wait after sending the read command

  // Check if the write operation was successful
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Failed to write %u bytes when writing to Register, return value was %d", sizeof(cmd_data), I2C_TransferStatus);
    return 0; // Return 0 if the operation failed
  }

  // Setup I2C transfer for reading the temperature data from the sensor
  I2C_TransferSeq.addr = SI7021_I2C_ADDRESS << 1; // Set the sensor's I2C address (left shift for read operation)
  I2C_TransferSeq.flags = I2C_FLAG_READ;          // Indicate that this is a read operation
  I2C_TransferSeq.buf[0].data = readData;         // Point to the buffer to store read data
  I2C_TransferSeq.buf[0].len = 2;                 // Expect to read 2 bytes of data

  // Perform the I2C read operation
  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);

  // Check if the read operation was successful
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Failed to write %u bytes while reading register, return value was %d", sizeof(cmd_data), I2C_TransferStatus);
    return 0; // Return 0 if the operation failed
  }

  // Calculate temperature from the raw sensor data
  temprature = SHIFT_DATA_EIGHT_BIT(readData[0]) + MASK_TEMPRATURE_DATA_BITS(readData[1]);
  temprature = CONVERT_TEMP_TO_C(temprature);

  LOG_INFO("Got the temprature from Si7021 sensor => %d Celsius\n", temprature); // Log the temperature data

  //sensor_Disable();    // Disable the sensor
  return (temprature); // Return the calculated temperature
}



void io_expander_readByte(void)
{
  cmd_data = TCA6408_INPUT;
  // Setup I2C transfer for writing the read temperature command to the sensor
  I2C_TransferSeq.addr = TCA6408_ADDR1 << 1; // Set the sensor's I2C address (left shift for write operation)
  I2C_TransferSeq.flags = I2C_FLAG_WRITE_READ;         // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = &cmd_data;        // Point to the command data
  I2C_TransferSeq.buf[0].len = sizeof(cmd_data);  // Set the command data length

  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Failed to write %u bytes when writing to Register, return value was %d", sizeof(cmd_data), I2C_TransferStatus);
    return 0; // Return 0 if the operation failed
  }

  LOG_INFO("!! IO expander read sucessfull, data : %d len %d \n\r", I2C_TransferSeq.buf[1].data, I2C_TransferSeq.buf[1].data);

}

