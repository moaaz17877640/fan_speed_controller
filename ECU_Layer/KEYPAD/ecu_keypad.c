/* 
 * File:   ecu_keypad.h
 * Author: MOAAZ
 *
 * Created on February 10, 2024, 1:34 PM
 */
/* SECTION : includes*/
#include "ecu_keypad.h"
/* SECTION : datatype declarations */
static const uint8 keypad_values[KEY_PAD_ROWS][KEY_PAD_COLUMNS] = { {'7' , '8' , '9','/'  }, 
                                                                    {'4' , '5' , '6','*'  }, 
                                                                    {'1' , '2' , '3','-'  },
                                                                    {'c' , '0' , '=','+'  }};
/* SECTION : functions DEFINITION */
/**
 * @param keypad
 * @return Std_ReturnType ok if true n_ok if false 
 * @brief --> this interface for init the key_pad pins as input and output..
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad){
Std_ReturnType ret = E_NOT_OK;
uint8 row_counter = 0 , column_counter =0 ;
    if(NULL==keypad)
    {
        ret =E_NOT_OK ;
    }else
    {
     for(row_counter = 0 ; row_counter < KEY_PAD_ROWS ; row_counter++ ){
            ret = gpio_pin_intialize(&(keypad->pad_row[row_counter]));
        }
         for(column_counter = 0 ; column_counter < KEY_PAD_COLUMNS ; column_counter++ ){
            ret = gpio_pin_direction_intialize(&(keypad->pad_column[column_counter]));
        }
        ret = E_OK ;
    }
    return ret;
}
/**
 * 
 * 
 * @param keypad
 * @param value pointer to return value 
 * @return Std_ReturnType ok if true n_ok if false 
 * @brief --> used to return the value that  pressed on keypad  
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value ){
Std_ReturnType ret = E_OK;
uint8 l_counter= 0 , row_counter= 0  , column_counter =0 , ret_logic = 0; 
    if((NULL==keypad)||(NULL == value))
    {
        ret =E_NOT_OK ;
    }else
    {
        for(l_counter = 0 ; l_counter <KEY_PAD_ROWS ; l_counter++ ){
        for(row_counter = 0 ; row_counter <KEY_PAD_ROWS ; row_counter++ ){
            ret = gpio_pin_write_logic(&(keypad->pad_row[row_counter]), LOGIC_LOW);
        }
        ret = gpio_pin_write_logic(&(keypad->pad_row[l_counter]), LOGIC_HIGH);
        __delay_ms(10);
        for(column_counter = 0 ; column_counter <KEY_PAD_COLUMNS ; column_counter++ ){
            ret = gpio_pin_read_logic(&(keypad->pad_column[column_counter]),&ret_logic);
            if(LOGIC_HIGH == ret_logic){
            *value = keypad_values[l_counter][column_counter];
            }
        }
        }
    }
    return ret;
}
