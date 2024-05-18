/* 
 * File:   hal_timer1.h
 * Author: MOAAZ
 *
 * Created on March 6, 2024, 3:26 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/*INclude sectiON */
#include "../proc/pic18f4620.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_gen_cfg.h"
/* timer1 configure defines*/
#define TIMER1_COUNTER_MODE_CFG                1
#define TIMER1_TIMER_MODE_CFG                  0
#define TIMER1_Enable_osc_cfg                  1
#define TIMER1_Disable_osc_cfg                 0
#define TIMER1_16_RW_reg                       1
#define TIMER1_8_RW_reg                        0
#define TIMER1_SYNCHRONOUS_mode                0
#define TIMER1_ASYNCHRONOUS_mode               1


#define TIMER1_CLOCK_SYSTEM_STATUS()    (T1CONbits.T1RUN)

 /* Marco function definition*/ 
#define TIMER1_ENABLE_16BIT_RD()   (T1CONbits.RD16 = 1)
#define TIMER1_ENABLE_8BIT_RD()   (T1CONbits.RD16 = 0)
#define TIMER1_OSCILLATOR_ENABLE() (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_DISABLE() (T1CONbits.T1OSCEN = 0)
#define TIMER1_MODE_COUNTER() (T1CONbits.TMR1CS = 1 )
#define TIMER1_MODE_TIMER() (T1CONbits.TMR1CS = 0 )
#define TIMER1_MODULE_ENABLE() (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE() (T1CONbits.TMR1ON = 0)
#define TIMER1_SYNCHRONOUS_EXTERNAL_CLOCK() (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNCHRONOUS_EXTERNAL_CLOCK() (T1CONbits.T1SYNC = 1)
#define TIMER1_PRESCALER_CONFIGURE(_CONFIG) (T1CONbits.T1CKPS = _CONFIG)
/*datatype declarition  */
typedef enum{
 TIMER1_PRESCALER_DIV_1,
             TIMER1_PRESCALER_DIV_2,
             TIMER1_PRESCALER_DIV_4,
             TIMER1_PRESCALER_DIV_8,
}Timer1_Prescaler_select_t;
typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER1_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg timer1_priority ;
#endif
Timer1_Prescaler_select_t Prescaler_value ;
uint16     timer1_preload_value          ;
uint8      timer1_mode                 : 1;
uint8      timer1_osc_cfg                : 1; // enable timer osc or disable
uint8      timer1_register_size        : 1; 
uint8      counter_mode                :1 ; // asynchron or synchr
uint8      timer1_reserved             : 4;
}Timer1_t;

/* -------------------------software interfaces declaration--------------------*/
/**
 * 
 * @param TMR
 * @return 
 */
Std_ReturnType TMR1_Init(const Timer1_t *TMR);
/**
 * 
 * @param TMR
 * @return 
 */
Std_ReturnType TMR1_DEInit(const Timer1_t *TMR);
/**
 * 
 * @param TMR
 * @param value
 * @return 
 */
Std_ReturnType TMR1_Write_value(const Timer1_t *TMR , uint16 value);
/**
 * 
 * @param TMR
 * @param value
 * @return 
 */
Std_ReturnType TMR1_Read_value(const Timer1_t *TMR , uint16 *value);
/**
 * 
 * 
 */
void timer1_clear_flag(void);
/**
 * 
 * @return  flag status -> e_ok (cleared)
 */
Std_ReturnType timer1_flag_statue(void);
#endif	/* HAL_TIMER1_H */

