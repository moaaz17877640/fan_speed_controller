/* 
 * File:   ecu_dc_motor.c
 * Author: MOAAZ
 *
 * Created on January 25, 2024, 7:54 PM
 */
/* SECTION : includes*/
#include "ecu_dc_motor.h"
/* SECTION : datatype definition */

/* SECTION : functions definition */
Std_ReturnType motor_initialize(const motor_t *motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL== motor)
    {
    ret = E_NOT_OK ;
    }else
    {
        
          gpio_pin_intialize(&(motor->motors[0]));
          gpio_pin_intialize(&(motor->motors[1]));
     ret = E_OK ;
    }
    return ret;
}
Std_ReturnType motor_move_right(const motor_t *motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL== motor)
    {
    ret = E_NOT_OK ;
    }else
    {
        gpio_pin_write_logic(&(motor->motors[0]),LOGIC_HIGH);
        gpio_pin_write_logic(&(motor->motors[1]), LOGIC_LOW );
         ret = E_OK ;
        
    }
    return ret;
}
Std_ReturnType motor_move_left(const motor_t *motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL== motor)
    {
    ret = E_NOT_OK ;
    }else
    {
     gpio_pin_write_logic(&(motor->motors[0]),LOGIC_LOW);
        gpio_pin_write_logic(&(motor->motors[1]),LOGIC_HIGH);
         ret = E_OK ;
    }
    return ret;
}
Std_ReturnType   motor_stop(const motor_t *motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL== motor)
    {
    ret = E_NOT_OK ;
    }else
    {
     gpio_pin_write_logic(&(motor->motors[0]),LOGIC_LOW);
        gpio_pin_write_logic(&(motor->motors[1]),LOGIC_LOW);
        ret = E_OK ;
    }
    return ret;
}