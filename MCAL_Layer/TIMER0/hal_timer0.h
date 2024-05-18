/* 
 * File:   hal_timer0.h
 * Author: MOAAZ
 *
 * Created on March 1, 2024, 11:52 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*INCLUDE SECTION */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

#include "../../MCAL_Layer/Interrupt/mcal_interrupt_manager.h"

#define TIMER0_8BIT_CFG                   1
#define TIMER0_16BIT_CFG                  0
#define TIMER0_COUNTER_CFG                1
#define TIMER0_TIMER_CFG                  0
#define TIMER0_PRESCALER_ENABLE_CFG       1
#define TIMER0_PRESCALER_DISABLE_CFG      0
#define TIMER0_RISING_EDGE_CFG            0
#define TIMER0_FILLING_EDGE_CFG           1  


/* Marco function definition*/
#define TIMER0_INTERRUPT_FEATURE_ENABLE_CFG   INTERRUPT_FEATURE_ENABLE
#define TIMER0_ENABLE()       (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()    (T0CONbits.TMR0ON = 0)
#define TIMER0_CONFIGURE_8BIT()    (T0CONbits.T08BIT = 1)
#define TIMER0_CONFIGURE_16BIT()    (T0CONbits.T08BIT = 0)
#define TIMER0_RAISING_EDGE()         (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE()      (T0CONbits.T0SE = 1)
#define TIMER0_PRESCALER_ENABLE()     (T0CONbits.PSA = 1 )
#define TIMER0_PRESCALER_DISABLE()     (T0CONbits.PSA = 0 )
#define TIMER0_TIMER_MODE()    (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE()     (T0CONbits.T0CS = 1)


/*datatype declarition  */
typedef enum{
    PRESCALER_DIV_2,
             PRESCALER_DIV_4,
             PRESCALER_DIV_8,
             PRESCALER_DIV_16,
             PRESCALER_DIV_32,
             PRESCALER_DIV_64,
             PRESCALER_DIV_128,
             PRESCALER_DIV_256
}Timer0_Prescaler_select_t;
typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER0_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg timer0_priority ;
#endif    
Timer0_Prescaler_select_t Prescaler_value ;
uint8      Prescaler_enable            : 1;
uint8      timer0_mode                 : 1;
uint8      counter_edge                : 1;
uint8      timer_register_size         : 1; 
uint8      timer0_reserved             : 4;
uint16     timer0_preload_value;
}Timer0_t;
/* -------------------------software interfaces declaration--------------------*/
    Std_ReturnType TMR0_Init(const Timer0_t *TMR);
    Std_ReturnType TMR0_DEInit(const Timer0_t *TMR);
    Std_ReturnType TMR0_Write_value(const Timer0_t *TMR , uint16 value);
    Std_ReturnType TMR0_Read_value(const Timer0_t *TMR , uint16 *value);
#endif	/* HAL_TIMER0_H */

