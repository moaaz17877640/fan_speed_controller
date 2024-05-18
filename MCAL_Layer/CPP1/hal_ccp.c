#include "hal_ccp.h"

static void (*CCP1_INTERRUPT_HANDLERF)(void) = NULL;
static void (*CCP2_INTERRUPT_HANDLERF)(void) = NULL;


static inline void configure_mode(const ccp_t *_ccp);
static inline void ccp_interrupt(const ccp_t *_ccp);
static inline void selected_timer(const ccp_t *_ccp);

Std_ReturnType CCP_INIt(const ccp_t *_ccp){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == _ccp){
        ret=E_NOT_OK ;
    }else{ 
        /*disable module */
        if(CCP1_INST==_ccp->ccp_inst){
        CONFIGURE_CCP1_SUB_MODE(Capture_Compare_PWM_disabled);
        }else 
             if(CCP2_INST==_ccp->ccp_inst){
        CONFIGURE_CCP2_SUB_MODE(Capture_Compare_PWM_disabled);
        }
        ret= gpio_pin_intialize(&(_ccp->ccp_pin));
        /*configure mode and sub mode*/
      configure_mode(_ccp);
      ccp_interrupt(_ccp);

    
    }
    return ret; 
}
Std_ReturnType CCP_DEINIt(const ccp_t *_ccp){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == _ccp){
        ret=E_NOT_OK ;
    }else{
        if(CCP1_INST ==_ccp->ccp_inst ){
       CONFIGURE_CCP1_SUB_MODE(Capture_Compare_PWM_disabled);
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       CCP1_INTERRUPT_DISABLE() ;
#endif
        }
        else if(CCP2_INST ==_ccp->ccp_inst ){
       CONFIGURE_CCP2_SUB_MODE(Capture_Compare_PWM_disabled);
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       CCP2_INTERRUPT_DISABLE() ;
#endif
        }
    }
    return ret; 
}
#if (CCP1_MODULE_SELECTED == CCP1_MODULE_PWM_MODE_CFG)||(CCP2_MODULE_SELECTED == CCP2_MODULE_PWM_MODE_CFG) 
Std_ReturnType START_PWM(const ccp_t *_ccp){
Std_ReturnType ret = E_NOT_OK ;
if(CCP1_INST ==_ccp->ccp_inst ){
CONFIGURE_CCP1_SUB_MODE(PWM_Mode);
}else if(CCP2_INST ==_ccp->ccp_inst ){
CONFIGURE_CCP2_SUB_MODE(PWM_Mode);
}
return ret; 
}
Std_ReturnType STOP_PWM(const ccp_t *_ccp){
Std_ReturnType ret = E_NOT_OK ;
if(CCP1_INST ==_ccp->ccp_inst ){
CONFIGURE_CCP1_SUB_MODE(Capture_Compare_PWM_disabled);
}else if(CCP2_INST ==_ccp->ccp_inst ){
CONFIGURE_CCP2_SUB_MODE(Capture_Compare_PWM_disabled);
}
return ret; 

}
Std_ReturnType PWM_set_Duty(uint8 duty , const ccp_t *_ccp){
Std_ReturnType ret = E_NOT_OK ;
uint16 set_duty_valu = ZERO_INIT ;
if(CCP1_INST ==_ccp->ccp_inst ){
set_duty_valu = (uint16)(( PR2 + 1 ) * ( duty / 100.0) * 4);
CCP1CONbits.DC1B =(uint8)(set_duty_valu & 0x0003);
CCPR1L =(uint8)(set_duty_valu>>2);
}else if(CCP2_INST ==_ccp->ccp_inst ){
set_duty_valu = (uint16)(( PR2 + 1 ) * ( duty / 100.0) * 4);
CCP2CONbits.DC2B =(uint8)(set_duty_valu & 0x0003);
CCPR2L =(uint8)(set_duty_valu>>2);
}
return ret; 
}
#endif

#if CCP1_MODULE_SELECTED == CCP1_MODULE_CAPTURE_MODE_CFG || CCP2_MODULE_SELECTED == CCP2_MODULE_CAPTURE_MODE_CFG
Std_ReturnType capture_is_ready(uint8 *capture_statue ,const ccp_t *_ccp ){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == capture_statue){
        ret=E_NOT_OK ;
    }else{
        if(CCP1_INST ==_ccp->ccp_inst ){
            
              if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
    *capture_statue = CCP1_CAPTURE_READY;
    }else{
        *capture_statue =  CCP1_CAPTURE_NOT_READY;
        
    }  
        }
        else if(CCP2_INST ==_ccp->ccp_inst ){
            
              if(CCP2_CAPTURE_READY == PIR2bits.CCP2IF){
    *capture_statue = CCP2_CAPTURE_READY;
    }else{
        *capture_statue =  CCP2_CAPTURE_NOT_READY;
        
    }  
        }
    
    
}
    return ret; 
}
Std_ReturnType capture_read_value(const ccp_t *_ccp, uint16 *capture_value ){
    Std_ReturnType ret = E_NOT_OK ; 
    CCP_reg_t retu_reg = {.CCP_REG_High = ZERO_INIT , .CCP_REG_Low = ZERO_INIT};
    if(NULL == capture_value){
        ret=E_NOT_OK ;
    }else{
        if(CCP1_INST ==_ccp->ccp_inst ){
            
     retu_reg.CCP_REG_High = CCPR1H ;
    retu_reg.CCP_REG_Low = CCPR1L ;
    *capture_value = retu_reg.CCP_16_REG ; 
        }  else if(CCP2_INST ==_ccp->ccp_inst ){
            
     retu_reg.CCP_REG_High = CCPR2H ;
    retu_reg.CCP_REG_Low = CCPR2L ;
    *capture_value = retu_reg.CCP_16_REG ; 
        }
        }
    return ret; 
}
#endif
#if CCP1_MODULE_SELECTED == CCP1_MODULE_COMPARE_MODE_CFG || CCP2_MODULE_SELECTED == CCP2_MODULE_COMPARE_MODE_CFG
Std_ReturnType compare_is_Complete(const ccp_t *_ccp ,uint8 *statue){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == statue){
        ret = E_NOT_OK ;
    }else{
        if(CCP1_INST ==_ccp->ccp_inst ){
               if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
            *statue = CCP1_COMPARE_READY;
            }else{
      *statue = CCP1_COMPARE_NOT_READY;
        }
        }else  if(CCP2_INST ==_ccp->ccp_inst ){
               if(CCP2_CAPTURE_READY == PIR2bits.CCP2IF){
            *statue = CCP2_COMPARE_READY;
            }else{
      *statue = CCP2_COMPARE_NOT_READY;
        }
        }
   
    }
    return ret; 
}
Std_ReturnType compare_set_value(const ccp_t *_ccp ,uint16 capture_value){
     Std_ReturnType ret = E_NOT_OK ; 
CCP_reg_t retu_reg = {.CCP_REG_High = ZERO_INIT , .CCP_REG_Low = ZERO_INIT};
if(CCP1_INST ==_ccp->ccp_inst ){
  retu_reg.CCP_16_REG = capture_value ;
  CCPR1H  =  retu_reg.CCP_REG_High  ;
  CCPR1L  =  retu_reg.CCP_REG_Low   ;  
}else if(CCP2_INST ==_ccp->ccp_inst ){
  retu_reg.CCP_16_REG = capture_value ;
  CCPR2H  =  retu_reg.CCP_REG_High  ;
  CCPR2L  =  retu_reg.CCP_REG_Low   ;  
}
else{
//nothing 
}
   return ret; 
}
#endif
void CCP1_ISR(void){
CCP1_CLEAR_FLAG();
if(CCP1_INTERRUPT_HANDLERF){
    CCP1_INTERRUPT_HANDLERF();
}else{
//NOTHING
}

}
void CCP2_ISR(void){
CCP2_CLEAR_FLAG();
if(CCP2_INTERRUPT_HANDLERF){
    CCP2_INTERRUPT_HANDLERF();
}else{
//NOTHING
}

}
static inline void configure_mode(const ccp_t *_ccp){
        if(CCP1_INST ==_ccp->ccp_inst ){
            
    if(CCP1_MODULE_COMPARE_MODE_CFG == _ccp->CCP_Mode){
            switch(_ccp->Sub_mode)
            {
                case   Compare_Mode_Toggle_Output  :   
                    CONFIGURE_CCP1_SUB_MODE(Compare_Mode_Toggle_Output);
                    break ;
                    case   Compare_mode_force_CCP2_pin_High : 
                        CONFIGURE_CCP1_SUB_MODE(Compare_mode_force_CCP2_pin_High);
                    break ;
                    case   Compare_mode_force_CCP2_pin_Low  : 
                        CONFIGURE_CCP1_SUB_MODE(Compare_mode_force_CCP2_pin_Low);
                    break ;
                    case   Compare_mode_generate_software_interrupt  : 
                        CONFIGURE_CCP1_SUB_MODE(Compare_mode_generate_software_interrupt);
                    break ;
                     case   Compare_mode_trigger_special_event  : 
                         CONFIGURE_CCP1_SUB_MODE(Compare_mode_trigger_special_event);
                    break ;
                default : //nothing     
                           ;
            }
            selected_timer(_ccp);
        }else if(CCP1_MODULE_CAPTURE_MODE_CFG == _ccp->CCP_Mode){
          switch(_ccp->Sub_mode)
            {
                case   Capture_mode_every_falling_edge  :   
                    CONFIGURE_CCP1_SUB_MODE(Capture_mode_every_falling_edge);
                    break ;
                    case   Capture_mode_every_rising_edge  : 
                        CONFIGURE_CCP1_SUB_MODE(Capture_mode_every_rising_edge);
                    break ;
                    case   Capture_mode_every_4rising_edge  : 
                        CONFIGURE_CCP1_SUB_MODE(Capture_mode_every_4rising_edge);
                    break ;
                    case   Capture_mode_every_16rising_edge  : 
                        CONFIGURE_CCP1_SUB_MODE(Capture_mode_every_16rising_edge);
                    break ;
                default : //nothing     
                           ;
            }
          selected_timer(_ccp);
        }else if(CCP1_MODULE_PWM_MODE_CFG == _ccp->CCP_Mode){
#if (CCP1_MODULE_SELECTED == CCP1_MODULE_PWM_MODE_CFG)||(CCP2_MODULE_SELECTED == CCP2_MODULE_PWM_MODE_CFG)          
           if(PWM_Mode == _ccp->Sub_mode){
        CONFIGURE_CCP1_SUB_MODE(PWM_Mode);
           }
        else {
        
        }
         PR2 =(uint8 )((_XTAL_FREQ/(_ccp->PWM_Freq * 4.0 * _ccp->timer2_prescaler *_ccp->timer2_postscaler))-1);
#endif 
        }


        }
        else if(CCP2_INST ==_ccp->ccp_inst ){
         if(CCP2_MODULE_COMPARE_MODE_CFG == _ccp->CCP_Mode){
            switch(_ccp->Sub_mode)
            {
                case   Compare_Mode_Toggle_Output  :   
                    CONFIGURE_CCP2_SUB_MODE(Compare_Mode_Toggle_Output);
                    break ;
                    case   Compare_mode_force_CCP2_pin_High  : 
                        CONFIGURE_CCP2_SUB_MODE(Compare_mode_force_CCP2_pin_High);
                    break ;
                    case   Compare_mode_force_CCP2_pin_Low  : 
                        CONFIGURE_CCP2_SUB_MODE(Compare_mode_force_CCP2_pin_Low);
                    break ;
                    case   Compare_mode_generate_software_interrupt  : 
                        CONFIGURE_CCP2_SUB_MODE(Compare_mode_generate_software_interrupt);
                    break ;
                     case   Compare_mode_trigger_special_event  : 
                         CONFIGURE_CCP2_SUB_MODE(Compare_mode_trigger_special_event);
                    break ;
                default : //nothing     
                           ;
            }
            selected_timer(_ccp);
        }else if(CCP1_MODULE_CAPTURE_MODE_CFG == _ccp->CCP_Mode){
          switch(_ccp->Sub_mode)
            {
                case   Capture_mode_every_falling_edge  :   
                    CONFIGURE_CCP2_SUB_MODE(Capture_mode_every_falling_edge);
                    break ;
                    case   Capture_mode_every_rising_edge  : 
                        CONFIGURE_CCP2_SUB_MODE(Capture_mode_every_rising_edge);
                    break ;
                    case   Capture_mode_every_4rising_edge  : 
                        CONFIGURE_CCP2_SUB_MODE(Capture_mode_every_4rising_edge);
                    break ;
                    case   Capture_mode_every_16rising_edge  : 
                        CONFIGURE_CCP2_SUB_MODE(Capture_mode_every_16rising_edge);
                    break ;
                default : //nothing     
                           ;
            }
          selected_timer(_ccp);
        }else if(CCP1_MODULE_PWM_MODE_CFG == _ccp->CCP_Mode){
#if (CCP1_MODULE_SELECTED == CCP1_MODULE_PWM_MODE_CFG)||(CCP2_MODULE_SELECTED == CCP2_MODULE_PWM_MODE_CFG)         
           if(PWM_Mode == _ccp->Sub_mode){
        CONFIGURE_CCP2_SUB_MODE(PWM_Mode);
           }
        else {
        
        }
         PR2 =(uint8 )((_XTAL_FREQ/(_ccp->PWM_Freq * 4.0 * _ccp->timer2_prescaler *_ccp->timer2_postscaler))-1);
#endif 
        }

   
        }
    
  
}
static inline void ccp_interrupt(const ccp_t *_ccp){
    if(CCP1_INST== _ccp){
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_CLEAR_FLAG();
        CCP1_INTERRUPT_HANDLERF = _ccp->CCP1_INTERRUPT_HANDLER ;
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _ccp->priority_CCP1){ 
            INTERRUPT_GlobalInterruptHighEnable();
           CCP1_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp->priority_CCP1){ 
              INTERRUPT_GlobalInterruptLowEnable();
           CCP1_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
       
        
#endif
          
    }else if(CCP2_INST== _ccp){
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         CCP2_INTERRUPT_ENABLE();
        CCP2_CLEAR_FLAG();
        CCP2_INTERRUPT_HANDLERF = _ccp->CCP2_INTERRUPT_HANDLER ;
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _ccp->priority_CCP2){ 
            INTERRUPT_GlobalInterruptHighEnable();
           CCP2_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp->priority_CCP2){ 
              INTERRUPT_GlobalInterruptLowEnable();
           CCP2_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
       
        
#endif
    }

}
static inline void selected_timer(const ccp_t *_ccp){
    if(TIMER1_FOR_CCP1_CCP2 == _ccp->tmr){
  T3CONbits.T3CCP1 = 0 ; 
    T3CONbits.T3CCP2 = 0 ; 
    }else if(TIMER1_FOR_CCP1_TIMER3_FOR_CCP2== _ccp->tmr){
         T3CONbits.T3CCP1 = 1 ; 
    T3CONbits.T3CCP2 = 0 ; 
    }else if(TIMER3_FOR_CCP1_CCP2== _ccp->tmr){
       T3CONbits.T3CCP1 = 0 ; 
    T3CONbits.T3CCP2 = 1 ;   
    }

}