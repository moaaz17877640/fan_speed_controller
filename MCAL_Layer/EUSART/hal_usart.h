/* 
 * File:   hal_usart.h
 * Author: MOAAZ
 *
 * Created on April 5, 2024, 11:49 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/* section include */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
/*$defines configuration */
/*configure module*/
#define EUSART_MODULE_ENABLE_CFG    1
#define EUSART_MODULE_ENABLE_CFG    0

#define EUSART_SYNCHRONOUS_MODE_CFG   1
#define EUSART_ASYNCHRONOUS_MODE_CFG  0

#define EUSART_ASYNCHRONOUS_TX_ENABLE_CFG           1
#define EUSART_ASYNCHRONOUS_TX_DISABLE_CFG          0

#define EUSART_ASYNCHRONOUS_TX_SELECT_9BIT_ENABLE_CFG       1
#define EUSART_ASYNCHRONOUS_TX_SELECT_9BIT_DISABLE_CFG     0

#define EUSART_TX_INTERRUPT_ENABLE_CFG  1
#define EUSART_TX_INTERRUPT_DISABLE_CFG 0

#define EUSART_ASYNCHRONOUS_RX_ENABLE_CFG           1
#define EUSART_ASYNCHRONOUS_RX_DISABLE_CFG          0

#define EUSART_ASYNCHRONOUS_RX_SELECT_9BIT_ENABLE_CFG       1
#define EUSART_ASYNCHRONOUS_RX_SELECT_9BIT_DISABLE_CFG      0

#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE_CFG  1
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE_CFG 0

#define EUSART_BAUDRATE_ASYN_LOW_SPEED_CFG   0
#define EUSART_BAUDRATE_ASYN_HIGH_SPEED_CFG  1

#define EUSART_BAUDRATE_16BIT_GENERATOR_CFG  1
#define EUSART_BAUDRATE_8BIT_GENERATOR_CFG   0

#define  EUSART_FRAMING_ERROR_ENABLE_CFG    1
#define  EUSART_FRAMING_ERROR_DISABLE_CFG   0

#define  EUSART_OVERRUN_ERROR_ENABLE_CFG    1
#define  EUSART_OVERRUN_ERROR_DISABLE_CFG   0

#define EUSART_MODULE_ENABLE()   (RCSTAbits.SPEN = 1)
#define EUSART_MODULE_DISABLE()   (RCSTAbits.SPEN = 0)
/* section datatype declartion */
typedef struct{
    uint8 asyn_tx_enable         :1 ;
    uint8 asyn_tx_interrupt_cfg  :1 ;
    uint8 asyn_tx_9bit_select    :1 ;
    interrupt_priority_cfg tx_priority ;
    uint8 reserved               :5 ;           
}usart_tx_cfg;
typedef struct{
    uint8 asyn_rx_enable         :1 ;
    uint8 asyn_rx_interrupt_cfg  :1 ;
    uint8 asyn_rx_9bit_select    :1 ;
    interrupt_priority_cfg rx_priority ;
    uint8 reserved               :5 ; 
}usart_rx_cfg;
typedef enum{
    BAUDRATE_ASYNCHRONOUS_8BIT_LOW_SPEED,
            BAUDRATE_ASYNCHRONOUS_8BIT_HIGH_SPEED ,
            BAUDRATE_ASYNCHRONOUS_16BIT_LOW_SPEED = 2 ,
            BAUDRATE_ASYNCHRONOUS_16BIT_HIGH_SPEED ,
            BAUDRATE_SYNCHRONOUS_8BIT,
            BAUDRATE_SYNCHRONOUS_16BIT
}baud_rate_t;
typedef union{
    struct {
        uint8 ferro     :1 ;
        uint8 overr     :1 ;
        uint8 reserved  :6 ;
    };
    uint8 status ;
}usart_error_cfg;
typedef struct{
uint16 baud_rate_value ;
baud_rate_t baud_rate_formula;
usart_tx_cfg tx_cfg ;
usart_rx_cfg rx_cfg ;
usart_error_cfg error_t;
void (*EUSART_TX_INTERRUPT_HANDLER)(void);
void (*EUSART_RX_INTERRUPT_HANDLER)(void);
void (*EUSART_FRAMING_ERROR_INTERRUPT_HANDLER)(void);
void (*EUSART_OVERRUN_ERROR_INTERRUPT_HANDLER)(void);
}eusart_t;
/*section : sw interfaces*/
Std_ReturnType EUSArt_ASYNC_INIT(const eusart_t *_eusa);
Std_ReturnType EUSArt_ASYNC_DEINIT(const eusart_t *_eusa);

Std_ReturnType EUSArt_ASYNC_Write_valueBlocking(uint16 value);
Std_ReturnType EUSArt_ASYNC_WriteString_valueBlocking(uint8 *value , uint16 str_len);

Std_ReturnType EUSArt_ASYNC_Write_valueNoBlocking(uint16 value);
Std_ReturnType EUSArt_ASYNC_WriteString_valueNoBlocking(uint8 *value , uint16 str_len);

Std_ReturnType EUSArt_ASYNC_Restart_mode(void);
Std_ReturnType EUSArt_ASYNC_Read_valueBlocking( uint16 *value);
Std_ReturnType EUSArt_ASYNC_Read_valuenoBlocking( uint16 *value);
#endif	/* HAL_USART_H */

