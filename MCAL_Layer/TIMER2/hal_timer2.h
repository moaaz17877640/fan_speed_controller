/* 
 * File:   hal_timer2.h
 * Author: MOAAZ
 *
 * Created on March 8, 2024, 11:23 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/* include section */
#include "../proc/pic18f4620.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
/*macro function declaration*/
#define TIMER2_enable_cfg       1
#define TIMER2_disable_cfg      0


#define TIMER2_MODULE_ENABLE() (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE() (T2CONbits.TMR2ON = 0)
#define TIMER2_PRESCALER_CONFIGURE(_CONFIG) (T2CONbits.T2CKPS =_CONFIG)
#define TIMER2_POSTSCALER_CONFIGURE(_CONFIG) (T2CONbits.TOUTPS =_CONFIG)

/* datatype declaration*/
typedef enum{
    TIMER2_PRESCALER_DIV_1,
             TIMER2_PRESCALER_DIV_4,
             TIMER2_PRESCALER_DIV_16,
}timer2_prescaler_value;
typedef enum{
    TIMER2_POSTSCALER_DIV_1,
            TIMER2_POSTSCALER_DIV_2,
            TIMER2_POSTSCALER_DIV_3,
            TIMER2_POSTSCALER_DIV_4 ,
            TIMER2_POSTSCALER_DIV_5 ,
            TIMER2_POSTSCALER_DIV_6 ,
            TIMER2_POSTSCALER_DIV_7 ,
            TIMER2_POSTSCALER_DIV_8 ,
            TIMER2_POSTSCALER_DIV_9 ,
            TIMER2_POSTSCALER_DIV_10 ,
            TIMER2_POSTSCALER_DIV_11 ,
            TIMER2_POSTSCALER_DIV_12 ,
            TIMER2_POSTSCALER_DIV_13 ,
            TIMER2_POSTSCALER_DIV_14 ,
            TIMER2_POSTSCALER_DIV_15 ,
            TIMER2_POSTSCALER_DIV_16            
}timer2_postscaler_value;
typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER2_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg timer2_priority ;
#endif
 timer2_prescaler_value prescaler_valu ;
timer2_postscaler_value postscaler_valu;
 uint8 preload_value           ;
 }Timer2_t;
 
 /*interfaces section*/
 Std_ReturnType TMR2_Init(const Timer2_t *TMR);
Std_ReturnType TMR2_DEInit(const Timer2_t *TMR);
Std_ReturnType TMR2_Write_value(const Timer2_t *TMR , uint8 value);
Std_ReturnType TMR2_Read_value(const Timer2_t *TMR , uint8 *value);
#endif	/* HAL_TIMER2_H */

