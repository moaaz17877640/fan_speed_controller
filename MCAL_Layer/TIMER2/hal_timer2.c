#include "hal_timer2.h"
void (*TMR2_INTERRUPT_HANDLER)(void) = NULL;
static volatile uint8 preload_val = ZERO_INIT ;
 Std_ReturnType TMR2_Init(const Timer2_t *TMR){
     Std_ReturnType ret = E_OK ;
     if(NULL == TMR)
     {
         ret= E_NOT_OK;
     }else{
         TIMER2_MODULE_DISABLE();
        TMR2 = TMR->preload_value;
        preload_val =TMR->preload_value;
        TIMER2_PRESCALER_CONFIGURE(TMR->prescaler_valu);
        TIMER2_POSTSCALER_CONFIGURE(TMR->postscaler_valu);
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == TMR->timer2_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
           TIMER2_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY ==  TMR->timer2_priority){ 
              INTERRUPT_GlobalInterruptLowEnable();
           TIMER2_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
         INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();

#endif
        TMR2_INTERRUPT_HANDLER = TMR->TIMER2_INTERRUPT_HANDLER;
#endif
        TIMER2_MODULE_ENABLE();
     
     }
     return ret ;
 }
Std_ReturnType TMR2_DEInit(const Timer2_t *TMR){
     Std_ReturnType ret = E_OK ;
     if(NULL == TMR)
     {
     }else{
     TIMER2_MODULE_ENABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     TIMER2_INTERRUPT_DISABLE();
#endif
     
     }
     return ret ;
 }
Std_ReturnType TMR2_Write_value(const Timer2_t *TMR , uint8 value){
     Std_ReturnType ret = E_OK ;
     if(NULL == TMR)
     {
     }else{
     TMR2 = value;
     
     }
     return ret ;
 }
Std_ReturnType TMR2_Read_value(const Timer2_t *TMR , uint8 *value){
     Std_ReturnType ret = E_OK ;
     if(NULL == TMR)
     {
     }else{
     *value = TMR2;
     
     }
     return ret ;
 }
void TMR2_ISR(void){
    TIMER2_CLEAR_FLAG();
    TMR2 = preload_val ;
    if(TMR2_INTERRUPT_HANDLER){
    TMR2_INTERRUPT_HANDLER();
    }else{
    //nothjng 
    }


}