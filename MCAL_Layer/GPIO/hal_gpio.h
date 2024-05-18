/* 
 * File:   hal_gpio.h
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:34 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* SECTION : includes*/
#include "../proc/pic18f4620.h"
#include "../Mcal_Std_Types.h"
#include "../device_config.h"
/* SECTION :macro declarations */
#define PORT_MASK       0xFF
#define BIT_MASK        (uint8)   1
#define PIN_MAX_NUM       (8)
#define PORT_MAX_NUM      (5)
#define CONFIGURAE_PIN_STATUE   CONFIG_ENABLE
#define CONFIGURAE_PORT_STATUE   CONFIG_ENABLE
#define ZERO_INIT        (0)
/* SECTION : macro function declarations */


#define HWREG8(_X)   (*((volatile uint8 *)(_X)))
#define SET_BIT( REG, BIT_POSITION )      (REG |= ( BIT_MASK << BIT_POSITION ))
#define CLEAR_BIT( REG, BIT_POSITION )    (REG &= ~( BIT_MASK << BIT_POSITION ))
#define TOGGLE_BIT( REG, BIT_POSITION )   (REG ^= ( BIT_MASK << BIT_POSITION ))
#define READ_BIT( REG, BIT_POSITION )     ((REG >> BIT_POSITION)& BIT_MASK)
/* SECTION : datatype declarations */
typedef enum{
    LOGIC_LOW,
            LOGIC_HIGH
}logic_t;
typedef enum{
    OUTPUT, 
            INPUT
}direction_t;
typedef enum{
    PORTA_INDEX,
             PORTB_INDEX,
             PORTC_INDEX,
             PORTD_INDEX,
            PORTE_INDEX
}port_index_t;
typedef enum{
    PIN0,
            PIN1,
            PIN2,
            PIN3,
            PIN4,
            PIN5,
            PIN6,
            PIN7,
}pin_index_t;
typedef struct{
    uint8 port : 3;       /*@ref : port_index_t */
    uint8 pin : 3;       /*@ref : pin_index_t */
    uint8 direction :1 ; /*@ref :  direction_t*/
    uint8 logic : 1;     /*@ref : logic_t */
    
}pin_config_t;
/* SECTION : functions declaration*/
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *__pin_t);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *__pin_t , direction_t *direction);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *__pin_t,logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *__pin_t, logic_t *logic );
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *__pin_t );
Std_ReturnType gpio_pin_intialize(pin_config_t *_pin_t);

Std_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 *direction);
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic );
Std_ReturnType gpio_port_toggle_logic(port_index_t port );

#endif	/* HAL_GPIO_H */

