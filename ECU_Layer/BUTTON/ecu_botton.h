/* 
 * File:   ecu_botton.h
 * Author: MOAAZ
 *
 * Created on January 9, 2024, 10:59 PM
 */

#ifndef ECU_BOTTON_H
#define	ECU_BOTTON_H
/* SECTION : includes*/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* SECTION :macro declarations */

/* SECTION : macro function declarations */

/* SECTION : datatype declarations */

/* SECTION : functions declaration*/
typedef enum{
    BUTTON_PRESSED , 
            BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW,
            BUTTON_ACTIVE_HIGH
}button_active_t;
typedef struct{
pin_config_t button_pin ; 
 button_state_t btn_state ;
 button_active_t active ;
}button_t;
    



Std_ReturnType button_initalize(button_t *btn );
Std_ReturnType button_read_state(button_t *btn , button_state_t *state);
#endif	/* ECU_BOTTON_H */

