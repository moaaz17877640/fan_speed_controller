/* 
 * File:   ecu_led.h
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:36 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/* SECTION : includes*/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* SECTION :macro declarations */

/* SECTION : macro function declarations */



/* SECTION : functions declaration*/
#define LED_ON   1
#define LED_OFF  0
/* SECTION : datatype declarations */
typedef struct{
   uint8 port :4;
   uint8 statu : 1;
   uint8 pin :3;
}led_t;

/* section interfaces declarations*/
Std_ReturnType led_intalize(const led_t *led);
Std_ReturnType led_on(const led_t *led);
Std_ReturnType led_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);



#endif	/* ECU_LED_H */

