/* 
 * File:   hal_i2c.h
 * Author: Moaaz elmahi
 *
 * Created on April 26, 2024, 8:46 AM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H
/* section include */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
/*configuration defines*/
 /*   Slew Rate configure   */
#define I2C_SLEW_RATE_ENABLE_CFG    0
#define I2C_SLEW_RATE_DISABLE_CFG   1
/* SMBus Select configure */
#define I2C_SMBUS_SELECT_ENABLE_CFG  1
#define I2C_SMBUS_SELECT_DISABLE_CFG 0
/* Data/Address  configure */
#define I2C_LAST_BYTE_RECE_TRANS_DATA_CFG             1
#define I2C_LAST_BYTE_RECE_TRANS_DATA_ADDRESS_CFG     0
/* stop bit  configure */
#define I2C_STOP_BIT_DETECTED_LAST_CFG       1   
#define I2C_STOP_BIT_NOT_DETECTED_LAST_CFG   0  
/* start bit  configure */
#define I2C_START_BIT_DETECTED_LAST_CFG       1   
#define I2C_START_BIT_NOT_DETECTED_LAST_CFG   0
/*Read /write bit configure */
#define I2C_SLAVE_MODE_READ_CFG  1
#define I2C_SLAVE_MODE_WRITE_CFG 0
/*Transmit running status*/
#define I2C_MASTER_TRANSMIT_IN_PROGRESS_CFG      1
#define I2C_MASTER_TRANSMIT_NOT_IN_PROGRESS_CFG  0
/* buffer reg configure */
#define I2C_BUFFER_REGISTER_IS_FULL_CFG   1
#define I2C_BUFFER_REGISTER_IS_EMPTY_CFG  0
/* Mssp module configure */
#define MSSP_MODULE_ENABLE_CFG   1
#define MSSP_MODULE_DISABLE_CFG  0
/* Mssp mode configure*/
#define I2C_MASTER_MODE_CFG  1
#define I2C_SLAVE_MODE_CFG   0
/* general call configuration*/
#define I2C_GENERAL_CALL_ENABLE_CFG 1
#define I2C_GENERAL_CALL_DISABLE_CFG 0
/*ACK bit configuration*/
#define  I2C_RECEIVED_ACK_CFG        0
#define  I2C_RECEIVED_NOT_ACK_CFG    1
/*ACK bit configuration*/
#define I2C_SEND_ACK_CFG        0
#define I2C_SEND_NOT_ACK_CFG    1
/*receiving configuration*/
#define I2C_MASTER_RECEIVE_ENABLE_CFG  1
#define I2C_MASTER_RECEIVE_DISABLE_CFG  0
/* MSSP Modes configuration*/
#define  I2C_Slave_mode_7bit_address         0x06U
#define  I2C_Slave_mode_10bit_address        0x07U
#define  I2C_Master_mode                     0x08U
#define  I2C_Firmware_Controlled_Master_mode 0x0BU
#define  I2C_Slave_mode_7bit_address_Interrupt_enable 0x0EU 
#define  I2C_Slave_mode_10bit_address_Interrupt_enable 0x0FU 

/*macro function for configuration*/
 /*   Slew Rate configure   */
#define I2C_SLEW_RATE_ENABLE()   (SSPSTATbits.SMP = 0)
#define I2C_SLEW_RATE_DISABLE()   (SSPSTATbits.SMP = 1)
/* SMBus Select configure */
#define I2C_SMBUS_SELECT_ENABLE() (SSPSTATbits.CKE = 1)
#define I2C_SMBUS_SELECT_DISABLE() (SSPSTATbits.CKE = 0)  
/* general call configuration*/
#define I2C_GENERAL_CALL_ENABLE() (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE() (SSPCON2bits.GCEN = 0)
/*receiving configuration*/
#define I2C_MASTER_RECEIVE_ENABLE() (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECEIVE_DISABLE() (SSPCON2bits.RCEN = 0)
/* Mssp module configure */
#define MSSP_MODULE_ENABLE() (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE() (SSPCON1bits.SSPEN = 0)
/*clock stretch configuration*/
#define I2C_CLK_STRETCH_ENABLE() (SSPCON1bits.CKP = 0)
#define I2C_CLK_STRETCH_DISABLE() (SSPCON1bits.CKP = 1)
/* section datatype declaration */
typedef struct {
    uint8 i2c_mode :1 ;      /*master or slave*/
    uint8 Slew_Rate :1;
    uint8 SMBus :1 ;
    uint8 i2c_mode_cfg ;    /* MSSP Modes configuration*/
    uint8 i2c_general_call : 1;
    uint8 i2c_master_rec_mode : 1;
    uint8 slave_address ;
    uint8 reserved  : 3 ;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg i2c_bus_priority ;
    interrupt_priority_cfg i2c_tr_priority ;
#endif
}i2c_cfg_t;   
typedef struct{
    uint16 clock_value ;
    i2c_cfg_t i2c_cfg ;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Write_Collision_HANDLER)(void);
    void (*I2C_Receive_Overflow_IndicatoR_HANDLER)(void);
    void (*I2C_INTERRUPT_HANDLER)(void) ;
#endif
}Mssp_i2c_t;
 /* interfaces declaration*/
Std_ReturnType   MSSP_I2c_MODE_Init(const Mssp_i2c_t *i2c);
Std_ReturnType   MSSP_I2c_MODE_DEInit(const Mssp_i2c_t *i2c);

Std_ReturnType   MSSP_I2c_Send_start_Bit(const Mssp_i2c_t *i2c);
Std_ReturnType   MSSP_I2c_Send_Stop_Bit(const Mssp_i2c_t *i2c);
Std_ReturnType   MSSP_I2c_Send_Repeated_start_Bit(const Mssp_i2c_t *i2c);

Std_ReturnType   MSSP_I2c_read_data_Blocking(const Mssp_i2c_t *i2c ,uint8 *data , uint8 ACK);
Std_ReturnType   MSSP_I2c_Write_data_Blocking(const Mssp_i2c_t *i2c ,uint8 data, uint8 *ACK);

Std_ReturnType   MSSP_I2c_read_data_nBlocking(const Mssp_i2c_t *i2c ,uint8 *data, uint8 ACK);
Std_ReturnType   MSSP_I2c_Write_data_nBlocking(const Mssp_i2c_t *i2c ,uint8 data, uint8 *ACK);

#endif	/* HAL_I2C_H */

