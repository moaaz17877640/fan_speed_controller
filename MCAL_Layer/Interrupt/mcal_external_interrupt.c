/* 
 * File:   mcal_external_interrupt.c
 * Author: Moaaz elmahi
 *
 * Created on 02 August 2023, 20:26
 */


#include "mcal_external_interrupt.h"


/* pointer to function hilding callback function */
static InterruptHandeler INT0_InterruptHandeler = NULL;
static InterruptHandeler INT1_InterruptHandeler = NULL;
static InterruptHandeler INT2_InterruptHandeler = NULL;

static InterruptHandeler RB4_InterruptHandeler_High = NULL;
static InterruptHandeler RB4_InterruptHandeler_Low = NULL;
static InterruptHandeler RB5_InterruptHandeler_High = NULL;
static InterruptHandeler RB5_InterruptHandeler_Low = NULL;
static InterruptHandeler RB6_InterruptHandeler_High = NULL;
static InterruptHandeler RB6_InterruptHandeler_Low = NULL;
static InterruptHandeler RB7_InterruptHandeler_High = NULL;
static InterruptHandeler RB7_InterruptHandeler_Low = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *init_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *init_obj);
static Std_ReturnType Interrupt_INTx_Priority_init(const interrupt_INTx_t *init_obj);
static Std_ReturnType Interrupt_INTx_Edge_init(const interrupt_INTx_t *init_obj);
static Std_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx_t *init_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *init_obj);

static Std_ReturnType INT0_SetInterruptHandeler(void (*InterruptHandeler)(void));
static Std_ReturnType INT1_SetInterruptHandeler(void (*InterruptHandeler)(void));
static Std_ReturnType INT2_SetInterruptHandeler(void (*InterruptHandeler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandeler(const interrupt_INTx_t *init_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *init_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *init_obj);
static Std_ReturnType Interrupt_RBx_Priority_init(const interrupt_RBx_t *init_obj);
static Std_ReturnType Interrupt_RBx_Pin_init(const interrupt_RBx_t *init_obj);


/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        ret = Interrupt_INTx_Disable(init_obj);
        /*clear interrupt flag */
        ret |= Interrupt_INTx_Clear_Flag(init_obj);
        /* Configure the external interrupt edge */
        ret |= Interrupt_INTx_Edge_init(init_obj);
        /* Configure the external interrupt I/O pins */
        ret |= Interrupt_INTx_Pin_init(init_obj);
        /* Configure default interrupt callback */
        ret |= Interrupt_INTx_SetInterruptHandeler(init_obj);
        /* Enable the external interrupt */
        ret |= Interrupt_INTx_Enable(init_obj);
    }
    return ret;
}
 
/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(init_obj);
        ret= Interrupt_INTx_Clear_Flag(init_obj);
    }
    return ret;
}

/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_Interrupt_Disable();
         
        EXT_RBx_Interrupt_Flag_Clear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(init_obj->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowEnable();
                EXT_RBx_PriorityLow(); 
            }
            else if(init_obj->priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GlobalInterruptHighEnable();
                EXT_RBx_PriorityHigh();
            } 
            else{
                /* Nothing */
            }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif    /* Intialize the RBx direction to be input  */
            gpio_pin_direction_intialize(&(init_obj->mcu_pin));
            /* Intialize the callback function */
            switch(init_obj->mcu_pin.pin){
                case PIN4:
                    RB4_InterruptHandeler_High = init_obj->EXT_InterruptHandler_High;
                    RB4_InterruptHandeler_Low = init_obj->EXT_InterruptHandler_Low;
                    break;
                case PIN5:
                    RB5_InterruptHandeler_High = init_obj->EXT_InterruptHandler_High;
                    RB5_InterruptHandeler_Low = init_obj->EXT_InterruptHandler_Low;
                    break;
                case PIN6:
                    RB6_InterruptHandeler_High = init_obj->EXT_InterruptHandler_High;
                    RB6_InterruptHandeler_Low = init_obj->EXT_InterruptHandler_Low;
                    break;
                case PIN7:
                    RB7_InterruptHandeler_High = init_obj->EXT_InterruptHandler_High;
                    RB7_InterruptHandeler_Low = init_obj->EXT_InterruptHandler_Low;
                    break;
                    
                default : ret = E_NOT_OK;
            }
        EXT_RBx_Interrupt_Enable();
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param init_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_Interrupt_Disable();
        EXT_RBx_Interrupt_Flag_Clear();
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
     switch(init_obj->src){
        case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_GlobalInterruptHighEnable();
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
             
            EXT_INT0_Interrupt_Enable();
            ret = E_OK;
            break;
        case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(init_obj->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else if(init_obj->priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GlobalInterruptHighEnable();
            } 
            else{
                /* Nothing */
            }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
            EXT_INT1_Interrupt_Enable();
            ret = E_OK;
            break;
        case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(init_obj->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else if(init_obj->priority == INTERRUPT_HIGH_PRIORITY){
                 INTERRUPT_GlobalInterruptHighEnable();
            } 
            else{
                /* Nothing */
            }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
            EXT_INT2_Interrupt_Enable();
            ret = E_OK;
            break;
        default :ret = E_NOT_OK; 
     }   
    }
    return ret;   
}


static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(init_obj->src){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_Interrupt_Disable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_Interrupt_Disable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_Interrupt_Disable();
                ret = E_OK;
                break;
            default :ret = E_NOT_OK; 
        }
    }
    return ret; 
}


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_init(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(init_obj->src){
            case INTERRUPT_EXTERNAL_INT1:
                if(init_obj->priority == INTERRUPT_LOW_PRIORITY){
                     EXT_INT1_LowPrioritySet();
                }
                else if(init_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    EXT_INT1_HighPrioritySet();
                } 
                else{
                    /* Nothing */
                }
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(init_obj->priority == INTERRUPT_LOW_PRIORITY){
                    EXT_INT2_LowPrioritySet();
                }
                else if(init_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    EXT_INT2_HighPrioritySet();
                } 
                else{
                    /* Nothing */
                }
                ret = E_OK;
                break;   
            default : ret = E_NOT_OK;          
        }
    }
    return ret;
}
#endif
 
static Std_ReturnType Interrupt_INTx_Edge_init(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(init_obj->src){
            case INTERRUPT_EXTERNAL_INT0:
                if(INTERRUPT_FALLING_EDGE == init_obj->edge){
                    EXT_INT0_FallingEdgeSet();
                }
                else if(INTERRUPT_RAISING_EDGE == init_obj->edge){
                    EXT_INT0_RaisingEdgeSet();
                }
                else{
                    /* Nothing */
                }
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_FALLING_EDGE == init_obj->edge){
                    EXT_INT1_FallingEdgeSet();
                }
                else if(INTERRUPT_RAISING_EDGE == init_obj->edge){
                    EXT_INT1_RaisingEdgeSet();
                }
                else{
                    /* Nothing */
                }
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_FALLING_EDGE == init_obj->edge){
                    EXT_INT2_FallingEdgeSet();
                }
                else if(INTERRUPT_RAISING_EDGE == init_obj->edge){
                    EXT_INT2_RaisingEdgeSet();
                }
                else{
                    /* Nothing */
                }
                ret = E_OK;
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret; 
}
 

static Std_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(init_obj->mcu_pin));
    }
    return ret;
}


static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_Interrupt_Enable();
    }
    return ret;
}

static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_Interrupt_Disable();
    }
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_RBx_Priority_init(const interrupt_RBx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        if(init_obj->priority == INTERRUPT_HIGH_PRIORITY){
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_PriorityHigh();
           ret = E_OK;
        }
        else if(init_obj->priority == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_PriorityLow();
            ret = E_OK;
        }
        else{ ret = E_NOT_OK; }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_RBx_Pin_init(const interrupt_RBx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(init_obj->mcu_pin));
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
      switch(init_obj->src){
        case INTERRUPT_EXTERNAL_INT0:
            EXT_INT0_Interrupt_Flag_Clear();
            ret = E_OK;
            break;
        case INTERRUPT_EXTERNAL_INT1:
            EXT_INT1_Interrupt_Flag_Clear();
            ret = E_OK;
            break;
        case INTERRUPT_EXTERNAL_INT2:
            EXT_INT2_Interrupt_Flag_Clear();
            ret = E_OK;
            break;
        default :ret = E_NOT_OK;/* Nothing */
     }   
    }
    return ret;
}


static Std_ReturnType INT0_SetInterruptHandeler(void (*InterruptHandeler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandeler){
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandeler = InterruptHandeler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandeler(void (*InterruptHandeler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandeler){
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandeler = InterruptHandeler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandeler(void (*InterruptHandeler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandeler){
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandeler = InterruptHandeler;
        ret = E_OK;
    }
    return ret;
}


static Std_ReturnType Interrupt_INTx_SetInterruptHandeler(const interrupt_INTx_t *init_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == init_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(init_obj->src){
            case INTERRUPT_EXTERNAL_INT0:
                ret = INT0_SetInterruptHandeler(init_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                ret = INT1_SetInterruptHandeler(init_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2:
                ret = INT2_SetInterruptHandeler(init_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

void INT0_ISR(void){
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_Interrupt_Flag_Clear();
    /* Code */
    
    /* Callback function */
    if(INT0_InterruptHandeler){
        INT0_InterruptHandeler();
    }
}

void INT1_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_Interrupt_Flag_Clear();
    /* Code */
    
    /* Callback function */
    if(INT1_InterruptHandeler){
        INT1_InterruptHandeler();
    }
    else{
        /* Nothing */
    }
}

void INT2_ISR(void){
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_Interrupt_Flag_Clear();
    /* Code */
    
    /* Callback function */
    if(INT2_InterruptHandeler){
        INT2_InterruptHandeler();
    }
    else{
        /* Nothing */
    }
}

void RB4_ISR(uint8 RB4_source){
    /* The RB4 external interrupt occurred (must be cleared in software) */
    EXT_RBx_Interrupt_Flag_Clear();
    
    if(0 == RB4_source){
        if(RB4_InterruptHandeler_High){
            RB4_InterruptHandeler_High();
        }
        else{
            /* Nothing */
        }
    }
    else if(1 == RB4_source){
        if(RB4_InterruptHandeler_Low){
            RB4_InterruptHandeler_Low();
        }
        else{
            /* Nothing */
        }
    }
    else{
            /* Nothing */
        }
    
}
void RB5_ISR(uint8 RB5_source){
    /* The RB5 external interrupt occurred (must be cleared in software) */
    EXT_RBx_Interrupt_Flag_Clear();
    
    if(0 == RB5_source){
        if(RB5_InterruptHandeler_High){
            RB5_InterruptHandeler_High();
        }
        else{
            /* Nothing */
        }
    }
    else if(1 == RB5_source){
        if(RB5_InterruptHandeler_Low){
            RB5_InterruptHandeler_Low();
        }
        else{
            /* Nothing */
        }
    }
    else{
            /* Nothing */
        }
}
void RB6_ISR(uint8 RB6_source){
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_Interrupt_Flag_Clear();
    
    if(0 == RB6_source){
        if(RB6_InterruptHandeler_High){
            RB6_InterruptHandeler_High();
        }
        else{
            /* Nothing */
        }
    }
    else if(1 == RB6_source){
        if(RB6_InterruptHandeler_Low){
            RB6_InterruptHandeler_Low();
        }
        else{
            /* Nothing */
        }
    }
    else{
            /* Nothing */
        }
}
void RB7_ISR(uint8 RB7_source){
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_Interrupt_Flag_Clear();
    
    if(0 == RB7_source){
        if(RB7_InterruptHandeler_High){
            RB7_InterruptHandeler_High();
        }
        else{
            /* Nothing */
        }
    }
    else if(1 == RB7_source){
        if(RB7_InterruptHandeler_Low){
            RB7_InterruptHandeler_Low();
        }
        else{
            /* Nothing */
        }
    }
    else{
            /* Nothing */
        }
}
