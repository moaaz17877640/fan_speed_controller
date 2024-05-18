/* 
 * File:   hal_spi.h
 * Author: MOAAZ
 *
 * Created on May 2, 2024, 12:03 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H
#include "../proc/pic18f4620.h"
#include "../Mcal_Std_Types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
/*section configuration defines*/
#define MSSP_SPI_INPUT_SAMPLE_AT_END     1
#define MSSP_SPI_INPUT_SAMPLE_AT_MIDDLE  0

#define MSSP_SPI_TRANSMIT_AT_TRANSITION_FROM_ACTIVE_TO_IDLE   1
#define MSSP_SPI_TRANSMIT_AT_TRANSITION_FROM_IDLE_TO_ACTIVE   0

#define MSSP_SPI_BUFFER_FULL   1
#define MSSP_SPI_BUFFER_EMPTY  0

#define MSSP_SPI_COLLISION_DETECTED       1
#define MSSP_SPI_COLLISION_NOT_DETECTED   0

#define MSSP_SPI_OVERFLOW_OCCUR      1
#define MSSP_SPI_OVERFLOW_NOT_OCCUR  0

#define MSSP_SPI_MODULE_ENABLE()   (SSPCON1bits.SSPEN = 1)
#define MSSP_SPI_MODULE_DISABLE()   (SSPCON1bits.SSPEN = 0)

#define MSSP_SPI_CLK_POARITY_IDLE_HIGH   1
#define MSSP_SPI_CLK_POARITY_IDLE_LOW    0

/*spi modes*/
#define MSSP_SPI_MASTER_CLK_FOSC_4       0
#define MSSP_SPI_MASTER_CLK_FOSC_16      1
#define MSSP_SPI_MASTER_CLK_FOSC_64      2
#define MSSP_SPI_MASTER_CLK_TMR2_OUT2    3
#define MSSP_SPI_SLAVE_CLK_SS_ENABL      4
#define MSSP_SPI_SLAVE_CLK_SS_DISABLE    5

typedef struct{
    uint8 clk_polarity:1 ;
    uint8 clk_phase  :1 ;
    uint8 clk_sample  :1;
    uint8 Reserved :5 ;
}spi_config ;
typedef struct {
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*MSSP_SPI_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg  priority_SPI ;
#endif
spi_config spi_cfg ;
uint16  spi_mode ;
}mssp_spi_t;
Std_ReturnType Spi_Init(const mssp_spi_t *spi);
Std_ReturnType Spi_DEInit(const mssp_spi_t *spi);
Std_ReturnType Spi_Read_byte_block(const mssp_spi_t *spi, uint8 *data);
Std_ReturnType Spi_Write_byte_block(const mssp_spi_t *spi, uint8 data);
Std_ReturnType Spi_Read_byte_noblock(const mssp_spi_t *spi, uint8 *data);
Std_ReturnType Spi_Write_byte_noblock(const mssp_spi_t *spi, uint8 data);
#endif	/* HAL_SPI_H */

