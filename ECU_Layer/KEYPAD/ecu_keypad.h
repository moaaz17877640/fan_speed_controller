/* 
 * File:   ecu_keypad.h
 * Author: MOAAZ
 *
 * Created on February 10, 2024, 1:34 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
#define KEY_PAD_ROWS    4
#define KEY_PAD_COLUMNS  4
/* SECTION : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* SECTION : datatype declarations */
typedef struct{
    pin_config_t pad_row[KEY_PAD_ROWS];
    pin_config_t pad_column[KEY_PAD_COLUMNS];
}keypad_t;

/* SECTION : functions declaration*/
/**
 * 
 * @param keypad
 * @return Std_ReturnType ok if true n_ok if false 
 * @brief --> this interface for init the key_pad pins as input and output..
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad);
/**
 * 
 * @param keypad
 * @param value pointer to return value 
 * @return Std_ReturnType ok if true n_ok if false 
 * @brief --> used to return the value that  pressed on keypad  
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value );
#endif	/* ECU_KEYPAD_H */

