#include "hal_timer3.h" 
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (*TIMER3_INTERRUPT_HANDLERF )(void) = NULL ;
#endif
 static volatile uint16 preload_vall= ZERO_INIT ;  
 static inline void configue_timer_mode(const Timer3_t *TMR);
 static inline void register_configure(const Timer3_t *TMR );
 
 
Std_ReturnType TMR3_Init(const Timer3_t *TMR){
Std_ReturnType ret = E_NOT_OK ; 
if(NULL == TMR){
    ret = E_NOT_OK ; 
}else {
    
    // disable module 
   TIMER3_MODULE_DISABLE();
   //configure presca
   TIMER3_CONFIGURE_PRESCALER(TMR->Prescaler_value);
   //configure preload
           TMR3H = ((TMR->timer3_preload_value)>> 8);
        TMR3L = (uint8)(TMR->timer3_preload_value);
        preload_vall =TMR->timer3_preload_value ;
   // configue  
   configue_timer_mode(TMR);
   register_configure(TMR);
   
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_CLEAR_FLAG();
        TIMER3_INTERRUPT_HANDLERF = TMR->TIMER3_INTERRUPT_HANDLER ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == TMR->timer3_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
           TIMER3_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY ==  TMR->timer3_priority){ 
           INTERRUPT_GlobalInterruptLowEnable();
           TIMER3_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
#endif 

    // enable module 
   TIMER3_MODULE_ENABLE();
}
return ret ;
}
Std_ReturnType TMR3_DEInit(const Timer3_t *TMR){
Std_ReturnType ret = E_NOT_OK ; 
if(NULL == TMR){
 ret = E_NOT_OK ; 
}else {
  TIMER3_MODULE_DISABLE();
 #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
TIMER3_INTERRUPT_DISABLE();
#endif
}
return ret ;
}
Std_ReturnType TMR3_Write_value(const Timer3_t *TMR , uint16 value){
Std_ReturnType ret = E_NOT_OK ; 
if(NULL == TMR){
 ret = E_NOT_OK ; 
}else {
     TMR3H = ((value)>> 8);
        TMR3L = (uint8)(value);
}
return ret ;

}
Std_ReturnType TMR3_Read_value(const Timer3_t *TMR , uint16 *value){
Std_ReturnType ret = E_NOT_OK ; 
uint8 l_timer3 = ZERO_INIT , h_timer3 = ZERO_INIT;
if((NULL == TMR)&&(NULL ==value)){
 ret = E_NOT_OK ; 
}else {
l_timer3 = TMR3L ;
h_timer3 = TMR3H ;
*value = (uint16)(h_timer3 << 8 ) + l_timer3 ; 
}
return ret ;
}


void TMR3_ISR(void){
 TIMER3_CLEAR_FLAG();
  TMR3H = (preload_vall) >> 8;
    TMR3L = (uint8)(preload_vall);
 if(TIMER3_INTERRUPT_HANDLERF){
 TIMER3_INTERRUPT_HANDLERF();
 }else{
 //nothing
 }


}

static inline void configue_timer_mode(const Timer3_t *TMR) {
    if (TIMER3_counter_mode_cfg == TMR->timer3_mode) {
        TIMER3_COUNTER_MODE();
        if (TIMER3_SYNCHRONOUS_mode == TMR->counter_mode) {
            TIMER3_SYNCHRONOUS_EXTERNAL_CLOCK();

        } else if (TIMER3_ASYNCHRONOUS_mode == TMR->counter_mode) {
            TIMER3_ASYNCHRONOUS_EXTERNAL_CLOCK();
        } else {
            //nothing
        }

    } else if (TIMER3_timer_mode_cfg == TMR->timer3_mode) {
        TIMER3_TIMER_MODE();
    } else {
        //nothing
    }

}
static inline void register_configure(const Timer3_t *TMR ){
    if(TIMER3_rd_16bit_cfg  == TMR->timer3_register_size){
    TIMER3_16BIT_RW();
    }else if(TIMER3_rd_8bit_cfg  == TMR->timer3_register_size){
    TIMER3_8BIT_RW();
    }else {
    //nothing ...
    }

}