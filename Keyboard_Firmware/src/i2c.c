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
#include "src/log.h" // Includes the logging header for debug messages

#define TCA6408_COL 0x21

#define TCA6408_ROW 0x20


#define TCA6408_INPUT 0x00
#define TCA6408_OUTPUT 0x01
#define TCA6408_POLARITY_INVERSION 0x02
#define TCA6408_CONFIGURATION 0x03

#define MAX_COLS 8 // 0 to 7 so total 8

#define DEFAULT_PORT_DIR_COL 0b00000000 // all output
#define DEFAULT_PORT_DIR_ROW 0b00011111 // p1, p1, p2, p3, p4 input, other output
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


#define WHICH_IO_EXPANDER(x) ((x == IO_EXPANDER_COL) ? TCA6408_COL << 1 : TCA6408_ROW << 1)

/* Global variables */
uint8_t cmd_data = TEMPRETURE_COMMAND; // Command data for reading temperature
uint8_t writeData[2];                  // setting p0, p1, p2 as input and other as output, setting one = input
uint8_t readData[2];                   // Buffer to hold raw temperature data read from the sensor

int32_t temprature; // Variable to hold the calculated temperature

I2C_TransferReturn_TypeDef I2C_TransferStatus; // Holds the status of the I2C transfer
I2C_TransferSeq_TypeDef I2C_TransferSeq;       // I2C transfer sequence structure

typedef enum
{
  P1_0 = 0b00000001,
  P1_1 = 0b00000010,
  P1_2 = 0b00000100,
  P1_3 = 0b00001000,
  P1_4 = 0b00010000,
  P1_5 = 0b00100000,
  P1_6 = 0b01000000,
  P1_7 = 0b10000000
} io_expander_pin_t;

io_expander_pin_t cols_scanning[8] = {P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7};

int __init_IO_expander(uint8_t which_io_expander, uint8_t data)
{
  if (which_io_expander > 2)
    return 0;

  // initialization of port in io expander
  cmd_data = TCA6408_CONFIGURATION;
  writeData[0] = data; // setting p0, p1, p2 as input and other as output, setting one = input
  // Setup I2C transfer for writing the read temperature command to the sensor
  I2C_TransferSeq.addr = WHICH_IO_EXPANDER(which_io_expander); // Set the sensor's I2C address (left shift for write operation)
  I2C_TransferSeq.flags = I2C_FLAG_WRITE_WRITE;                                                // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = &cmd_data;                                                     // Point to the command data
  I2C_TransferSeq.buf[0].len = 1;                                                              // Set the command data length
  I2C_TransferSeq.buf[1].data = writeData;
  I2C_TransferSeq.buf[1].len = 1;

  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Error: init_I2C, Input pin conf failed, %02X \n", I2C_TransferStatus);
    return 0;
  }
  return 1;
}

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

  timerWaitUs_polled(20 * 1000); // 20ms delay

  // initialization of port direction in io expander

  __init_IO_expander(TCA6408_COL, DEFAULT_PORT_DIR_COL);
  __init_IO_expander(TCA6408_ROW, DEFAULT_PORT_DIR_ROW);

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
  enable_Temperature_Sensor(true);
  // sensor_Enable();            // Enable the sensor pin
  timerWaitUs_polled(INITIAL_DELAY); // Wait for the sensor to be ready
  cmd_data = TEMPRETURE_COMMAND;
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

  readData[0] = 0;
  readData[1] = 1;
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

  PRINT_LOG("Got the temprature from Si7021 sensor => %ld Celsius\n", temprature); // Log the temperature data
  char buf[100];
  snprintf(buf, sizeof(buf), "%d", temprature);
  display_string(buf,70,100);
  // static int cnt = 0;
  // if(cnt%3==0)
  // {
  //   display_string("CONN",2,10);
  //   display_string("0",110,50);
  // }
  // else
  // {
  //   display_string("DISCONN",2,10);
  //   display_string("1",110,50);
  // }
  //   cnt++;
  enable_Temperature_Sensor(false);    // Disable the sensor
  return (temprature); // Return the calculated temperature
}

int io_expander_readByte(uint8_t which_io_expander)
{
  //  __init_IO_expander(1);

  cmd_data = TCA6408_INPUT; // set command to input
  if (which_io_expander > 2)
    return 0;
  // Setup I2C transfer for writing the input register to the expander
  I2C_TransferSeq.addr = WHICH_IO_EXPANDER(which_io_expander); // Set the sensor's I2C
  I2C_TransferSeq.flags = I2C_FLAG_WRITE;                                                      // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = &cmd_data;                                                     // Point to the command data
  I2C_TransferSeq.buf[0].len = 1;                                                              // Set the command data length

  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Failed to write %u bytes when writing to Register, return value was %d", sizeof(cmd_data), I2C_TransferStatus);
    return 0; // Return 0 if the operation failed
  }

  // clearing read data
  readData[0] = 0;
  readData[1] = 0;

  // Setup I2C transfer for writing the read temperature command to the sensor
  I2C_TransferSeq.addr = WHICH_IO_EXPANDER(which_io_expander); // Set the sensor's I2C
  I2C_TransferSeq.flags = I2C_FLAG_READ;                                                       // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = readData;                                                      // Point to the command data
  I2C_TransferSeq.buf[0].len = 1;                                                              // Set the command data length

  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Failed to write %u bytes when writing to Register, return value was %d", sizeof(cmd_data), I2C_TransferStatus);
    return 0; // Return 0 if the operation failed
  }

  
  return readData[0];
}

int io_expander_writeByte(uint8_t which_io_expander, uint8_t what_data)
{
  cmd_data = TCA6408_OUTPUT; // change command to output
   // will look on this 
  writeData[0] = what_data;
  writeData[1] = 1;

  if (which_io_expander > 2)
    return 0;
  // Setup I2C transfer for writing the read temperature command to the sensor
  I2C_TransferSeq.addr = WHICH_IO_EXPANDER(which_io_expander); // Set the sensor's I2C address (left shift for write operation)
  I2C_TransferSeq.flags = I2C_FLAG_WRITE_WRITE;                                                // Indicate that this is a write operation
  I2C_TransferSeq.buf[0].data = &cmd_data;                                                     // Point to the command data
  I2C_TransferSeq.buf[0].len = 1;                                                              // Set the command data length
  I2C_TransferSeq.buf[1].data = writeData;                                                     // Point to the command data
  I2C_TransferSeq.buf[1].len = 1;                                                              // Set the command data length

  I2C_TransferStatus = I2CSPM_Transfer(I2C0, &I2C_TransferSeq);
  if (I2C_TransferStatus != i2cTransferDone)
  {
    LOG_ERROR("Failed to write %u bytes when writing to Register, return value was %d", sizeof(cmd_data), I2C_TransferStatus);
    return 0; // Return 0 if the operation failed
  }
  return writeData[0];
}

static uint8_t scanned_keys[MAX_COLS];

uint8_t * scan_io_expander(void)
{
  __init_IO_expander(IO_EXPANDER_ROW, DEFAULT_PORT_DIR_ROW);
  memset(scanned_keys, 0x00, sizeof(scanned_keys));
  for (int col = 0; col < MAX_COLS; col++)
  {
    // __init_IO_expander(IO_EXPANDER_COL, 0b00000000);
    io_expander_writeByte(IO_EXPANDER_COL, cols_scanning[col]);  // setting one to scanning column.

    uint8_t data = io_expander_readByte(IO_EXPANDER_ROW) & DEFAULT_PORT_DIR_ROW;
    
    if(data > 0){
      scanned_keys[col] = data;
      // PRINT_LOG("DATA : 0x%02X, col %d %d\n\r", data, col, scanned_keys[col]);

    }  
    
  }
  __init_IO_expander(IO_EXPANDER_COL, 0b00000000);
  io_expander_writeByte(IO_EXPANDER_COL, 0xFF);
  return scanned_keys;
}

