/* 
 * File:   hal_spi.c
 * Author: Moaaz elmahi
 *
 * Created on May 2, 2024, 12:03 PM
 */
#include "hal_spi.h"
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*MSSP_SPI_INTERRUPT_HANDLERF)(void);
   
#endif
static void spi_interrupt_configuration(const mssp_spi_t *spi);
static void spi_master_mode_configuration(const mssp_spi_t *spi);
static void spi_slave_mode_configuration(const mssp_spi_t *spi);
Std_ReturnType Spi_Init(const mssp_spi_t *spi){
    Std_ReturnType ret= E_NOT_OK ; 
    if(NULL== spi ){
        ret = E_NOT_OK ;
    }else{
        /*disable module */
        MSSP_SPI_MODULE_DISABLE();
         /*configure mode*/
        //not complete
        SSPCON1bits.SSPM = spi->spi_mode ;
        if( (MSSP_SPI_MASTER_CLK_FOSC_4 == spi->spi_mode)||(MSSP_SPI_MASTER_CLK_FOSC_16 == spi->spi_mode)||
                (MSSP_SPI_MASTER_CLK_FOSC_64 == spi->spi_mode)||(MSSP_SPI_MASTER_CLK_TMR2_OUT2 == spi->spi_mode)){
        spi_master_mode_configuration(spi);
        }else if( (MSSP_SPI_MASTER_CLK_FOSC_4 == spi->spi_mode)||
                (MSSP_SPI_MASTER_CLK_FOSC_16 == spi->spi_mode)){
            
        spi_slave_mode_configuration(spi);
        }
        /*configure clock select(polarity)*/
        SSPCON1bits.CKP = spi->spi_cfg.clk_polarity ; 
         /*configure clock phase ->time of latch*/
        SSPSTATbits.CKE = spi->spi_cfg.clk_phase ;
        /*configure when sample*/
        SSPSTATbits.SMP = spi->spi_cfg.clk_sample ; 
        spi_interrupt_configuration(spi);
        /*enable module */
        MSSP_SPI_MODULE_ENABLE();
        
        ret= E_OK; 
    }
    return ret ;
}
Std_ReturnType Spi_DEInit(const mssp_spi_t *spi){
    Std_ReturnType ret= E_NOT_OK ; 
    if(NULL== spi ){
        ret = E_NOT_OK ;
        
    }else{
        MSSP_SPI_MODULE_DISABLE();
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        MSSP_SPI_INTERRUPT_DISABLE();
#endif
        ret= E_OK; 
    }
    return ret ;
}
Std_ReturnType Spi_Read_byte_block(const mssp_spi_t *spi, uint8 *data){
    Std_ReturnType ret= E_NOT_OK ; 
    if(NULL== spi ){
        ret = E_NOT_OK ;
        
    }else{
        while(!SSPSTATbits.BF);
        *data = SSPBUF ; 
        ret= E_OK; 
    }
    return ret ;
}
Std_ReturnType Spi_Write_byte_block(const mssp_spi_t *spi, uint8 data){
    Std_ReturnType ret= E_NOT_OK ; 
    if(NULL== spi ){
        ret = E_NOT_OK ;
        
    }else{
        SSPBUF = data ;
        while(!(PIR1bits.SSPIF));
         MSSP_SPI_CLEAR_FLAG();
         
        
        ret= E_OK; 
    }
    return ret ;
}
Std_ReturnType Spi_Read_byte_noblock(const mssp_spi_t *spi, uint8 *data){
    Std_ReturnType ret= E_NOT_OK ; 
    if(NULL== spi ){
        ret = E_NOT_OK ;
        
    }else{
         
         if(SSPSTATbits.BF == MSSP_SPI_BUFFER_EMPTY){
         //nothing
             ret= E_NOT_OK; 
         }else{
          *data = SSPBUF ; 
          ret= E_OK; 
         }
       
        
    }
    return ret ;
}
Std_ReturnType Spi_Write_byte_noblock(const mssp_spi_t *spi, uint8 data){
    Std_ReturnType ret= E_NOT_OK ; 
    if(NULL== spi ){
        ret = E_NOT_OK ;
        
    }else{
        SSPBUF = data ;
        if(PIR1bits.SSPIF == 0){
            ret = E_NOT_OK ; 
        //nothing
        }else{
        MSSP_SPI_CLEAR_FLAG();
        ret= E_OK; 
        }
         
        
    }
    return ret ;
}
static void spi_interrupt_configuration(const mssp_spi_t *spi){
    
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         MSSP_SPI_INTERRUPT_ENABLE();
         MSSP_SPI_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == spi->priority_SPI){ 
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_SPI_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == spi->priority_SPI){ 
              INTERRUPT_GlobalInterruptLowEnable();
           MSSP_SPI_INTERRUPT_LOW_PRIORITY();
        }
        else{ /* Nothing */ }
#else
         INTERRUPT_PeripheralInterruptEnable();
          INTERRUPT_GlobalInterruptEnable();
#endif
        MSSP_SPI_INTERRUPT_HANDLERF = spi->MSSP_SPI_INTERRUPT_HANDLER ;
        
#endif
}
static void spi_master_mode_configuration(const mssp_spi_t *spi){
pin_config_t SDO = {.pin = PIN5 ,.port = PORTC_INDEX ,.direction = OUTPUT };
pin_config_t SDI = {.pin = PIN4 ,.port = PORTC_INDEX ,
                   .direction = INPUT  , .logic = LOGIC_LOW};
pin_config_t SKL = {.pin = PIN3 ,.port = PORTC_INDEX ,
                   .direction = OUTPUT  , .logic = LOGIC_LOW};
gpio_pin_intialize(&SDO);
gpio_pin_intialize(&SDI);
gpio_pin_intialize(&SKL);
}
static void spi_slave_mode_configuration(const mssp_spi_t *spi){
pin_config_t SDO = {.pin = PIN5 ,.port = PORTC_INDEX ,.direction = OUTPUT };
pin_config_t SDI = {.pin = PIN4 ,.port = PORTC_INDEX ,
                   .direction = INPUT  , .logic = LOGIC_LOW};
pin_config_t SKL = {.pin = PIN3 ,.port = PORTC_INDEX ,
                   .direction = INPUT  , .logic = LOGIC_LOW};
pin_config_t SS_PIN= {.pin = PIN5 ,.port = PORTA_INDEX ,
                   .direction = INPUT  , .logic = LOGIC_LOW};
gpio_pin_intialize(&SDO);
gpio_pin_intialize(&SDI);
gpio_pin_intialize(&SKL);
if(MSSP_SPI_SLAVE_CLK_SS_ENABL ==spi->spi_mode ){
gpio_pin_intialize(&SS_PIN);
}else{
/*nothing*/
}
}
void MSSP_Spi_ISR(void){
  MSSP_SPI_CLEAR_FLAG();
  if(MSSP_SPI_INTERRUPT_HANDLERF){
  MSSP_SPI_INTERRUPT_HANDLERF();
  }else{
  /*nothing*/
  }

}