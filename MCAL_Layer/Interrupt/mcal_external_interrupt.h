/* 
 * File:   mcal_external_interrupt.h
 * Author: Moaaz elmahi
 *
 * Created on 02 August 2023, 20:26
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H


/************************ Includes ************************/
#include "mcal_interrupt_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "mcal_interrupt_manager.h"


/************************  Macro Declaration ************************/
 

/************************  Macro Function Declaration ************************/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clear interrupt disable for the external interrupts , INT0 */
#define EXT_INT0_Interrupt_Disable()             (INTCONbits.INT0IE = 0)
/* this routine sets interrupt enable for the external interrupts , INT0 */
#define EXT_INT0_Interrupt_Enable()              (INTCONbits.INT0IE = 1)
/* this routine clear interrupt flag for the external interrupts , INT0 */
#define EXT_INT0_Interrupt_Flag_Clear()          (INTCONbits.INT0IF = 0)
/* this routine sets the edge detect of the extern interrupts to negative edge */
#define EXT_INT0_RaisingEdgeSet()                (INTCON2bits.INTEDG0 = 1)
/* this routine sets the edge detect of the extern interrupts to positive edge */
#define EXT_INT0_FallingEdgeSet()               (INTCON2bits.INTEDG0 = 0)

/* this routine clear interrupt enable for the external interrupts , INT1 */
#define EXT_INT1_Interrupt_Disable()             (INTCON3bits.INT1IE = 0)
/* this routine sets interrupt enable for the external interrupts , INT1 */
#define EXT_INT1_Interrupt_Enable()              (INTCON3bits.INT1IE = 1)
/* this routine clear interrupt flag for the external interrupts , INT2 */
#define EXT_INT1_Interrupt_Flag_Clear()          (INTCON3bits.INT1IF = 0)
/* this routine sets the edge detect of the extern interrupts to negative edge */
#define EXT_INT1_RaisingEdgeSet()                (INTCON2bits.INTEDG1 = 1)
/* this routine sets the edge detect of the extern interrupts to positive edge */
#define EXT_INT1_FallingEdgeSet()                (INTCON2bits.INTEDG1 = 0)

/* this routine clear interrupt enable for the external interrupts , INT2 */
#define EXT_INT2_Interrupt_Disable()             (INTCON3bits.INT2IE = 0)
/* this routine sets interrupt enable for the external interrupts , INT2 */
#define EXT_INT2_Interrupt_Enable()              (INTCON3bits.INT2IE = 1)
/* this routine clear interrupt flag for the external interrupts , INT */
#define EXT_INT2_Interrupt_Flag_Clear()          (INTCON3bits.INT2IF = 0)
/* this routine sets the edge detect of the extern interrupts to negative edge */
#define EXT_INT2_RaisingEdgeSet()                (INTCON2bits.INTEDG2 = 1)
/* this routine sets the edge detect of the extern interrupts to positive edge */
#define EXT_INT2_FallingEdgeSet()                (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine set the INT1 external interrupt priority to be high priority */
#define EXT_INT1_HighPrioritySet()      (INTCON3bits.INT1P = 1)
/* this routine set the INT1 external interrupt priority to be low priority */
#define EXT_INT1_LowPrioritySet()       (INTCON3bits.INT1P = 0)

/* this routine set the INT2 external interrupt priority to be high priority */
#define EXT_INT2_HighPrioritySet()      (INTCON3bits.INT2P = 1)
/* this routine set the INT2 external interrupt priority to be low priority */
#define EXT_INT2_LowPrioritySet()       (INTCON3bits.INT2P = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_onChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clear interrupt enable for the external interrupts , RB0 */
#define EXT_RBx_Interrupt_Disable()             (INTCONbits.RBIE = 0)
/* this routine set interrupt enable for the external interrupts , RB0 */
#define EXT_RBx_Interrupt_Enable()              (INTCONbits.RBIE = 1)
/* this routine clear interrupt flag for the external interrupts , RB0 */
#define EXT_RBx_Interrupt_Flag_Clear()          (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine set the RBx External Interrupt Priority to be High priority */
#define EXT_RBx_PriorityHigh()                  (INTCON2bits.RBIP = 1)
/* This routine set the RBx External Interrupt Priority to be Low priority */
#define EXT_RBx_PriorityLow()                   (INTCON2bits.RBIP = 0)

#endif

#endif

/************************  Data Type Declaration ************************/
typedef void (* InterruptHandeler)(void);

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RAISING_EDGE,
            
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,        
}interrupt_INTx_src;

typedef struct{
    void (* EXT_InterruptHandler)(void); 
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src src;
    interrupt_priority_cfg priority;
}interrupt_INTx_t; 
     
typedef struct{
    void (* EXT_InterruptHandler_High)(void); 
    void (* EXT_InterruptHandler_Low)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

/************************  Software interface Declaration ************************/

/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *init_obj);
/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *init_obj);
/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *init_obj);
/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *init_obj);



#endif	/* MCAL_EXTERNAL_INTERRUPT_H */


