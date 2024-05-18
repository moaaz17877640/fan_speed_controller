/* 
 * File:   hal_usart.h
 * Author: MOAAZ
 *
 * Created on April 5, 2024, 11:49 AM
 */

#include "hal_usart.h"
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (*EUSART_TX_INTERRUPT_HANDLERF)(void);
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (*EUSART_RX_INTERRUPT_HANDLERF)(void);
void (*EUSART_FRAMING_ERROR_INTERRUPT_HANDLERF)(void);
void (*EUSART_OVERRUN_ERROR_INTERRUPT_HANDLERF)(void);
#endif

static void eusart_baudrate_configuration(const eusart_t *_eusa);
static void EUSART_ASYC_Rx_init(const eusart_t *_eusa);
static void EUSART_ASYC_Tx_init(const eusart_t *_eusa);

Std_ReturnType EUSArt_ASYNC_INIT(const eusart_t *_eusa){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL==_eusa)){
        ret = E_NOT_OK ;
    }else{
        EUSART_MODULE_DISABLE();
        TRISCbits.RC6 = 1 ; 
        TRISCbits.RC7 = 1 ; 
    eusart_baudrate_configuration(_eusa);
     EUSART_ASYC_Rx_init(_eusa);
     EUSART_ASYC_Tx_init(_eusa);
    EUSART_MODULE_ENABLE();
    }
    return ret ;
}
Std_ReturnType EUSArt_ASYNC_DEINIT(const eusart_t *_eusa){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL==_eusa)){
    ret = E_NOT_OK ;
    }else{
    EUSART_MODULE_DISABLE();

    }
    return ret ;
}
Std_ReturnType EUSArt_ASYNC_Write_valueBlocking(uint16 value){
    Std_ReturnType ret = E_NOT_OK ; 
   
     while(!(TXSTAbits.TRMT));
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     EUSART_TX_INTERRUPT_ENABLE();
#endif
        TXREG = value ;
    return ret ;
}
Std_ReturnType EUSArt_ASYNC_WriteString_valueBlocking(uint8 *value , uint16 str_len){
    uint8 len_l = str_len ;
   Std_ReturnType ret = E_NOT_OK ;
    while(str_len){
    EUSArt_ASYNC_Write_valueBlocking(value[len_l-str_len]);
    str_len--;
    }

}

Std_ReturnType EUSArt_ASYNC_Write_valueNoBlocking(uint16 value){
    Std_ReturnType ret = E_NOT_OK ; 
   
    if(1==TXSTAbits.TRMT){
     TXREG = value ;
    }else{
    //nothing
    }
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     EUSART_TX_INTERRUPT_ENABLE();
#endif
       
    return ret ;
}
Std_ReturnType EUSArt_ASYNC_WriteString_valueNoBlocking(uint8 *value , uint16 str_len){
 uint8 len_l = str_len ;
   Std_ReturnType ret = E_NOT_OK ;
    while(str_len){
    EUSArt_ASYNC_Write_valueNoBlocking(value[len_l-str_len]);
    str_len--;
    }

}
Std_ReturnType EUSArt_ASYNC_Read_valueBlocking( uint16 *value){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL == value)){
    ret = E_NOT_OK ;
    }else{
        while(!(PIR1bits.RCIF) );
        *value = RCREG ;
    }
    return ret ;
}
Std_ReturnType EUSArt_ASYNC_Read_valuenoBlocking( uint16 *value){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL == value)){
    ret = E_NOT_OK ;
    }else{
        if(PIR1bits.RCIF == 1){
           *value = RCREG ;
        }
        else{
        //nothing
        }
     
    }
    return ret ;
}

static void eusart_baudrate_configuration(const eusart_t *_eusa){
    float baud_temp = ZERO_INIT ;
    if(BAUDRATE_ASYNCHRONOUS_8BIT_LOW_SPEED ==_eusa->baud_rate_formula ){
        TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE_CFG ;
        BAUDCONbits.BRG16 = EUSART_BAUDRATE_8BIT_GENERATOR_CFG ;
        TXSTA1bits.BRGH  = EUSART_BAUDRATE_ASYN_LOW_SPEED_CFG ;
    baud_temp = (_XTAL_FREQ /(float)_eusa->baud_rate_value /64.0) - 1 ;
    }
    else if(BAUDRATE_ASYNCHRONOUS_8BIT_HIGH_SPEED ==_eusa->baud_rate_formula ){
     // 001
        TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE_CFG ;
        BAUDCONbits.BRG16 = EUSART_BAUDRATE_8BIT_GENERATOR_CFG ;
        TXSTA1bits.BRGH  = EUSART_BAUDRATE_ASYN_HIGH_SPEED_CFG ;
    baud_temp = (_XTAL_FREQ /(float)_eusa->baud_rate_value /16.0) - 1 ;
    }
    else if(BAUDRATE_ASYNCHRONOUS_16BIT_LOW_SPEED ==_eusa->baud_rate_formula ){
    //010
     TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE_CFG ;
        BAUDCONbits.BRG16 = EUSART_BAUDRATE_16BIT_GENERATOR_CFG ;
        TXSTA1bits.BRGH  = EUSART_BAUDRATE_ASYN_LOW_SPEED_CFG ;
        baud_temp = (_XTAL_FREQ /(float)_eusa->baud_rate_value /16.0) - 1 ;
    }
    else if(BAUDRATE_ASYNCHRONOUS_16BIT_HIGH_SPEED ==_eusa->baud_rate_formula ){
    //011
     TXSTA1bits.SYNC =EUSART_ASYNCHRONOUS_MODE_CFG ;
        BAUDCONbits.BRG16 = EUSART_BAUDRATE_16BIT_GENERATOR_CFG ;
        TXSTA1bits.BRGH  = EUSART_BAUDRATE_ASYN_HIGH_SPEED_CFG ;
         baud_temp = (_XTAL_FREQ /(float)_eusa->baud_rate_value /4.0) - 1 ;
    }
    else if(BAUDRATE_SYNCHRONOUS_8BIT ==_eusa->baud_rate_formula ){
     TXSTA1bits.SYNC = EUSART_SYNCHRONOUS_MODE_CFG ;
        BAUDCONbits.BRG16 = EUSART_BAUDRATE_8BIT_GENERATOR_CFG ;
                baud_temp = (_XTAL_FREQ /(float)_eusa->baud_rate_value /4.0) - 1 ;

    
    }else if(BAUDRATE_SYNCHRONOUS_16BIT ==_eusa->baud_rate_formula ){
    
     TXSTA1bits.SYNC = EUSART_SYNCHRONOUS_MODE_CFG ;
        BAUDCONbits.BRG16 =EUSART_BAUDRATE_16BIT_GENERATOR_CFG ;
                baud_temp = (_XTAL_FREQ /(float)_eusa->baud_rate_value /4.0) - 1 ;

    }else { // nothing  
        
    }
    SPBRG = (uint8)((uint32)(baud_temp));
    SPBRGH = (uint8)(((uint32)baud_temp) >>8 );

}

static void EUSART_ASYC_Tx_init(const eusart_t *_eusa) {

    if (EUSART_ASYNCHRONOUS_TX_ENABLE_CFG == _eusa->tx_cfg.asyn_tx_enable) {
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE_CFG;
        if (EUSART_ASYNCHRONOUS_TX_SELECT_9BIT_ENABLE_CFG == _eusa->tx_cfg.asyn_tx_9bit_select) {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_TX_SELECT_9BIT_ENABLE_CFG;
        } else if (EUSART_ASYNCHRONOUS_TX_SELECT_9BIT_DISABLE_CFG == _eusa->tx_cfg.asyn_tx_9bit_select) {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_TX_SELECT_9BIT_DISABLE_CFG;
        } else {
            //nothing
        }

        if (EUSART_TX_INTERRUPT_ENABLE_CFG == _eusa->tx_cfg.asyn_tx_interrupt_cfg) {
            PIE1bits.TXIE = EUSART_TX_INTERRUPT_ENABLE_CFG;
        } else if (EUSART_TX_INTERRUPT_DISABLE_CFG == _eusa->tx_cfg.asyn_tx_interrupt_cfg) {
            PIE1bits.TXIE = EUSART_TX_INTERRUPT_DISABLE_CFG;
        } else {
            //nothing
        }

    } else {
        //nothing   
    }
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_INTERRUPT_ENABLE();
        
        EUSART_TX_INTERRUPT_HANDLERF = _eusa->EUSART_TX_INTERRUPT_HANDLER ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _eusa->tx_cfg.tx_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            EUSART_TX_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY ==  _eusa->tx_cfg.tx_priority){ 
           INTERRUPT_GlobalInterruptLowEnable();
             EUSART_TX_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
#endif

}

static void EUSART_ASYC_Rx_init(const eusart_t *_eusa) {

    if (EUSART_ASYNCHRONOUS_RX_ENABLE_CFG == _eusa->rx_cfg.asyn_rx_enable) {
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE_CFG;
        if (EUSART_ASYNCHRONOUS_RX_SELECT_9BIT_ENABLE_CFG == _eusa->rx_cfg.asyn_rx_9bit_select) {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_RX_SELECT_9BIT_ENABLE_CFG;
        } else if (EUSART_ASYNCHRONOUS_RX_SELECT_9BIT_DISABLE_CFG == _eusa->rx_cfg.asyn_rx_9bit_select) {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_RX_SELECT_9BIT_DISABLE_CFG;
        } else {
            //nothing
        }

        if (EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE_CFG == _eusa->rx_cfg.asyn_rx_interrupt_cfg) {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE_CFG;
        } else if (EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE_CFG == _eusa->rx_cfg.asyn_rx_interrupt_cfg) {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE_CFG;
        } else {
            //nothing
        }

    } else {
        //nothing   
    }
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_RX_INTERRUPT_ENABLE();
        
        EUSART_RX_INTERRUPT_HANDLERF = _eusa->EUSART_RX_INTERRUPT_HANDLER ;
        EUSART_OVERRUN_ERROR_INTERRUPT_HANDLERF = _eusa->EUSART_OVERRUN_ERROR_INTERRUPT_HANDLER ;
        EUSART_FRAMING_ERROR_INTERRUPT_HANDLERF = _eusa->EUSART_FRAMING_ERROR_INTERRUPT_HANDLER ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _eusa->rx_cfg.rx_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            EUSART_RX_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY ==  _eusa->rx_cfg.rx_priority){ 
           INTERRUPT_GlobalInterruptLowEnable();
             EUSART_RX_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();       
#endif
#endif
    

}
Std_ReturnType EUSArt_ASYNC_Restart_mode(void){
    Std_ReturnType ret = E_OK;
RCSTAbits.CREN  = 0 ;
RCSTAbits.CREN  = 1 ;
return ret ;

}
void EUSART_TX_ASY_ISR(void){
EUSART_TX_INTERRUPT_DISABLE();
    if(EUSART_TX_INTERRUPT_HANDLERF){
    EUSART_TX_INTERRUPT_HANDLERF();
    }else{
    /*nothing*/
    }

}
void EUSART_RX_ASY_ISR(void){
   if(EUSART_RX_INTERRUPT_HANDLERF){
    EUSART_RX_INTERRUPT_HANDLERF();
    }else{
    /*nothing*/
    }
      if(EUSART_FRAMING_ERROR_INTERRUPT_HANDLERF){
    EUSART_FRAMING_ERROR_INTERRUPT_HANDLERF();
    }else{
    /*nothing*/
    }
      if(EUSART_OVERRUN_ERROR_INTERRUPT_HANDLERF){
    EUSART_OVERRUN_ERROR_INTERRUPT_HANDLERF();
    }else{
    /*nothing*/
    }

}
