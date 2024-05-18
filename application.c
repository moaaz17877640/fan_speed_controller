/*
 * File: application.c
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:21 PM
 */
#include "application.h"
volatile uint8 tmr1_counter = 0 ;
void  app_initialize(void);
motor_t motor_1 ={ 
 .motors[0].pin= PIN0 ,
 .motors[0].port = PORTD_INDEX ,
 .motors[0].logic = MOTOR_OFF_STATUS ,
 .motors[0].direction = OUTPUT , 
 .motors[1].pin = PIN1 ,
 .motors[1].port = PORTD_INDEX ,
 .motors[1].logic = MOTOR_OFF_STATUS ,
 .motors[1].direction = OUTPUT ,
};
 chr_lcd_4bit_t lcd_1 = {
  .pin_Rs.port = PORTC_INDEX,
   .pin_Rs.pin = PIN0,
   .pin_Rs.direction = OUTPUT,
   .pin_Rs.logic =LOGIC_LOW,
   .pin_en.port = PORTC_INDEX,
   .pin_en.pin = PIN1,
   .pin_en.direction = OUTPUT,
   .pin_en.logic = LOGIC_LOW,
    
  .lcd_pins[0].port = PORTC_INDEX,
  .lcd_pins[0].logic = LOGIC_LOW,
  .lcd_pins[0].direction = OUTPUT,
  .lcd_pins[0].pin = PIN3,
   
  .lcd_pins[1].port = PORTC_INDEX,
  .lcd_pins[1].pin = PIN4,
  .lcd_pins[1].direction = OUTPUT,
   .lcd_pins[1].logic = LOGIC_LOW,
   
   .lcd_pins[2].port = PORTC_INDEX,
    .lcd_pins[2].pin = PIN5,
  .lcd_pins[2].direction = OUTPUT,
  .lcd_pins[2].logic = LOGIC_LOW,
   
   .lcd_pins[3].port = PORTC_INDEX,
   .lcd_pins[3].pin = PIN6,
   .lcd_pins[3].direction = OUTPUT,
   .lcd_pins[3].logic = LOGIC_LOW,
 
};
 ADc_t temp_sens ={
 .ACD_INTERRUPT_HANDLER = NULL ,
 .channal =AN0_CHANNEL , 
 .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED ,
 .clock_con = FOSC_32 ,
 .time_aq = TAD20 ,
 .result_format = ADC_RIGHT_FORMAT
 };
 Timer2_t tm2;
void TMR_INIT(void){
tm2.TIMER2_INTERRUPT_HANDLER = NULL ;
tm2.postscaler_valu =  TIMER2_POSTSCALER_DIV_1;
tm2.prescaler_valu =TIMER2_PRESCALER_DIV_1 ;
tm2.preload_value = 0 ;
TMR2_Init(&tm2);
}
 ccp_t ccp_obj ;
void ccp_init(void){
ccp_obj.PWM_Freq =5000 ;
ccp_obj.CCP_Mode = CCP_MODULE_PWM_MODE ;
ccp_obj.Sub_mode = PWM_Mode ;
ccp_obj.ccp_inst= CCP1_INST ;
ccp_obj.timer2_postscaler = CCP_TIMER2_POSTSCALER_DIV_1 ;
ccp_obj.timer2_prescaler =CCP_TIMER2_PRESCALER_DIV_1   ;
ccp_obj.ccp_pin.direction = OUTPUT ;
ccp_obj.ccp_pin.logic = LOGIC_LOW ;
ccp_obj.ccp_pin.pin =PIN2;
ccp_obj.ccp_pin.port =PORTC_INDEX ;
CCP_INIt(&ccp_obj);
START_PWM(&ccp_obj);
}
Std_ReturnType ret = E_NOT_OK;
uint16 sens_res = 0;
uint16 degr_cel=0 ;
uint8 fan_mode = 0;
uint8 str[6] ;
int main() {
    TMR_INIT();
    ccp_init();
     app_initialize();
    ret|= Adc_start_conversion(&temp_sens);
//  5 MODES  0 STOP --TO --5 HIGHEST SPEED
    while(1){
       ret|= ADC_GetConversion_Blocking(&temp_sens ,AN0_CHANNEL, &sens_res);
       degr_cel = (sens_res * 4.88f) ;
       degr_cel/=10.0;
       ret|= lcd_4bit_send_data_string_posit(&lcd_1 , 1 , 1 , "temp =");
        ret|=convert_uint16_to_string(degr_cel ,str );
        ret|=lcd_4bit_send_data_string_posit(&lcd_1 , 1 , 8 , str);
       // lcd_4bit_send_data_string_posit(&lcd_1 , 2 , 1 , "fan");
       ret|= lcd_4bit_send_data_string_posit(&lcd_1 , 2 , 2, "st speed mode");
        if(degr_cel > 80){
            ret|=PWM_set_Duty(100, &ccp_obj);
           ret|= motor_move_left(&motor_1);
            fan_mode ='4';
         
        }else if(degr_cel >= 50 && degr_cel < 80){
          ret|=  PWM_set_Duty(80, &ccp_obj);
           ret|= motor_move_left(&motor_1);
          fan_mode ='3';
         
        }else if(degr_cel >= 30 && degr_cel <50){
           ret|= PWM_set_Duty(80, &ccp_obj);
            ret|=motor_move_left(&motor_1);
          fan_mode ='2';
         
        }else if(degr_cel >= 20){
          ret|=  PWM_set_Duty(60, &ccp_obj);
           ret|= motor_move_left(&motor_1);
         fan_mode ='1';
        }
        else{
        ret|= PWM_set_Duty(0, &ccp_obj);
          ret|=  motor_stop(&motor_1);
       fan_mode ='0';
        }
       ret|= lcd_4bit_send_data_char_posit(&lcd_1 , 2 , 1 ,fan_mode );
        if(fan_mode){
       ret|= lcd_4bit_send_data_string_posit(&lcd_1 , 1 , 11 , "fan on");
        }else{
       ret|= lcd_4bit_send_data_string_posit(&lcd_1 , 1 , 11 , "fan off");
        }
        
     
    }
   
     return (EXIT_SUCCESS);
}

void  app_initialize(void) {
  Std_ReturnType ret = E_NOT_OK;
  ret|=lcd_4bit_initialize(&lcd_1);
 ret|=motor_initialize(&motor_1);
 ret|= ADC_INIT(&temp_sens);

}