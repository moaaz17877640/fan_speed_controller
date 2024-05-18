/* 
 * File:   hal_adc.c
 * Author: MOAAZ
 *
 * Created on February 25, 2024, 5:21 PM
 */
#include "hal_adc.h"
//HELPER FUNCTION
static inline Std_ReturnType adc_select_format(const ADc_t *adc_obj );
static inline Std_ReturnType adc_select_Voltage(const ADc_t *adc_obj );
static inline Std_ReturnType adc_configure_pin(const Adc_select_Channel_t adc_obj );
void (*ADC_INTERRUPT_HANDLERF)(void);


Std_ReturnType ADC_INIT(const ADc_t *adc_obj){
    Std_ReturnType ret =E_OK ;
    if((NULL == adc_obj))
    {
        ret = E_NOT_OK;
    }
    else{
     // disable --> configure --> enable 
        ADC_IS_DISABLE();
//  void (*ACD_INTERRUPT_HANDLER)(void); 
//Adc_select_Channel_t channal;
        ADCON0bits.CHS =adc_obj->channal ;
        adc_configure_pin(adc_obj->channal);
//Adc_time_Acquisition_t time_aq;
        ADCON2bits.ACQT = adc_obj->time_aq ;
//Adc_conversion_clock_t clock_con;
        ADCON2bits.ADCS = adc_obj->clock_con ;
//uint8 result_format : 1;
        adc_select_format(adc_obj->result_format);
//uint8 voltage_reference : 1;
        adc_select_Voltage(adc_obj->voltage_reference); 
        //interrupt handling
#if ADC_INTERRUPT_FEATURE_ENABLE_CFG == INTERRUPT_FEATURE_ENABLE
         ADC_Interrupt_Enable();
         ADC_Interrupt_Flag_Clear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == adc_obj->priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            ADC_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == adc_obj->priority){ 
              INTERRUPT_GlobalInterruptLowEnable();
           ADC_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
         INTERRUPT_PeripheralInterruptEnable();
          INTERRUPT_GlobalInterruptEnable();
#endif
        ADC_INTERRUPT_HANDLERF = adc_obj->ACD_INTERRUPT_HANDLER ;
        
#endif
        ADC_IS_ENABLE() ;
         ret = E_OK ;
    }
    return ret;
}
Std_ReturnType ADC_DEINIT(const ADc_t *adc_obj){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj))
    {
        ret =E_NOT_OK ;
    }
    else{
        // disable adc
      ADC_IS_ENABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE_CFG == INTERRUPT_FEATURE_ENABLE_CFG
   ADC_INTERRUPT_ENABLE();
#endif
      //disable interrupt
    ret = E_OK ;
    }
    return ret;
}
Std_ReturnType Adc_select_Channel(const ADc_t *adc_obj ,Adc_select_Channel_t channal ){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj))
    { 
        ret = E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = channal ;
        adc_configure_pin(channal);
         ret = E_OK ;
    }
    return ret;
}
Std_ReturnType Adc_start_conversion(const ADc_t *adc_obj  ){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj))
    {
          ret = E_NOT_OK;
    }
    else{
        
    ADC_START_CONVERSION();
    
    ret = E_OK ;
    }
    return ret;
}
Std_ReturnType Adc_is_conversion_done(const ADc_t *adc_obj , uint8 *conversion_status ){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj)&&(NULL ==conversion_status))
    {
        ret =E_NOT_OK ;
       
    }
    else{
        *conversion_status =(uint8)( !(ADCON0bits.GO_nDONE));
         ret = E_OK ;
    }
    return ret;
}
Std_ReturnType Adc_Get_conversion_result(const ADc_t *adc_obj , uint16 *conversion_result ){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj)&&(NULL ==conversion_result))
    {
        ret =E_NOT_OK ;
    }
    else{
        if(ADC_RIGHT_FORMAT == adc_obj->result_format){
           *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
   
        }
        else if(ADC_LEFT_FORMAT == adc_obj->result_format){
        *conversion_result =(uint16)(((ADRESH << 8) + ADRESL) >> 6) ;
    
        }
        ret = E_OK ;
    }
    return ret;
}
Std_ReturnType ADC_GetConversion_Blocking(const ADc_t *adc_obj, Adc_select_Channel_t channel, 
                                                             uint16 *conversion_result){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj)&&(NULL ==conversion_result))
    {
        ret =E_NOT_OK;
    }
    else{
        
    ret = Adc_select_Channel(adc_obj,channel);
    ret =Adc_start_conversion(adc_obj);
    while(ADCON0bits.GO_nDONE);
    ret = Adc_Get_conversion_result(adc_obj ,conversion_result);
   
    ret = E_OK ;
    }
    return ret;
} 
Std_ReturnType ADC_Conversion_interrupt(const ADc_t *adc_obj, Adc_select_Channel_t channel){
    Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj))
    {
        ret =E_NOT_OK;
    }
    else{
         ADC_Interrupt_Flag_Clear();
    ret = Adc_select_Channel( adc_obj, channel );
    ret =Adc_start_conversion(adc_obj);
   
    ret =E_OK ;
   
    }
    return ret;
} 
static inline Std_ReturnType adc_select_format(const ADc_t *adc_obj ){
 Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj))
    {
         ret =E_NOT_OK ;
    }
    else{
        if(ADC_RIGHT_FORMAT == adc_obj->result_format){
        ADC_RESULT_RIGHT_FORMAT();
        }
        else if(ADC_LEFT_FORMAT == adc_obj->result_format){
        ADC_RESULT_LEFT_FORMAT() ;
        }
        else {
           ADC_RESULT_RIGHT_FORMAT();
        }
         ret = E_OK ;
    }
    return ret;
 
}
static inline Std_ReturnType adc_select_Voltage(const ADc_t *adc_obj ){
 Std_ReturnType ret =E_NOT_OK ;
    if((NULL == adc_obj))
    {
         ret =E_NOT_OK ;
    }
    else{
        if(ADC_VOLTAGE_REFERENCE_ENABLED == adc_obj->voltage_reference){
      ADC_ENABLE_VOLTAGE_REFERENCE();
        }
        else if(ADC_VOLTAGE_REFERENCE_DISABLED == adc_obj->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        else {
        ADC_ENABLE_VOLTAGE_REFERENCE();
        }
         ret = E_OK ;
    }
    return ret;
 
}
static inline Std_ReturnType adc_configure_pin(const Adc_select_Channel_t adc_obj ){
  Std_ReturnType  ret = E_OK ;
  
        switch(adc_obj){
         case     AN0_CHANNEL:    SET_BIT( TRISA, _TRISA_RA0_POSN ); break;
        
            case  AN1_CHANNEL : SET_BIT( TRISA, _TRISA_RA1_POSN ); break;
            
        case    AN2_CHANNEL:   SET_BIT( TRISA, _TRISA_RA2_POSN );   break;
        
         case   AN3_CHANNEL:     SET_BIT( TRISA, _TRISA_RA3_POSN ); break;
         
         case   AN4_CHANNEL:    SET_BIT( TRISA, _TRISA_RA5_POSN );  break;
         
          case  AN5_CHANNEL:    SET_BIT( TRISE, _TRISE_RE0_POSN );  break;
          
         case   AN6_CHANNEL:     SET_BIT(  TRISE, _TRISE_RE1_POSN); break;
         
          case  AN7_CHANNEL:   SET_BIT( TRISE, _TRISE_RE2_POSN );   break;
          
         case   AN8_CHANNEL:    SET_BIT(  TRISB, _TRISB_RB2_POSN );  break;
         
          case  AN9_CHANNEL:     SET_BIT( TRISB, _TRISB_RB3_POSN ); break;
          
          case  AN10_CHANNEL:     SET_BIT(TRISB, _TRISB_RB1_POSN ); break;
          
          case  AN11_CHANNEL:    SET_BIT( TRISB, _TRISB_RB4_POSN );  break;
          case  AN12_CHANNEL:    SET_BIT( TRISB, _TRISB_RB0_POSN );  break; 
        }
    
    return ret;

}
void ADC_ISR(void){
ADC_Interrupt_Flag_Clear();
if(ADC_INTERRUPT_HANDLERF){
ADC_INTERRUPT_HANDLERF();
}else{
//nothing 
}

}