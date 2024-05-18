/* 
 * File:   relay_ecu.h
 * Author: MOAAZ
 *
 * Created on January 22, 2024, 4:48 PM
 */

#ifndef RELAY_ECU_H
#define	RELAY_ECU_H
/* SECTION : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* SECTION :macro declarations */
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U
/* SECTION : macro function declarations */

/* SECTION : datatype declarations */
typedef struct {
    uint8  relay_port : 4 ;
    uint8  relay_pin  : 3 ;
    uint8 relay_status : 1;
}relay_t;

/* SECTION : functions declaration*/
Std_ReturnType relay_initalize(const relay_t *relay);
Std_ReturnType relay_on(const relay_t *relay );
Std_ReturnType relay_off(const relay_t *relay );

#endif	/* RELAY_ECU_H */

