/***************************************************************************//**
 * @file
 * @brief SL_MX25_FLASH_SHUTDOWN_USART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_MX25_FLASH_SHUTDOWN_CONFIG_H
#define SL_MX25_FLASH_SHUTDOWN_CONFIG_H

// <<< sl:start pin_tool >>>
// {usart signal=TX,RX,CLK} SL_MX25_FLASH_SHUTDOWN
// [USART_SL_MX25_FLASH_SHUTDOWN]
#define SL_MX25_FLASH_SHUTDOWN_PERIPHERAL        USART1
#define SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO     1

// USART1 TX on PC6
#define SL_MX25_FLASH_SHUTDOWN_TX_PORT           gpioPortC
#define SL_MX25_FLASH_SHUTDOWN_TX_PIN            6
#define SL_MX25_FLASH_SHUTDOWN_TX_LOC            11

// USART1 RX on PC7
#define SL_MX25_FLASH_SHUTDOWN_RX_PORT           gpioPortC
#define SL_MX25_FLASH_SHUTDOWN_RX_PIN            7
#define SL_MX25_FLASH_SHUTDOWN_RX_LOC            11

// USART1 CLK on PC8
#define SL_MX25_FLASH_SHUTDOWN_CLK_PORT          gpioPortC
#define SL_MX25_FLASH_SHUTDOWN_CLK_PIN           8
#define SL_MX25_FLASH_SHUTDOWN_CLK_LOC           11

// [USART_SL_MX25_FLASH_SHUTDOWN]

// <gpio> SL_MX25_FLASH_SHUTDOWN_CS

// $[GPIO_SL_MX25_FLASH_SHUTDOWN_CS]
#ifndef SL_MX25_FLASH_SHUTDOWN_CS_PORT          
#define SL_MX25_FLASH_SHUTDOWN_CS_PORT           gpioPortB
#endif
#ifndef SL_MX25_FLASH_SHUTDOWN_CS_PIN           
#define SL_MX25_FLASH_SHUTDOWN_CS_PIN            11
#endif
// [GPIO_SL_MX25_FLASH_SHUTDOWN_CS]$

// <<< sl:end pin_tool >>>

#endif // SL_MX25_FLASH_SHUTDOWN_CONFIG_H
