#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// $[ACMP0]
// [ACMP0]$

// $[ACMP1]
// [ACMP1]$

// $[ADC0]
// [ADC0]$

// $[CMU]
// [CMU]$

// $[CSEN]
// [CSEN]$

// $[DBG]
// DBG SWCLKTCK on PF0
#ifndef DBG_SWCLKTCK_PORT                       
#define DBG_SWCLKTCK_PORT                        gpioPortF
#endif
#ifndef DBG_SWCLKTCK_PIN                        
#define DBG_SWCLKTCK_PIN                         0
#endif
#ifndef DBG_ROUTE_LOC                           
#define DBG_ROUTE_LOC                            0
#endif

// DBG SWDIOTMS on PF1
#ifndef DBG_SWDIOTMS_PORT                       
#define DBG_SWDIOTMS_PORT                        gpioPortF
#endif
#ifndef DBG_SWDIOTMS_PIN                        
#define DBG_SWDIOTMS_PIN                         1
#endif

// DBG SWV on PF2
#ifndef DBG_SWV_PORT                            
#define DBG_SWV_PORT                             gpioPortF
#endif
#ifndef DBG_SWV_PIN                             
#define DBG_SWV_PIN                              2
#endif
#ifndef DBG_SWV_LOC                             
#define DBG_SWV_LOC                              0
#endif

// [DBG]$

// $[ETM]
// [ETM]$

// $[PTI]
// [PTI]$

// $[GPIO]
// [GPIO]$

// $[I2C0]
// I2C0 SCL on PC10
#ifndef I2C0_SCL_PORT                           
#define I2C0_SCL_PORT                            gpioPortC
#endif
#ifndef I2C0_SCL_PIN                            
#define I2C0_SCL_PIN                             10
#endif
#ifndef I2C0_SCL_LOC                            
#define I2C0_SCL_LOC                             14
#endif

// I2C0 SDA on PC11
#ifndef I2C0_SDA_PORT                           
#define I2C0_SDA_PORT                            gpioPortC
#endif
#ifndef I2C0_SDA_PIN                            
#define I2C0_SDA_PIN                             11
#endif
#ifndef I2C0_SDA_LOC                            
#define I2C0_SDA_LOC                             16
#endif

// [I2C0]$

// $[I2C1]
// [I2C1]$

// $[IDAC0]
// [IDAC0]$

// $[LESENSE]
// [LESENSE]$

// $[LETIMER0]
// [LETIMER0]$

// $[LEUART0]
// [LEUART0]$

// $[LFXO]
// [LFXO]$

// $[MODEM]
// [MODEM]$

// $[PCNT0]
// [PCNT0]$

// $[PRS.CH0]
// [PRS.CH0]$

// $[PRS.CH1]
// [PRS.CH1]$

// $[PRS.CH2]
// [PRS.CH2]$

// $[PRS.CH3]
// [PRS.CH3]$

// $[PRS.CH4]
// [PRS.CH4]$

// $[PRS.CH5]
// [PRS.CH5]$

// $[PRS.CH6]
// [PRS.CH6]$

// $[PRS.CH7]
// [PRS.CH7]$

// $[PRS.CH8]
// [PRS.CH8]$

// $[PRS.CH9]
// [PRS.CH9]$

// $[PRS.CH10]
// [PRS.CH10]$

// $[PRS.CH11]
// [PRS.CH11]$

// $[TIMER0]
// [TIMER0]$

// $[TIMER1]
// [TIMER1]$

// $[USART0]
// USART0 RX on PA1
#ifndef USART0_RX_PORT                          
#define USART0_RX_PORT                           gpioPortA
#endif
#ifndef USART0_RX_PIN                           
#define USART0_RX_PIN                            1
#endif
#ifndef USART0_RX_LOC                           
#define USART0_RX_LOC                            0
#endif

// USART0 TX on PA0
#ifndef USART0_TX_PORT                          
#define USART0_TX_PORT                           gpioPortA
#endif
#ifndef USART0_TX_PIN                           
#define USART0_TX_PIN                            0
#endif
#ifndef USART0_TX_LOC                           
#define USART0_TX_LOC                            0
#endif

// [USART0]$

// $[USART1]
// USART1 CLK on PC8
#ifndef USART1_CLK_PORT                         
#define USART1_CLK_PORT                          gpioPortC
#endif
#ifndef USART1_CLK_PIN                          
#define USART1_CLK_PIN                           8
#endif
#ifndef USART1_CLK_LOC                          
#define USART1_CLK_LOC                           11
#endif

// USART1 CS on PC9
#ifndef USART1_CS_PORT                          
#define USART1_CS_PORT                           gpioPortC
#endif
#ifndef USART1_CS_PIN                           
#define USART1_CS_PIN                            9
#endif
#ifndef USART1_CS_LOC                           
#define USART1_CS_LOC                            11
#endif

// USART1 RX on PC7
#ifndef USART1_RX_PORT                          
#define USART1_RX_PORT                           gpioPortC
#endif
#ifndef USART1_RX_PIN                           
#define USART1_RX_PIN                            7
#endif
#ifndef USART1_RX_LOC                           
#define USART1_RX_LOC                            11
#endif

// USART1 TX on PC6
#ifndef USART1_TX_PORT                          
#define USART1_TX_PORT                           gpioPortC
#endif
#ifndef USART1_TX_PIN                           
#define USART1_TX_PIN                            6
#endif
#ifndef USART1_TX_LOC                           
#define USART1_TX_LOC                            11
#endif

// [USART1]$

// $[USART2]
// [USART2]$

// $[VDAC0]
// [VDAC0]$

// $[WTIMER0]
// [WTIMER0]$

// $[CUSTOM_PIN_NAME]
#ifndef _PORT                                   
#define _PORT                                    gpioPortA
#endif
#ifndef _PIN                                    
#define _PIN                                     0
#endif

// [CUSTOM_PIN_NAME]$

#endif // PIN_CONFIG_H

