/* 
 * File:   hal_timer0.C
 * Author: MOAAZ
 *
 * Created on March 1, 2024, 11:52 AM
 */
#include "hal_timer0.h"
#define MOAZ_TMR (HWREG8(0xFD7))
static volatile uint16 preload_value = ZERO_INIT;
static inline void Prescaler_configure(const Timer0_t *TMR );
static inline void MODE_configure(const Timer0_t *TMR );

static inline void register_configure(const Timer0_t *TMR );
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_INTERRUPPT)(void)= NULL;
#endif
Std_ReturnType TMR0_Init(const Timer0_t *TMR){
    Std_ReturnType ret =E_NOT_OK ;
    if(NULL == TMR)
    {
    ret =E_NOT_OK ;
    }else{
    /* disable module --> configure  --> enable */
        TIMER0_DISABLE();
        Prescaler_configure(TMR); 
         MODE_configure(TMR);
         register_configure(TMR);
         
        // 0000 0000 1100 1100   
         TMR0L = (uint8)((TMR->timer0_preload_value)) ;
         TMR0H =((TMR->timer0_preload_value)>> 8);
   
         
        preload_value = TMR->timer0_preload_value ;
       
       
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_CLEAR_FLAG();
        TIMER0_INTERRUPPT = TMR->TIMER0_INTERRUPT_HANDLER ;
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == TMR->timer0_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
           TIMER0_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY ==  TMR->timer0_priority){ 
              INTERRUPT_GlobalInterruptLowEnable();
           TIMER0_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
       
        
#endif
        
        TIMER0_ENABLE();
    }
    return  ret;
}
Std_ReturnType TMR0_DEInit(const Timer0_t *TMR){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == TMR){
    
    }else {
    TIMER0_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE_CFG == INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_DISABLE();
#endif
    ret = E_OK;
    } 
   return ret; 
}
Std_ReturnType TMR0_Write_value(const Timer0_t *TMR , uint16 value){
 Std_ReturnType ret = E_NOT_OK ;
    if(NULL == TMR){
    
    }else {
        ret = E_OK;
        TMR0H = ( value>> 8);// 0000 0000 1100 1100  
        TMR0L = (uint8)(value);
    } 
   return ret;
}
Std_ReturnType TMR0_Read_value(const Timer0_t *TMR , uint16 *value){
 Std_ReturnType ret = E_NOT_OK ;
 uint8 l_tmr0 =ZERO_INIT , h_tmr0 =ZERO_INIT ;  
    if((NULL == TMR)||(NULL == value)){
    
    }else {
        l_tmr0 = TMR0L ; 
        h_tmr0 = TMR0H ; 
         *value = (uint16)((h_tmr0 << 8) + l_tmr0  ); 
        ret = E_OK;
    } 
   return ret;
}

static inline void Prescaler_configure(const Timer0_t *TMR ){
    if(TIMER0_PRESCALER_ENABLE_CFG == TMR->Prescaler_enable){
    TIMER0_PRESCALER_ENABLE();
    T0CONbits.T0PS = TMR->Prescaler_value ;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == TMR->Prescaler_enable){
    TIMER0_PRESCALER_DISABLE();
    }
    else {
    /* **nothing*** */
    }

}
static inline void MODE_configure(const Timer0_t *TMR ){ 
    if(TIMER0_TIMER_CFG ==TMR->timer0_mode)
    {
    TIMER0_TIMER_MODE();
    } 
    else if(TIMER0_COUNTER_CFG ==TMR->timer0_mode)
    {
    TIMER0_COUNTER_MODE();
     if(TIMER0_FILLING_EDGE_CFG ==TMR->counter_edge)
    {
    TIMER0_FALLING_EDGE();
    } 
    else if(TIMER0_RISING_EDGE_CFG ==TMR->counter_edge)
    {
    TIMER0_RAISING_EDGE();
    }
    else{
    /*nothing*/
    }
    }
    else {/*nothing *** */}
}

    static inline void register_configure(const Timer0_t *TMR ){
    if(TIMER0_16BIT_CFG  == TMR->timer_register_size){
    TIMER0_CONFIGURE_16BIT() ;
    }else if(TIMER0_8BIT_CFG  == TMR->timer_register_size){
    TIMER0_CONFIGURE_8BIT() ;
    }else {
    //nothing ...
    }

}
void TMR0_ISR(void){
    TIMER0_CLEAR_FLAG(); 
    TMR0H = (preload_value >> 8);
    TMR0L =(uint8)(preload_value);
 
if(TIMER0_INTERRUPPT){
     TIMER0_INTERRUPPT();
}
else{
/*   **Nothing****   */
}
}