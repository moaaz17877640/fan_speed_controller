/* 
 * File:   hal_timer1.h
 * Author: MOAAZ
 *
 * Created on March 6, 2024, 3:26 PM
 */
#include "hal_timer1.h"
/**
 *  @breif : initliaze timer1 module
 * @param TMR
 * @return status of execute ...
 */
static volatile uint16 preload_value = ZERO_INIT;

static inline void MODE_configure(const Timer1_t *TMR );
static inline void register_configure(const Timer1_t *TMR );
static inline void OSC_configure(const Timer1_t *TMR );

static void (*TIMER1_INTERRUPPT_HANDLERF)(void)= NULL;



Std_ReturnType TMR1_Init(const Timer1_t *TMR){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == TMR){
        ret =E_NOT_OK ;
    }else 
    {
    // disable module
        TIMER1_MODULE_DISABLE();
        MODE_configure(TMR);
        register_configure(TMR);
        OSC_configure(TMR);
        TIMER1_PRESCALER_CONFIGURE(TMR->Prescaler_value);
        TMR1H = ((TMR->timer1_preload_value)>>8);
        TMR1L = (uint8)(TMR->timer1_preload_value);
        preload_value= TMR->timer1_preload_value ; 
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_CLEAR_FLAG();
        TIMER1_INTERRUPPT_HANDLERF = TMR->TIMER1_INTERRUPT_HANDLER ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == TMR->timer1_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
           TIMER1_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY ==  TMR->timer1_priority){ 
           INTERRUPT_GlobalInterruptLowEnable();
           TIMER1_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
#endif 
        TIMER1_MODULE_ENABLE();
    }
    return ret ; 
}
Std_ReturnType TMR1_DEInit(const Timer1_t *TMR){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == TMR){
        ret =E_NOT_OK ;
    }else 
    {
      TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
      TIMER1_INTERRUPT_DISABLE() ;
#endif
    
    
    }
    return ret ; 

}
Std_ReturnType TMR1_Write_value(const Timer1_t *TMR , uint16 value){

    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == TMR){
        ret =E_NOT_OK ;
    }else 
    {
       TMR1H = ((value)>>8);
       TMR1L = (uint8)(value);
    
    
    }
    return ret ; 

}
Std_ReturnType TMR1_Read_value(const Timer1_t *TMR , uint16 *value){
  Std_ReturnType ret = E_NOT_OK ; 
  uint8 l_tmr =ZERO_INIT ,h_tmr = ZERO_INIT ;
    if((NULL == TMR)&& (NULL == value)){
        ret =E_NOT_OK ;
    }else 
    {
      l_tmr =TMR1L ; 
      h_tmr =TMR1H;
    *value = (uint16)((h_tmr << 8 ) + l_tmr) ; 
    
    
    }
    return ret ; 
}
void TMR1_ISR(void){
    TIMER1_CLEAR_FLAG();
     TMR1H = ((preload_value)>>8);
       TMR1L = (uint8)(preload_value);
    if(TIMER1_INTERRUPPT_HANDLERF)
    {TIMER1_INTERRUPPT_HANDLERF();
    }else{
    //nothing  
    }

}
static inline void MODE_configure(const Timer1_t *TMR ){ 
    if(TIMER1_COUNTER_MODE_CFG == TMR->timer1_mode)
    {
    TIMER1_MODE_COUNTER();
     if(TIMER1_SYNCHRONOUS_mode == TMR->counter_mode){
    TIMER1_SYNCHRONOUS_EXTERNAL_CLOCK() ;
    }
    else if(TIMER1_ASYNCHRONOUS_mode == TMR->counter_mode){
     TIMER1_ASYNCHRONOUS_EXTERNAL_CLOCK() ;
    }else{
    //nothing
    }
    } 
    else if(TIMER1_TIMER_MODE_CFG == TMR->timer1_mode)
    {
    TIMER1_MODE_TIMER();
    }
    else {/*nothing *** */}
}
static inline void register_configure(const Timer1_t *TMR ){
    if(TIMER1_16_RW_reg  == TMR->timer1_register_size){
    TIMER1_ENABLE_16BIT_RD() ;
    }else if(TIMER1_8_RW_reg  == TMR->timer1_register_size){
    TIMER1_ENABLE_8BIT_RD() ;
    }else {
    //nothing ...
    }

}
static inline void OSC_configure(const Timer1_t *TMR ){
    if(TIMER1_Enable_osc_cfg == TMR->timer1_osc_cfg){
        TIMER1_OSCILLATOR_ENABLE();
    
    }else  if(TIMER1_Disable_osc_cfg == TMR->timer1_osc_cfg){
    TIMER1_OSCILLATOR_DISABLE();
    }
    else {
    //nothing
    }

}
void timer1_clear_flag(void){
TIMER1_CLEAR_FLAG();
}
Std_ReturnType timer1_flag_statue(void){
    return PIR1bits.TMR1IF ;
}