/* 
 * File:   hal_timer3.h
 * Author: MOAAZ
 *
 * Created on March 10, 2024, 7:53 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H
/*includes section*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
/*configuration defines*/
#define TIMER3_enable_cfg    1
#define TIMER3_disable_cfg    0
#define TIMER3_counter_mode_cfg     1
#define TIMER3_timer_mode_cfg       0
#define TIMER3_rd_8bit_cfg         0
#define TIMER3_rd_16bit_cfg         1
#define TIMER3_SYNCHRONOUS_mode                0
#define TIMER3_ASYNCHRONOUS_mode               1
/*macro declaration*/
#define TIMER3_INTERRUPT_FEATURE_ENABLE_CFG   INTERRUPT_FEATURE_ENABLE
#define TIMER3_MODULE_ENABLE()       (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()    (T3CONbits.TMR3ON = 0)
#define TIMER3_8BIT_RW()    (T3CONbits.RD16 = 0)
#define TIMER3_16BIT_RW()    (T3CONbits.RD16 = 1)
#define TIMER3_SYNCHRONOUS_EXTERNAL_CLOCK() (T3CONbits.T3SYNC=0 )
#define TIMER3_ASYNCHRONOUS_EXTERNAL_CLOCK() (T3CONbits.T3SYNC=1)
#define TIMER3_TIMER_MODE()    (T3CONbits.TMR3CS =0)
#define TIMER3_COUNTER_MODE()     (T3CONbits.TMR3CS =1)
#define TIMER3_CONFIGURE_PRESCALER(_CONFIG) (T3CONbits.T3CKPS = _CONFIG)



typedef enum{
 TIMER3_PRESCALER_DIV_1,
             TIMER3_PRESCALER_DIV_2,
             TIMER3_PRESCALER_DIV_4,
             TIMER3_PRESCALER_DIV_8,
}Timer3_Prescaler_select_t;

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER3_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg timer3_priority ;
#endif
Timer3_Prescaler_select_t Prescaler_value ;
uint16     timer3_preload_value          ;
uint8      timer3_mode                 : 1;
uint8      timer3_register_size        : 1; 
uint8      counter_mode                : 1 ; // asynchron or synchr
uint8      timer3_reserved             : 5;
}Timer3_t;

/* -------------------------software interfaces declaration--------------------*/
Std_ReturnType TMR3_Init(const Timer3_t *TMR);
Std_ReturnType TMR3_DEInit(const Timer3_t *TMR);
Std_ReturnType TMR3_Write_value(const Timer3_t *TMR , uint16 value);
Std_ReturnType TMR3_Read_value(const Timer3_t *TMR , uint16 *value);
#endif	/* HAL_TIMER3_H */

