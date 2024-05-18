/* 
 * File:   7_segment.c
 * Author: MOAAZ
 *
 * Created on February 8, 2024, 6:41 PM
 */
/* SECTION : includes*/
#include "7_segment.h"
/**
 * 
 * @param seg
 * @return 
 */
Std_ReturnType Segment_initalize(const Segment_t *seg){
 Std_ReturnType ret = E_NOT_OK;
    if(NULL==seg)
    {
        ret =E_NOT_OK ;
    }else
    {
        gpio_pin_intialize(&(seg->seg__pins[0]));
        gpio_pin_intialize(&(seg->seg__pins[1]));
        gpio_pin_intialize(&(seg->seg__pins[2]));
        gpio_pin_intialize(&(seg->seg__pins[3]));
        ret = E_OK ;
    }
    return ret;
}
/**
 * 
 * @param seg
 * @param number
 * @return 
 */
Std_ReturnType Segment_Write_number(const Segment_t *seg , uint8 number){
Std_ReturnType ret = E_NOT_OK;
    if((NULL==seg)||(number >9))
    {
        ret =E_NOT_OK ;
    }else
    {
        gpio_pin_write_logic(&(seg->seg__pins[0]),(uint8)((number)&0x01)); 
        gpio_pin_write_logic(&(seg->seg__pins[1]),(uint8)((number>>1)&0x1));
        gpio_pin_write_logic(&(seg->seg__pins[2]),(uint8)((number>>2)&0x1));
        gpio_pin_write_logic(&(seg->seg__pins[3]),(uint8)((number>>3)&0x01));
        ret = E_OK ;
    }
    return ret;
}