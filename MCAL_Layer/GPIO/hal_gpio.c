/* 
 * File:   hal_gpio.h
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:34 PM
 */

/* SECTION : includes*/
#include "hal_gpio.h"
/* SECTION : datatype declarations */
volatile uint8 *tris_registers[] ={&TRISA , &TRISB ,&TRISC ,&TRISD ,&TRISE}; 
volatile uint8 *port_registers[] ={&PORTA , &PORTB ,&PORTC ,&PORTD , &PORTE };
volatile uint8 *lat_registers[] ={&LATA , &LATB ,&LATC , &LATD , &LATE};

/* SECTION : functions DEFINITION */
/**
 * 
 * @param __pin_t
 * @return 
 */
#if CONFIGURAE_PIN_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *__pin_t){
    Std_ReturnType ret = E_OK;
    if( NULL ==__pin_t ||__pin_t ->pin > PIN_MAX_NUM-1 )
    {
        ret = E_NOT_OK; 
    }
    else
    {
     switch(__pin_t ->direction)
    {
        case OUTPUT :
            CLEAR_BIT(*tris_registers[__pin_t ->port] , __pin_t ->pin);
            break;
        case INPUT :
            SET_BIT(*tris_registers[__pin_t ->port],__pin_t ->pin);
            break;
        default : 
             ret = E_NOT_OK; 
            
    }
    }
   
    return ret;
}
#endif
/**
 * 
 * @param __pin_t
 * @param direction
 * @return 
 */
#if CONFIGURAE_PIN_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_t , direction_t *direction){
       Std_ReturnType ret = E_OK;
    if(NULL ==_pin_t || _pin_t->pin > PIN_MAX_NUM-1||NULL==direction )
    {
        ret = E_NOT_OK; 
    }
    else
    {
    *direction = READ_BIT(*tris_registers[_pin_t ->port] , _pin_t ->pin);
    
    }
   
    return ret;
}
#endif

/**
 * 
 * @param __pin_t
 * @param logic
 * @return 
 */
#if CONFIGURAE_PIN_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_t,logic_t logic){
    Std_ReturnType ret = E_OK;
    if( NULL ==_pin_t || _pin_t->pin > PIN_MAX_NUM-1 )
    {
        ret = E_NOT_OK; 
    }
    else
    {
        switch(logic){
            case LOGIC_HIGH :
              SET_BIT(*lat_registers[_pin_t->port],_pin_t->pin)  ;
              break;
            case LOGIC_LOW :
            CLEAR_BIT(*lat_registers[_pin_t->port],_pin_t->pin) ;
            break;
            default :
                ret = E_NOT_OK;
        }
    
    }
   
    return ret;
}
#endif

/**
 * 
 * @param __pin_t
 * @param logic
 * @return 
 */
#if CONFIGURAE_PIN_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_t, logic_t *logic ){
    Std_ReturnType ret = E_OK;
    if( NULL ==_pin_t || _pin_t->pin >PIN_MAX_NUM-1 ||NULL == logic)
    {
        ret = E_NOT_OK; 
    }
    else
    {
      
              *logic = READ_BIT(*port_registers[_pin_t->port],_pin_t->pin)  ;
       
    }
   
    return ret;
}
#endif

/**
 * 
 * @param port
 * @return 
 */
#if CONFIGURAE_PIN_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *__pin_t ){
    Std_ReturnType ret = E_OK;
    if((NULL ==__pin_t)|| __pin_t->pin > PIN_MAX_NUM-1  )
    {
        ret = E_NOT_OK; 
    }
    else
    {
       TOGGLE_BIT (*lat_registers[__pin_t->port],__pin_t->pin);
         
    
    }
   
    return ret;
}
#endif

/**
 * 
 * @param _pin_t
 * @return 
 */
#if CONFIGURAE_PIN_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(pin_config_t *_pin_t){
   
    Std_ReturnType ret = E_OK;
    if((NULL ==_pin_t)|| _pin_t->pin > PIN_MAX_NUM-1 )
    {
        ret =E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(_pin_t);
        ret = gpio_pin_write_logic(_pin_t ,_pin_t->logic);
    
    }
    
return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if CONFIGURAE_PORT_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction){
   Std_ReturnType ret = E_OK;
   if(port > PORT_MAX_NUM){
       ret = E_NOT_OK;
   }
   else{
      *tris_registers[port]=direction; 
   }
   
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if CONFIGURAE_PORT_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 *direction){
    Std_ReturnType ret = E_OK;
    if(NULL == direction || port >PORT_MAX_NUM)
    {
        ret = E_NOT_OK; 
    }
    else
    {
    *direction  = *tris_registers[port];
    
    }
   
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if CONFIGURAE_PORT_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic){
  Std_ReturnType ret = E_OK;
  
  if(port >PORT_MAX_NUM )
  {
      ret= E_NOT_OK;
  }
  else
  {
      *lat_registers[port] = logic;
  }
    return ret;
}
#endif


/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if CONFIGURAE_PORT_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic ){
  Std_ReturnType ret = E_OK;
    if(NULL== logic||port >PORT_MAX_NUM)
    {
        ret = E_NOT_OK; 
    }
    else
    {
     *logic = *port_registers[port];
    
    }
   
    return ret;
}
#endif


/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if CONFIGURAE_PORT_STATUE == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port ){
  Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUM)
    {
        ret = E_NOT_OK; 
    }
    else
    {
    
        *lat_registers[port] ^= PORT_MASK;
    }
   
    return ret;
}
#endif