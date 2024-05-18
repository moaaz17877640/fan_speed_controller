/* 
 * File:   ecu_led.c
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:36 PM
 */
#include "ecu_led.h"
Std_ReturnType led_intalize(const led_t *led)
{
Std_ReturnType ret = E_OK;
if(NULL==led){
    ret = E_NOT_OK;
}
else {
    pin_config_t obj ={ .port = led->port , .pin = led->pin , .logic =led->statu ,.direction = OUTPUT }  ;
    
    gpio_pin_intialize(&obj);
    
}
return ret;
}
Std_ReturnType led_on(const led_t *led){
Std_ReturnType ret = E_OK;
if(NULL==led)
{  ret = E_NOT_OK;
}
else {
pin_config_t obj ={ .port = led->port , .pin = led->pin , .logic =led->statu ,.direction = OUTPUT }  ;
    
    gpio_pin_write_logic(&obj,LOGIC_HIGH);
}
return ret;
}
Std_ReturnType led_off(const led_t *led){
Std_ReturnType ret = E_OK;
if(NULL==led)
{  ret = E_NOT_OK;}
else {
pin_config_t obj ={ .port = led->port , .pin = led->pin , .logic =led->statu ,.direction = OUTPUT }  ;
    
    gpio_pin_write_logic(&obj,LOGIC_LOW);}
return ret;

}
Std_ReturnType led_toggle(const led_t *led){

Std_ReturnType ret = E_OK;
if(NULL==led)

{  ret = E_NOT_OK;}
else {pin_config_t obj ={ .port = led->port , .pin = led->pin , .logic =led->statu ,.direction = OUTPUT }  ;
    
    gpio_pin_toggle_logic(&obj);}
return ret;

}
