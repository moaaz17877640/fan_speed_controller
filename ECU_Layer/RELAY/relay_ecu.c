/* 
 * File:   relay_ecu .c
 * Author: MOAAZ
 *
 * Created on January 22, 2024, 4:48 PM
 */
/* SECTION : includes*/
#include "relay_ecu.h"
/* SECTION : functions definition*/
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_initalize(const relay_t *relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL==relay)
    {
        ret =E_NOT_OK ;
    }else
    {
         pin_config_t obj = { .direction =  OUTPUT , .pin = relay->relay_pin  ,
                            .port = relay->relay_port , .logic =  relay->relay_status ,
         };
        gpio_pin_intialize(&obj);
        ret = E_OK ;
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_on(const relay_t *relay ){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL==relay)
    {
        ret =E_NOT_OK ;
    }else
    { 
        pin_config_t obj = { .direction =  OUTPUT , .pin = relay->relay_pin  ,
                            .port = relay->relay_port , .logic =  relay->relay_status ,
         };
        gpio_pin_write_logic(&obj , LOGIC_HIGH);
        ret = E_OK ; 
        
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_off(const relay_t *relay ){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL==relay)
    {
        ret =E_NOT_OK ;
    }else
    {
          pin_config_t obj = { .direction =  OUTPUT , .pin = relay->relay_pin  ,
                            .port = relay->relay_port , .logic =  relay->relay_status ,
         };
        gpio_pin_write_logic(&obj , LOGIC_LOW);
        ret = E_OK ; 
        
    }
    return ret;
}
