/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H
 
/************************ Includes ************************/
#include "../Mcal_Std_Types.h"
/************************  Macro Declaration ************************/
#define INTERRUPT_FEATURE_ENABLE                       1
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE               INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE         INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_onChange_FEATURE_ENABLE     INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE_CFG               INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define MSSP_SPI_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
/************************  Macro Function Declaration ************************/
 

/************************  Data Type Declaration ************************/
 

/************************  Software interface Declaration ************************/
 

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

