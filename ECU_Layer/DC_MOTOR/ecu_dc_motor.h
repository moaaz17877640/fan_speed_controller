/* 
 * File:   ecu_dc_motor.h
 * Author: MOAAZ
 *
 * Created on January 25, 2024, 7:54 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/* SECTION : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* SECTION :macro declarations */
#define MOTOR_ON_STATUS 0x01U
#define MOTOR_OFF_STATUS 0x00U
#define MOTON_PIN_1  0x00U
#define MOTON_PIN_2  0x01U
/* SECTION : macro function declarations */

/* SECTION : datatype declarations */
//typedef struct {
//    uint8 motor_port : 4 ;
//    uint8 motor_pin : 3  ;
//    uint8 motor_State :1 ;
//}motor_type;

typedef struct{
    pin_config_t motors[2];
}motor_t;
/* SECTION : functions declaration*/
Std_ReturnType motor_initialize(const motor_t *motor);
Std_ReturnType motor_move_right(const motor_t *motor);
Std_ReturnType motor_move_left(const motor_t *motor);
Std_ReturnType   motor_stop(const motor_t *motor);
#endif	/* ECU_DC_MOTOR_H */

