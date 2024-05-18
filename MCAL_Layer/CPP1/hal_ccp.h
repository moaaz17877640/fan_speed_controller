/* 
 * File:   hal_ccp.h
 * Author: Moaaz elmahy
 *
 * Created on March 14, 2024, 12:59 PM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H
/* SECTION : includes*/
#include "../proc/pic18f4620.h"
#include "../Mcal_Std_Types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
/*section configuration defines*/
#define CCP1_MODULE_COMPARE_MODE_CFG        0x00
#define CCP1_MODULE_CAPTURE_MODE_CFG        0x01
#define CCP1_MODULE_PWM_MODE_CFG            0x02
#define CCP1_MODULE_SELECTED      (CCP1_MODULE_PWM_MODE_CFG)
//==================================================
#define CCP2_MODULE_COMPARE_MODE_CFG        0x00
#define CCP2_MODULE_CAPTURE_MODE_CFG        0x01
#define CCP2_MODULE_PWM_MODE_CFG            0x02
#define CCP2_MODULE_SELECTED      (CCP2_MODULE_PWM_MODE_CFG)
//==================================================
/*tiimer_2 configuration for ccp module*/
typedef enum{
    CCP_TIMER2_POSTSCALER_DIV_1 = 1,
            CCP_TIMER2_POSTSCALER_DIV_2,
            CCP_TIMER2_POSTSCALER_DIV_3,
            CCP_TIMER2_POSTSCALER_DIV_4 ,
            CCP_TIMER2_POSTSCALER_DIV_5 ,
            CCP_TIMER2_POSTSCALER_DIV_6 ,
            CCP_TIMER2_POSTSCALER_DIV_7 ,
            CCP_TIMER2_POSTSCALER_DIV_8 ,
            CCP_TIMER2_POSTSCALER_DIV_9 ,
            CCP_TIMER2_POSTSCALER_DIV_10 ,
            CCP_TIMER2_POSTSCALER_DIV_11 ,
            CCP_TIMER2_POSTSCALER_DIV_12 ,
            CCP_TIMER2_POSTSCALER_DIV_13 ,
            CCP_TIMER2_POSTSCALER_DIV_14 ,
            CCP_TIMER2_POSTSCALER_DIV_15 ,
            CCP_TIMER2_POSTSCALER_DIV_16            
}ccp_timer2_postscaler_value;
typedef enum {
    CCP_TIMER2_PRESCALER_DIV_1 = 1,
             CCP_TIMER2_PRESCALER_DIV_4,
             CCP_TIMER2_PRESCALER_DIV_16,

}ccp_timer2_prescalar;
// configuration macro for capture mode ccp1
#define CCP1_CAPTURE_READY            0x01
#define CCP1_CAPTURE_NOT_READY        0x00
// configuration macro for compare mode
#define CCP1_COMPARE_READY            0x01
#define CCP1_COMPARE_NOT_READY        0x00

// configuration macro for capture mode
#define CCP2_CAPTURE_READY            0x01
#define CCP2_CAPTURE_NOT_READY        0x00
// configuration macro for compare mode
#define CCP2_COMPARE_READY            0x01
#define CCP2_COMPARE_NOT_READY        0x00
// configuration submode
#define  Capture_Compare_PWM_disabled               (uint8)(0x00)
#define  Compare_Mode_Toggle_Output                 (uint8)(0x02)
#define  Capture_mode_every_falling_edge            (uint8)(0x04)
#define  Capture_mode_every_rising_edge             (uint8)(0x05)
#define  Capture_mode_every_4rising_edge            (uint8)(0x06)
#define  Capture_mode_every_16rising_edge           (uint8)(0x07)
#define  Compare_mode_force_CCP2_pin_High           (uint8)(0x08)
#define  Compare_mode_force_CCP2_pin_Low            (uint8)(0x09)
#define  Compare_mode_generate_software_interrupt   (uint8)(0x0A)
#define  Compare_mode_trigger_special_event         (uint8)(0x0B)
#define  PWM_Mode                                   (uint8)(0x0C)  
/* SECTION :macro function  declarations */
#define CONFIGURE_CCP1_SUB_MODE(_CONFIG_)  (CCP1CONbits.CCP1M =_CONFIG_)
#define CONFIGURE_CCP2_SUB_MODE(_CONFIG_)  (CCP2CONbits.CCP2M =_CONFIG_)

/* SECTION : datatype declarations */
typedef enum{
 CCP_MODULE_COMPARE_MODE    ,
 CCP_MODULE_CAPTURE_MODE    ,
 CCP_MODULE_PWM_MODE  
}ccp_mode_t;
typedef enum{
    TIMER1_FOR_CCP1_CCP2 ,
           TIMER1_FOR_CCP1_TIMER3_FOR_CCP2,
           TIMER3_FOR_CCP1_CCP2  
}Selected_Timer_t;
typedef enum{
    CCP1_INST ,
            CCP2_INST
}ccp_inst_t;
typedef union{
   struct{
  uint8 CCP_REG_High ;
  uint8 CCP_REG_Low ;
    };
 struct{
    uint16 CCP_16_REG ;
    };
}CCP_reg_t;
typedef struct {
#if (CCP1_INTERRUPT_FEATURE_ENABLE  == INTERRUPT_FEATURE_ENABLE)
    void (*CCP1_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg  priority_CCP1 ;
#endif
#if (CCP2_INTERRUPT_FEATURE_ENABLE  == INTERRUPT_FEATURE_ENABLE)
    void (*CCP2_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg  priority_CCP2 ;
#endif
#if (CCP1_MODULE_SELECTED == CCP1_MODULE_PWM_MODE_CFG)||(CCP2_MODULE_SELECTED == CCP2_MODULE_PWM_MODE_CFG)
    uint16 PWM_Freq ;  // Fosc
    ccp_timer2_prescalar timer2_prescaler ;
    ccp_timer2_postscaler_value timer2_postscaler ;
#endif 
    ccp_inst_t ccp_inst ;
    ccp_mode_t CCP_Mode  ;
    uint8 Sub_mode :  4  ;
    uint8 Reserved  :  2  ;
    Selected_Timer_t tmr;
    pin_config_t ccp_pin ;
}ccp_t;
/* SECTION : functions declaration*/
Std_ReturnType CCP_INIt(const ccp_t *_ccp);
Std_ReturnType CCP_DEINIt(const ccp_t *_ccp);
#if CCP1_MODULE_SELECTED == CCP1_MODULE_PWM_MODE_CFG || CCP2_MODULE_SELECTED == CCP2_MODULE_PWM_MODE_CFG
Std_ReturnType START_PWM(const ccp_t *_ccp);
Std_ReturnType STOP_PWM(const ccp_t *_ccp);
Std_ReturnType PWM_set_Duty(uint8 duty ,const ccp_t *_ccp);
#endif

#if CCP1_MODULE_SELECTED == CCP1_MODULE_CAPTURE_MODE_CFG || CCP2_MODULE_SELECTED == CCP2_MODULE_CAPTURE_MODE_CFG
Std_ReturnType capture_is_ready(uint8 *capture_statue ,const ccp_t *_ccp );
Std_ReturnType capture_read_value(const ccp_t *_ccp, uint16 *capture_value );
#endif

#if CCP1_MODULE_SELECTED == CCP1_MODULE_COMPARE_MODE_CFG || CCP2_MODULE_SELECTED == CCP2_MODULE_COMPARE_MODE_CFG
Std_ReturnType compare_is_Complete(const ccp_t *_ccp ,uint8 *statue);
Std_ReturnType compare_set_value(const ccp_t *_ccp ,uint16 capture_value);
#endif
/* section interfaces declarations*/
#endif	/* HAL_CCP_H */

