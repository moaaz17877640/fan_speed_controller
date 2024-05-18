#include "ecu_init.h"
//#define HWREG8(_X)  (*((volatile unsigned char *)(_X)))
//#define MOAZ_LATC (HWREG8(0xF8B))
//#define MOAZ_TRISC (HWREG8(0xF94))
//#define HWREG8(_X)  (*((volatile unsigned char *)(_X)))
//#define MOAZ_LATC (HWREG8(0xF8B))
//#define MOAZ_TRISC (HWREG8(0xF94))
//keypad_t keypad_1 ={
// .pad_row[0].direction = OUTPUT ,
//.pad_row[0].pin = PIN0 ,
//.pad_row[0].port =PORTC_INDEX  ,
//.pad_row[0].logic = LOGIC_LOW ,
//.pad_row[1].direction = OUTPUT ,
//.pad_row[1].pin = PIN1 ,
//.pad_row[1].port =PORTC_INDEX  ,
//.pad_row[1].logic = LOGIC_LOW ,
//.pad_row[2].direction = OUTPUT ,
//.pad_row[2].pin = PIN2 ,
//.pad_row[2].port =PORTC_INDEX  ,
//.pad_row[2].logic = LOGIC_LOW ,
//.pad_row[3].direction = OUTPUT ,
//.pad_row[3].pin = PIN3 ,
//.pad_row[3].port =PORTC_INDEX  ,
//.pad_row[3].logic = LOGIC_LOW ,
//.pad_column[0].direction = INPUT ,
//.pad_column[0].pin = PIN4 ,
//.pad_column[0].port =PORTC_INDEX  ,
//.pad_column[0].logic = LOGIC_LOW ,
//.pad_column[1].direction = INPUT ,
//.pad_column[1].pin = PIN5 ,
//.pad_column[1].port =PORTC_INDEX  ,
//.pad_column[1].logic = LOGIC_LOW ,
//.pad_column[2].direction = INPUT ,
//.pad_column[2].pin = PIN6 ,
//.pad_column[2].port =PORTC_INDEX  ,
//.pad_column[2].logic = LOGIC_LOW ,
//.pad_column[3].direction = INPUT ,
//.pad_column[3].pin = PIN7 ,
//.pad_column[3].port =PORTC_INDEX  ,
//.pad_column[3].logic = LOGIC_LOW ,
//};
//Segment_t seg_1 ={
//    .seg__pins[0].pin = PIN0 ,
//    .seg__pins[0].port =PORTC_INDEX ,
//    .seg__pins[0].direction =OUTPUT ,
//    .seg__pins[0].logic = LOGIC_LOW ,
//    .seg__pins[1].pin = PIN1 ,
//    .seg__pins[1].port =PORTC_INDEX ,
//    .seg__pins[1].direction =OUTPUT ,
//    .seg__pins[1].logic = LOGIC_LOW ,
//    .seg__pins[2].pin = PIN2 ,
//    .seg__pins[2].port =PORTC_INDEX ,
//    .seg__pins[2].direction =OUTPUT ,
//    .seg__pins[2].logic = LOGIC_LOW ,
//    .seg__pins[3].pin = PIN3 ,
//    .seg__pins[3].port =PORTC_INDEX ,
//    .seg__pins[3].direction =OUTPUT ,
//    .seg__pins[3].logic = LOGIC_LOW ,
//    .type = COMMON_ANODE
//};
//led_t red ={
//    .pin = PIN2 ,
//    .port = PORTD_INDEX ,
//    .statu = LED_OFF
//};
//led_t green ={
//    .pin = PIN3 ,
//    .port = PORTD_INDEX ,
//    .statu = LED_OFF
//};
//led_t yellow ={
//    .pin = PIN4 ,
//    .port = PORTD_INDEX ,
//    .statu = LED_OFF
//};
//pin_config_t seg_1_en = {
//  .port =PORTD_INDEX ,
//  .pin = PIN0,
//  .direction = OUTPUT ,
//  .logic =LOGIC_HIGH
//};
//pin_config_t seg_2_en = {
//  .port =PORTD_INDEX ,
//  .pin = PIN1,
//  .direction = OUTPUT ,
//  .logic =LOGIC_HIGH
//};
//pin_config_t led_1 = {
//    .port = PORTC_INDEX,
//    .pin = PIN0,
//    .logic = LOGIC_LOW,
//    .direction = OUTPUT
//};
//pin_config_t led_2 = {
//    .port = PORTC_INDEX,
//    .pin = PIN1,
//    .logic = LOGIC_LOW,
//    .direction = OUTPUT
//};
//pin_config_t led_3 = {
//    .port = PORTC_INDEX,
//    .pin = PIN2,
//    .logic = LOGIC_LOW,
//    .direction = OUTPUT
//};
//Std_ReturnType ret = E_OK;
//
//led_t led1 = {
//    .pin = PIN0,
//    .port = PORTC_INDEX,
//    .statu = LED_OFF
//};
//led_t led2 = {
//    .pin = PIN1,
//    .port = PORTC_INDEX,
//    .statu = LED_OFF
//};
//button_t btn_2 = {
//.button_pin.port =PORTC_INDEX ,
//.button_pin.direction =  INPUT , 
//.button_pin.pin = PIN2  ,
//.button_pin.logic = LOGIC_LOW ,
//.active = BUTTON_ACTIVE_LOW ,
//.btn_state = BUTTON_RELEASED
//};
//
//button_t btn_1 = {
//.button_pin.port =PORTD_INDEX ,
//.button_pin.direction =  INPUT , 
//.button_pin.pin = PIN0  ,
//.button_pin.logic = LOGIC_LOW ,
//.active = BUTTON_ACTIVE_LOW ,
//.btn_state = BUTTON_RELEASED
//};
//button_state_t states =  BUTTON_RELEASED;
//button_state_t states_2 =  BUTTON_PRESSED;
//relay_t relay1 = {
//.relay_pin = PIN0 ,
//.relay_port = PORTC_INDEX ,
//.relay_status =RELAY_OFF_STATUS 
//};
//relay_t relay2 = {
//.relay_pin = PIN1 ,
//.relay_port = PORTC_INDEX , 
//.relay_status =RELAY_OFF_STATUS 
//};


//motor_t motor_2 ={ 
// .motors[0].pin= PIN2 ,
// .motors[0].port = PORTC_INDEX ,
// .motors[0].logic = MOTOR_OFF_STATUS ,
// .motors[0].direction = OUTPUT , 
// .motors[1].pin = PIN3 ,
// .motors[1].port = PORTC_INDEX ,
// .motors[1].logic = MOTOR_OFF_STATUS ,
// .motors[1].direction = OUTPUT ,
//};
//Std_ReturnType ret = E_NOT_OK ;
//uint8 valu[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
//uint8 bas , ten ;

//=======================================================================

//    ret = gpio_port_direction_intialize(PORTC_INDEX, 0x00);
//    ret = button_initalize(&btn_1);
//    ret = button_initalize(&btn_2);
//
//    button_read_state(&btn_1,&states);
//    button_read_state(&btn_2,&states_2);
//    
//    ret = relay_initalize(&relay1);
//     ret = relay_initalize(&relay2);

//=======================================================================
//    while(1){
////        ret = motor_move_right(&motor_1);
////        ret = motor_move_right(&motor_2);
////        __delay_ms(7000);
////         ret = motor_move_left(&motor_1);
////        ret = motor_move_left(&motor_2);
////        __delay_ms(7000);
////         ret = motor_stop(&motor_1);
////        ret = motor_stop(&motor_2);
////        __delay_ms(7000);
////     ret = motor_move_right(&motor_1);
////      ret = motor_move_left(&motor_2);
////        __delay_ms(7000);
////         ret = motor_move_right(&motor_2);
////      ret = motor_move_left(&motor_1);
////      __delay_ms(7000);
////       ret = motor_stop(&motor_1);
////        ret = motor_stop(&motor_2);
////        __delay_ms(7000);
//    }
//     for(ten = 0 ; ten <= 9 ;ten ++){
//      for(bas = 0 ; bas <= 9 ;bas ++){
//      gpio_port_write_logic(PORTC_INDEX ,valu[bas]);
//   gpio_port_write_logic(PORTD_INDEX ,valu[ten] );
//   __delay_ms(100);
//     }
//     }
     
//     for(int i = 0 ; i<= 99 ;i++){
//         int num = (i%10) |((i/10)<<4);
//         gpio_port_write_logic(PORTC_INDEX , num);
//         __delay_ms(200);
//     }
//     while(1){
//       gpio_port_write_logic(PORTC_INDEX , 0x3);
//     }
//     uint8 green_counter =90 , red_counter =60 , yellow_counter =30 ,counter =0 ;
//     while(1){
//         while (red_counter >= 0) {
//        for(counter = 0; counter <=99 ; counter++){
//            led_on(&red);
//             Segment_Write_number(&seg_1 ,(uint8)(red_counter %10));
//            gpio_pin_write_logic(&seg_2_en , LOGIC_LOW); 
//             __delay_ms(10);
//             gpio_pin_write_logic(&seg_2_en , LOGIC_HIGH); 
//             Segment_Write_number(&seg_1 ,(uint8)(red_counter /10));
//             gpio_pin_write_logic(&seg_1_en , LOGIC_LOW);
//             __delay_ms(10);
//              gpio_pin_write_logic(&seg_1_en , LOGIC_HIGH);
//              led_off(&red);
//        } 
//        red_counter--;
//         }
//        for(green_counter = 60; green_counter >=0 ; green_counter --){
//           led_on(&green);
//             Segment_Write_number(&seg_1 ,(uint8)(green_counter %10));
//            gpio_pin_write_logic(&seg_2_en , LOGIC_LOW); 
//             __delay_ms(500);
//             gpio_pin_write_logic(&seg_2_en , LOGIC_HIGH); 
//             Segment_Write_number(&seg_1 ,(uint8)(green_counter /10));
//             gpio_pin_write_logic(&seg_1_en , LOGIC_LOW);
//             __delay_ms(500);
//              gpio_pin_write_logic(&seg_1_en , LOGIC_HIGH);
//              
//              led_off(&green);
//        } 
//        for(yellow_counter = 30; yellow_counter >=0 ; yellow_counter --){
//            led_on(&yellow);
//             Segment_Write_number(&seg_1 ,(uint8)(yellow_counter %10));
//            gpio_pin_write_logic(&seg_2_en , LOGIC_LOW); 
//             __delay_ms(500);
//             gpio_pin_write_logic(&seg_2_en , LOGIC_HIGH); 
//             Segment_Write_number(&seg_1 ,(uint8)(yellow_counter /10));
//             gpio_pin_write_logic(&seg_1_en , LOGIC_LOW);
//             __delay_ms(500);
//              gpio_pin_write_logic(&seg_1_en , LOGIC_HIGH);
//              
//              led_off(&yellow);
//        } 
//        
//     }
//=======================================================================
//    gpio_port_direction_intialize(PORTC_INDEX ,0x80 );
//   gpio_port_direction_intialize(PORTD_INDEX ,0x80);
   //gpio_port_write_logic(PORTC_INDEX , 0xF9);
    // gpio_port_write_logic(PORTD_INDEX , 0xF8);
//    gpio_port_direction_intialize(PORTC_INDEX , 0xF0);
//    gpio_port_direction_intialize(PORTD_INDEX , 0x00);
//    gpio_port_direction_intialize(PORTD_INDEX ,0XFC); 
//    Segment_initalize(&seg_1);
//    led_intalize(&red);
//    led_intalize(&green);
//    led_intalize(&yellow);
//=======================================================================
 ///test traFFIC LINE SIGNAL
//=======================================================================
/*
 pin_config_t seg1_en = {
    .port = PORTD_INDEX,
    .pin = PIN1,
    .direction = OUTPUT,
    .logic = LOGIC_HIGH
};
pin_config_t seg2_en = {
    .port = PORTD_INDEX,
    .pin = PIN0,
    .direction = OUTPUT,
    .logic = LOGIC_HIGH
};
led_t red = {
    .pin = PIN2,
    .port = PORTD_INDEX,
    .statu = LED_OFF
};
led_t green = {
    .pin = PIN4,
    .port = PORTD_INDEX,
    .statu = LED_OFF
};
led_t yellow = {
    .pin = PIN3,
   Segment_t seg_1 = {
    .seg__pins[0].pin = PIN0,
    .seg__pins[0].port = PORTC_INDEX,
    .seg__pins[0].direction = OUTPUT,
    .seg__pins[0].logic = LOGIC_LOW,
    .seg__pins[1].pin = PIN1,
    .seg__pins[1].port = PORTC_INDEX,
    .seg__pins[1].direction = OUTPUT,
    .seg__pins[1].logic = LOGIC_LOW,
    .seg__pins[2].pin = PIN2,
    .seg__pins[2].port = PORTC_INDEX,
    .seg__pins[2].direction = OUTPUT,
    .seg__pins[2].logic = LOGIC_LOW,
    .seg__pins[3].pin = PIN3,
    .seg__pins[3].port = PORTC_INDEX,
    .seg__pins[3].direction = OUTPUT,
    .seg__pins[3].logic = LOGIC_LOW,
    .type = COMMON_ANODE
}; .port = PORTD_INDEX,
    .statu = LED_OFF
};
Segment_t seg_1 = {
    .seg__pins[0].pin = PIN0,
    .seg__pins[0].port = PORTC_INDEX,
    .seg__pins[0].direction = OUTPUT,
    .seg__pins[0].logic = LOGIC_LOW,
    .seg__pins[1].pin = PIN1,
    .seg__pins[1].port = PORTC_INDEX,
    .seg__pins[1].direction = OUTPUT,
    .seg__pins[1].logic = LOGIC_LOW,
    .seg__pins[2].pin = PIN2,
    .seg__pins[2].port = PORTC_INDEX,
    .seg__pins[2].direction = OUTPUT,
    .seg__pins[2].logic = LOGIC_LOW,
    .seg__pins[3].pin = PIN3,
    .seg__pins[3].port = PORTC_INDEX,
    .seg__pins[3].direction = OUTPUT,
    .seg__pins[3].logic = LOGIC_LOW,
    .type = COMMON_ANODE
};

 
 ==============================================================
 * ==============================================================
 *  uint8 i = 0, l = 0, c = 0;
    app_initialize();
    while (1) {
        while (1) {
            for (int j = 0; j <= 50; j++) {

                Segment_Write_number(&seg_1, i % 10);
                gpio_pin_write_logic(&seg1_en, LOGIC_HIGH);
                __delay_ms(10);
                gpio_pin_write_logic(&seg1_en, LOGIC_LOW);
                Segment_Write_number(&seg_1, i / 10);
                gpio_pin_write_logic(&seg2_en, LOGIC_HIGH);

                __delay_ms(10);
                gpio_pin_write_logic(&seg2_en, LOGIC_LOW);

            }
            i++;
            c++;
            for (l = 0; l < 3; l++) {

                if ((c <= 60)&&(l == 0)) {
                    led_on(&red);
                    led_off(&green);
                    led_off(&yellow);

                } else if ((c % 60 == 0)&&(l == 1)) {
                    led_off(&red);
                    led_off(&green);
                    led_on(&yellow);
                    i = 0;
                } else if ((c == 120)&&(l == 2)) {
                    led_off(&red);
                    led_on(&green);
                    led_off(&yellow);
                    i = 0;

                } else if (c >= 180) {
                    c = 0;
                }


            }

        }

    }

    return (EXIT_SUCCESS);
}

void app_initialize(void) {

    Std_ReturnType ret = E_NOT_OK;
    ret = Segment_initalize(&seg_1);
    ret = gpio_pin_intialize(&seg1_en);
    ret = gpio_pin_intialize(&seg2_en);
    ret = led_intalize(&red);
    ret = led_intalize(&green);
    ret = led_intalize(&yellow);
}
 * 
 * 
 * ======================================================
 * CHARACTER_LCD 
 * 
 * 
 * chr_lcd_8bit_t lcd_2 = {
  .pin_Rs.port = PORTC_INDEX,
   .pin_Rs.pin = PIN6,
   .pin_Rs.direction = OUTPUT,
   .pin_Rs.logic =LOGIC_LOW,
   .pin_en.port = PORTC_INDEX,
   .pin_en.pin = PIN7,
   .pin_en.direction = OUTPUT,
   .pin_en.logic = LOGIC_LOW,
    
  .lcd_pins[0].port = PORTD_INDEX,
  .lcd_pins[0].logic = LOGIC_LOW,
  .lcd_pins[0].direction = OUTPUT,
  .lcd_pins[0].pin = PIN0,
   
  .lcd_pins[1].port = PORTD_INDEX,
  .lcd_pins[1].pin = PIN1,
  .lcd_pins[1].direction = OUTPUT,
   .lcd_pins[1].logic = LOGIC_LOW,
   
   .lcd_pins[2].port = PORTD_INDEX,
    .lcd_pins[2].pin = PIN2,
  .lcd_pins[2].direction = OUTPUT,
  .lcd_pins[2].logic = LOGIC_LOW,
   
   .lcd_pins[3].port = PORTD_INDEX,
   .lcd_pins[3].pin = PIN3,
   .lcd_pins[3].direction = OUTPUT,
   .lcd_pins[3].logic = LOGIC_LOW,
   
   .lcd_pins[4].port = PORTD_INDEX,
   .lcd_pins[4].pin = PIN4,
  .lcd_pins[4].direction = OUTPUT,
   .lcd_pins[4].logic = LOGIC_LOW,
   
  .lcd_pins[5].port = PORTD_INDEX,
   .lcd_pins[5].pin = PIN5,
   .lcd_pins[5].direction = OUTPUT,
   .lcd_pins[5].logic = LOGIC_LOW,
   
  .lcd_pins[6].port = PORTD_INDEX,
   .lcd_pins[6].pin = PIN6,
  .lcd_pins[6].direction = OUTPUT,
   .lcd_pins[6].logic = LOGIC_LOW,
  
   .lcd_pins[7].port = PORTD_INDEX,
   .lcd_pins[7].pin = PIN7,
   .lcd_pins[7].direction = OUTPUT,
   .lcd_pins[7].logic = LOGIC_LOW
          
};
 Std_ReturnType ret = E_NOT_OK;
 uint8 customChar[] = {
  0x00,
  0x00,
  0x0A,
  0x15,
  0x11,
  0x0A,
  0x04,
  0x00
};
 
  uint8 num= 253 ;
    uint8 str[4];
    ret = convert_uint8_to_string(num , str);
    ret = lcd_8bit_send_custom_char(&lcd_2 , 1 ,12 , customChar , 0);
    __delay_ms(1000);
 
 * 
 * ==========================================================
 * keypad_t keypad_1 ={
 .pad_row[0].direction = OUTPUT ,
.pad_row[0].pin = PIN0 ,
.pad_row[0].port =PORTC_INDEX  ,
.pad_row[0].logic = LOGIC_LOW ,
.pad_row[1].direction = OUTPUT ,
.pad_row[1].pin = PIN1 ,
.pad_row[1].port =PORTC_INDEX  ,
.pad_row[1].logic = LOGIC_LOW ,
.pad_row[2].direction = OUTPUT ,
.pad_row[2].pin = PIN2 ,
.pad_row[2].port =PORTC_INDEX  ,
.pad_row[2].logic = LOGIC_LOW ,
.pad_row[3].direction = OUTPUT ,
.pad_row[3].pin = PIN3 ,
.pad_row[3].port =PORTC_INDEX  ,
.pad_row[3].logic = LOGIC_LOW ,
.pad_column[0].direction = INPUT ,
.pad_column[0].pin = PIN4 ,
.pad_column[0].port =PORTC_INDEX  ,
.pad_column[0].logic = LOGIC_LOW ,
.pad_column[1].direction = INPUT ,
.pad_column[1].pin = PIN5 ,
.pad_column[1].port =PORTC_INDEX  ,
.pad_column[1].logic = LOGIC_LOW ,
.pad_column[2].direction = INPUT ,
.pad_column[2].pin = PIN6 ,
.pad_column[2].port =PORTC_INDEX  ,
.pad_column[2].logic = LOGIC_LOW ,
.pad_column[3].direction = INPUT ,
.pad_column[3].pin = PIN7 ,
.pad_column[3].port =PORTC_INDEX  ,
.pad_column[3].logic = LOGIC_LOW ,
};
Std_ReturnType ret = E_NOT_OK;
uint8 value = 0;
 ====================================================================
 * 
 * interrupt test 
 * led_t led1 ={
    .pin = PIN0 ,
    .port = PORTC_INDEX ,
    .statu = LED_OFF
};
led_t led2 ={
    .pin = PIN1,
    .port = PORTC_INDEX ,
    .statu = LED_OFF
};
volatile uint8 pro =0 ;
void int_isr(void){
    pro++;
}
void program1(void){
  led_on(&led1);

}
void program2(void){
  led_on(&led2);

}
INTX_interrupt_t int_ = {
    .EXT_InterruptHandler = int_isr ,
    .edge= INTERRUPT_RISING_EDGE , 
    .priority = PRIORITY_HIGH , 
    .source = INTERRUPT_INT0 ,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.direction = INPUT ,
    .mcu_pin.logic = LOGIC_LOW , 
    .mcu_pin.pin = PIN0 
};
 * 
 * 
 * 
 * ======================================================================
 * TIMER 0 
 * led_t red ={
    .pin = PIN0 ,
    .port = PORTC_INDEX ,
    .statu = LED_ON
};
Timer0_t tmr_ = {
.Prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG , 
.timer0_mode = TIMER0_TIMER_CFG , 
.TIMER0_INTERRUPT_HANDLER = TMR_INTERRUPTHANDLER ,
.timer_register_size = TIMER0_16BIT_CFG  ,
.Prescaler_value = PRESCALER_DIV_8 , 
.timer0_preload_value = 3036 ,
};
 */


//========================================================================
//        Timer2_t TMR_OB;
//        TMR_OB.TIMER2_INTERRUPT_HANDLER = timer_1_isr;
//        TMR_OB.postscaler_valu = TIMER2_POSTSCALER_DIV_13 ;
//        TMR_OB.prescaler_valu = TIMER2_PRESCALER_DIV_16 ;
//        TMR_OB.preload_value =240 ;
//        TMR2_Init(&TMR_OB);
//    Timer1_t tmr_1;
//tmr_1.TIMER1_INTERRUPT_HANDLER = timer_1_isr;
//tmr_1.timer1_priority = INTERRUPT_LOW_PRIORITY ;
//tmr_1.timer1_mode = TIMER1_COUNTER_MODE_CFG ;
//tmr_1.Prescaler_value = TIMER1_PRESCALER_DIV_1;
//tmr_1.timer1_preload_value = 0 ;
//tmr_1.timer1_register_size =TIMER1_16_RW_reg;
//tmr_1.counter_mode = TIMER1_SYNCHRONOUS_mode;
//tmr_1.timer1_osc_cfg = TIMER1_Disable_osc_cfg
//TMR1_Init(&tmr_1);
//  Timer0_t tmr_1;
//tmr_1.Prescaler_enable   =TIMER0_PRESCALER_ENABLE_CFG ;
//tmr_1.TIMER0_INTERRUPT_HANDLER = timer_1_isr ;
//tmr_1.timer_register_size =TIMER0_8BIT_CFG ;
//tmr_1.counter_edge =TIMER0_RISING_EDGE_CFG ;
//tmr_1.timer0_mode = TIMER0_TIMER_CFG ;
//tmr_1.Prescaler_value = PRESCALER_DIV_8 ;
//tmr_1.timer0_preload_value = 3036 ;
//TMR0_Init(&tmr_1);
//  interrupt_INTx_t int_ ;
//    int_.EXT_InterruptHandler = timer_1_isr ;
//    int_.edge= INTERRUPT_RAISING_EDGE , 
//    int_.priority = INTERRUPT_HIGH_PRIORITY ; 
//    int_.src = INTERRUPT_EXTERNAL_INT0 ;
//    int_.mcu_pin.port = PORTB_INDEX;
//    int_.mcu_pin.direction = INPUT ;
//    int_.mcu_pin.logic = LOGIC_LOW ; 
//    int_.mcu_pin.pin = PIN0 ;
//    Interrupt_INTx_Init(&int_);

//led_t led_1 = {.pin = PIN0 , .port= PORTC_INDEX , .statu = LED_OFF };
//led_t led_2 = {.pin = PIN1 , .port= PORTC_INDEX , .statu = LED_OFF };
//led_t led_3 = {.pin = PIN2 , .port= PORTC_INDEX , .statu = LED_OFF };
//led_t led_4 = {.pin = PIN3 , .port= PORTC_INDEX , .statu = LED_OFF };
//volatile uint8 counter = ZERO_INIT ;
//void TMR_Isr(void){
//   counter++;
//     led_toggle(&led_1);
//     led_toggle(&led_2);
//      led_toggle(&led_3);
//       led_toggle(&led_4);
// 
//}
//
//void leds_init(void){
//    led_intalize(&led_1);
//    led_intalize(&led_2);
//    led_intalize(&led_3);
//    led_intalize(&led_4);
//    
//}
//
//Timer0_t int0 ;
//void interrupt_init0(void){
//    int0.Prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG ;
//    int0.Prescaler_value = PRESCALER_DIV_4 ;
//    int0.TIMER0_INTERRUPT_HANDLER =TMR_Isr ;
//    //int0.counter_edge = TIMER0_RISING_EDGE_CFG ;
//    int0.timer0_mode  = TIMER0_TIMER_CFG ;
//    int0.timer0_preload_value= 3036 ;
//    int0.timer_register_size = TIMER0_8BIT_CFG ;
//    TMR0_Init(&int0);
//}
////Timer1_t int1 ;
////void interrupt_init1(void){
////int1.Prescaler_value = TIMER1_PRESCALER_DIV_1 ;
////int1.TIMER1_INTERRUPT_HANDLER = TMR_Isr ;
////int1.counter_mode =TIMER1_SYNCHRONOUS_mode ;
////int1.timer1_mode =  TIMER1_COUNTER_MODE_CFG ;
////int1.timer1_osc_cfg = TIMER1_Enable_osc_cfg ;
////int1.timer1_preload_value = 0 ;
////int1.timer1_register_size = TIMER1_16_RW_reg ;
////TMR1_Init(&int1);
////}
////Timer2_t tm2;
////void interrupt_init2(void){
////tm2.TIMER2_INTERRUPT_HANDLER = TMR_Isr ;
////tm2.postscaler_valu =  TIMER2_POSTSCALER_DIV_7;
////tm2.prescaler_valu =TIMER2_PRESCALER_DIV_16 ;
////tm2.preload_value = 223 ;
////TMR2_Init(&tm2);
////}
////Timer3_t tm3;
////void interrupt_init3(void){
////    tm3.Prescaler_value = TIMER3_PRESCALER_DIV_4 ;
////    tm3.TIMER3_INTERRUPT_HANDLER =TMR_Isr ;
////    tm3.timer3_mode = TIMER3_timer_mode_cfg ;
////    tm3.timer3_preload_value = 3036 ;
////    tm3.timer3_register_size =TIMER3_rd_8bit_cfg ;
////    TMR3_Init(&tm3);
////}

//Timer1_t int1 ;
//void interrupt_init1(void){
//int1.Prescaler_value = TIMER1_PRESCALER_DIV_1 ;
//int1.TIMER1_INTERRUPT_HANDLER = NULL ;
////int1.counter_mode =TIMER1_SYNCHRONOUS_mode ;
//int1.timer1_mode =  TIMER1_TIMER_MODE_CFG ;
//int1.timer1_osc_cfg = TIMER1_Disable_osc_cfg ;
//int1.timer1_preload_value = 0 ;
//int1.timer1_register_size = TIMER1_16_RW_reg ;
//TMR1_Init(&int1);
//}
//void TMR_ISR(void){
//    TMR1_Write_value(&int1 , 0);
//}
//led_t led_1 = {.pin = PIN0 , .port= PORTC_INDEX , .statu = LED_OFF };
//ccp_t ccp_obj ;
//void ccp_init(void){
//ccp_obj.CCP1_INTERRUPT_HANDLER =TMR_ISR ;
//ccp_obj.CCP2_INTERRUPT_HANDLER = NULL ;
//ccp_obj.CCP_Mode = CCP_MODULE_COMPARE_MODE ;
//ccp_obj.Sub_mode = Compare_Mode_Toggle_Output ;
//ccp_obj.ccp_inst= CCP1_INST ;
//ccp_obj.ccp_pin.direction = OUTPUT ;
//ccp_obj.ccp_pin.logic = LOGIC_LOW ;
//ccp_obj.ccp_pin.pin =PIN2;
//ccp_obj.ccp_pin.port =PORTC_INDEX ;
//ccp_obj.tmr =TIMER1_FOR_CCP1_CCP2 ;
//compare_set_value(&ccp_obj , 50000);
//CCP_INIt(&ccp_obj);
//}
