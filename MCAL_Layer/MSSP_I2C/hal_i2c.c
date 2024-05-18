#include "hal_i2c.h"
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Write_Collision_HANDLERF)(void);
    void (*I2C_Receive_Overflow_IndicatoR_HANDLERF)(void);
    void (*I2C_INTERRUPT_HANDLERF)(void) ;
#endif
    
    
static void MSSP_12C_Interrupt_configuration(const Mssp_i2c_t *i2c);
static inline void MSSP_I2C_Mode_GPIO_CFG(void);


Std_ReturnType   MSSP_I2c_MODE_Init(const Mssp_i2c_t *i2c){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
    
        ret=  E_NOT_OK ;
    }else{
     /*\disable \module*/
      MSSP_MODULE_DISABLE();   
     /*\configuration*/
      if(I2C_MASTER_MODE_CFG == i2c->i2c_cfg.i2c_mode)
      {
          SSPCON1bits.SSPM = i2c->i2c_cfg.i2c_mode_cfg ;
      SSPADD =  (uint8)((4*i2c->clock_value)/_XTAL_FREQ ) - 1 ;
      
      }else  if(I2C_SLAVE_MODE_CFG == i2c->i2c_cfg.i2c_mode)
      {
      
      if(I2C_GENERAL_CALL_ENABLE_CFG == i2c->i2c_cfg.i2c_general_call){
      I2C_GENERAL_CALL_ENABLE();
      }else if(I2C_GENERAL_CALL_DISABLE_CFG == i2c->i2c_cfg.i2c_general_call){
      I2C_GENERAL_CALL_DISABLE();
      }else {   /* \nothing*/   }
      /*\configure bus collision*/
       SSPCON1bits.WCOL = 0 ;
      /*\configure overflow*/
        SSPCON1bits.SSPOV = 0 ;
      /*\configure9 (Release) disable clock stretch*/ 
        SSPCON1bits.CKP = 1 ; 
        SSPADD = i2c->i2c_cfg.slave_address;
        /*configure i2c modes*/
        SSPCON1bits.SSPM = i2c->i2c_cfg.i2c_mode_cfg ;
      }else {  /* \nothing*/  }   
      MSSP_I2C_Mode_GPIO_CFG();
      if(I2C_SMBUS_SELECT_ENABLE_CFG == i2c->i2c_cfg.SMBus){
      I2C_SMBUS_SELECT_ENABLE();
      }else if(I2C_SMBUS_SELECT_DISABLE_CFG == i2c->i2c_cfg.SMBus){
          I2C_SMBUS_SELECT_DISABLE();
      }else {   /* \nothing*/  }
      
      if(I2C_SLEW_RATE_ENABLE_CFG == i2c->i2c_cfg.Slew_Rate){
      I2C_SLEW_RATE_ENABLE();
      }else if(I2C_SLEW_RATE_DISABLE_CFG == i2c->i2c_cfg.Slew_Rate){
                I2C_SLEW_RATE_DISABLE();
      }else {  /* \nothing*/   }
      
      /*interrupt configuration*/
      MSSP_12C_Interrupt_configuration(i2c);
     /*\enable \module*/
      ret = E_OK ;
      MSSP_MODULE_ENABLE();
    }
    return ret ;
}
Std_ReturnType   MSSP_I2c_MODE_DEInit(const Mssp_i2c_t *i2c){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    
    }else{
    MSSP_MODULE_DISABLE();
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_12C_INTERRUPT_DISABLE();
#endif
    }
    return ret ;
}
Std_ReturnType   MSSP_I2c_Send_start_Bit(const Mssp_i2c_t *i2c){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    }else{
    SSPCON2bits.SEN = 1 ;
    while(SSPCON2bits.SEN);
    PIR1bits.SSPIF = 0 ;
    if(I2C_START_BIT_DETECTED_LAST_CFG == SSPSTATbits.S){
    ret=  E_OK ;
    }else{
      ret=  E_NOT_OK ;
    }
    }
    return ret ;
}
Std_ReturnType   MSSP_I2c_Send_Stop_Bit(const Mssp_i2c_t *i2c){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    
    }else{
     SSPCON2bits.PEN = 1 ;
    while(SSPCON2bits.PEN);
    PIR1bits.SSPIF = 0 ;
    if(I2C_STOP_BIT_DETECTED_LAST_CFG == SSPSTATbits.P){
    ret=  E_OK ;
    }else{
      ret=  E_NOT_OK ;
    }
    }
    return ret ;
}
Std_ReturnType   MSSP_I2c_Send_Repeated_start_Bit(const Mssp_i2c_t *i2c){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    
    }else{
    SSPCON2bits.RSEN = 1 ;
    while(SSPCON2bits.RSEN);
    PIR1bits.SSPIF = 0 ;
    ret=  E_OK ;
    
    }
    return ret ;
}

Std_ReturnType   MSSP_I2c_read_data_Blocking(const Mssp_i2c_t *i2c ,uint8 *data , uint8 ACK){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL ==i2c)||(NULL ==data) ){
     ret=  E_NOT_OK ;
    }else{
        I2C_MASTER_RECEIVE_ENABLE();
        while(!SSPSTATbits.BF);
       *data = SSPBUF ;
       PIR1bits.SSPIF = 0 ;
       if(I2C_SEND_ACK_CFG == ACK){
       SSPCON2bits.ACKDT = 0 ;
       SSPCON2bits.ACKEN = 1 ;
         while(SSPCON2bits.ACKEN);
       }else  if(I2C_SEND_NOT_ACK_CFG == ACK){
       SSPCON2bits.ACKDT = 1 ;
       SSPCON2bits.ACKEN = 1 ;
       while(SSPCON2bits.ACKEN);
       }else { /*nothing*/ }
       ret = E_OK ;
    }
    return ret ;
}
Std_ReturnType   MSSP_I2c_Write_data_Blocking(const Mssp_i2c_t *i2c ,uint8 data, uint8 *ACK){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    
    }else{
    SSPBUF = data ;
    while(SSPSTATbits.BF);
    PIR1bits.SSPIF = 0 ;
    if(I2C_RECEIVED_ACK_CFG == SSPCON2bits.ACKSTAT)
    {
    *ACK = I2C_RECEIVED_ACK_CFG ;
    } else if(I2C_RECEIVED_NOT_ACK_CFG == SSPCON2bits.ACKSTAT)
    {
    *ACK = I2C_RECEIVED_NOT_ACK_CFG ;
    }
     ret = E_OK;
    }
    return ret ;
}

Std_ReturnType   MSSP_I2c_read_data_nBlocking(const Mssp_i2c_t *i2c ,uint8 *data, uint8 ACK){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    
    }else{
    
    }
    return ret ;
}
Std_ReturnType   MSSP_I2c_Write_data_nBlocking(const Mssp_i2c_t *i2c ,uint8 data, uint8 *ACK){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL ==i2c ){
     ret=  E_NOT_OK ;
    
    }else{
    
    }
    return ret ;
}
static void MSSP_12C_Interrupt_configuration(const Mssp_i2c_t *i2c){
      //interrupt handling
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         MSSP_12C_INTERRUPT_ENABLE();
         MSSP_12C_BUS_COLLISION_INTERRUPT_ENABLE();
         MSSP_12C_CLEAR_FLAG();
         MSSP_12C_BUS_COLLISION_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == i2c->i2c_cfg.i2c_tr_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == i2c->i2c_cfg.i2c_tr_priority){ 
              INTERRUPT_GlobalInterruptLowEnable();
           MSSP_I2C_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
                if(INTERRUPT_HIGH_PRIORITY == i2c->i2c_cfg.i2c_bus_priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_12C_BUS_COLLISION_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == i2c->i2c_cfg.i2c_bus_priority){ 
              INTERRUPT_GlobalInterruptLowEnable();
           MSSP_12C_BUS_COLLISION_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else
         INTERRUPT_PeripheralInterruptEnable();
          INTERRUPT_GlobalInterruptEnable();
#endif
       I2C_INTERRUPT_HANDLERF = i2c->I2C_INTERRUPT_HANDLER ;
       I2C_Receive_Overflow_IndicatoR_HANDLERF = i2c->I2C_Receive_Overflow_IndicatoR_HANDLER ;
       I2C_Write_Collision_HANDLERF = i2c->I2C_Write_Collision_HANDLER ;
        
#endif


}
static inline void MSSP_I2C_Mode_GPIO_CFG(void){
    TRISCbits.TRISC3 = 1; /* Serial clock (SCL) is Input */
    TRISCbits.TRISC4 = 1; /* Serial data (SDA) is Input */
}
void I2C_BUS_COLLISION_ISR(void){
MSSP_12C_BUS_COLLISION_CLEAR_FLAG();
if(I2C_Write_Collision_HANDLERF){
I2C_Write_Collision_HANDLERF();
}else {
/* nothing */
}

}
void I2C_MODULE_TR_ISR(void){
MSSP_12C_CLEAR_FLAG();
if(I2C_INTERRUPT_HANDLERF){
I2C_INTERRUPT_HANDLERF();
}else {
/* nothing */
}

}