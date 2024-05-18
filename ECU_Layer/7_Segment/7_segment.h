/* 
 * File:   7_segment.h
 * Author: MOAAZ
 *
 * Created on February 8, 2024, 6:41 PM
 */


#ifndef SEGMENT_H
#define	SEGMENT_H


/* SECTION : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* SECTION : datatype declarations */
typedef enum{
    COMMON_ANODE,
            COMMON_CATHODE
}Segment_type_t;
typedef struct{
    pin_config_t seg__pins[4];
    Segment_type_t type ;
}Segment_t;
Std_ReturnType Segment_initalize(const Segment_t *seg);
Std_ReturnType Segment_Write_number(const Segment_t *seg , uint8 number);

#endif	/* 7_SEGMENT_H */

