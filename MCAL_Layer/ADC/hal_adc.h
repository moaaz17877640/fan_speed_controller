/* 
 * File:   hal_adc.h
 * Author: MOAAZ
 *
 * Created on February 25, 2024, 5:21 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* section include */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "hal_adc_cfg.h"
#include "../../MCAL_Layer/Interrupt/mcal_interrupt_config.h"
/* section datatype declartion */
typedef enum{
            AN0_CHANNEL,
            AN1_CHANNEL,
            AN2_CHANNEL, 
            AN3_CHANNEL,
            AN4_CHANNEL,
            AN5_CHANNEL,
            AN6_CHANNEL,
            AN7_CHANNEL,
            AN8_CHANNEL,
            AN9_CHANNEL,
            AN10_CHANNEL,
            AN11_CHANNEL,
            AN12_CHANNEL,       
}Adc_select_Channel_t;

typedef enum {
    TAD0,
            TAD2,
            TAD4,
            TAD6,
            TAD8,
            TAD12,
            TAD16,
            TAD20   
}Adc_time_Acquisition_t;
typedef enum{
    FOSC_2,
    FOSC_8,
    FOSC_32,
    FOSC_,
    FOSC_4 ,
    FOSC_16,
    FOSC_64,
}Adc_conversion_clock_t;

typedef struct{
 #if ADC_INTERRUPT_FEATURE_ENABLE_CFG == INTERRUPT_FEATURE_ENABLE
    void (*ACD_INTERRUPT_HANDLER)(void);
    interrupt_priority_cfg  priority ;
#endif
Adc_select_Channel_t channal;
Adc_time_Acquisition_t time_aq;
Adc_conversion_clock_t clock_con;
uint8 result_format : 1;
uint8 voltage_reference : 1;
uint8 Reserved  : 6;
}ADc_t;
Std_ReturnType ADC_INIT(const ADc_t *adc_obj);
Std_ReturnType ADC_DEINIT(const ADc_t *adc_obj);
Std_ReturnType Adc_select_Channel(const ADc_t *adc_obj ,Adc_select_Channel_t channal );
Std_ReturnType Adc_start_conversion(const ADc_t *adc_obj  );
Std_ReturnType Adc_is_conversion_done(const ADc_t *adc_obj , uint8 *conversion_status );
Std_ReturnType Adc_Get_conversion_result(const ADc_t *adc_obj , uint16 *conversion_result );
Std_ReturnType ADC_GetConversion_Blocking(const ADc_t *_adc, Adc_select_Channel_t channel, 
                                                             uint16 *conversion_result);
Std_ReturnType ADC_Conversion_interrupt(const ADc_t *adc_obj, Adc_select_Channel_t channel);
#endif	/* HAL_ADC_H */

