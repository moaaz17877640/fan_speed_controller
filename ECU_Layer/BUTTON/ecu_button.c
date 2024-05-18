#include "ecu_botton.h"
//two type of connect button pull up pull down
/// validate two conditions.........
/// pull up button connect with power....and resistor connect to ground....
/// pull down  button connect with ground....and resistor connect to power....
/* SECTION : functions declaration*/

Std_ReturnType button_initalize(button_t *btn ){
Std_ReturnType ret = E_NOT_OK;
if(NULL == btn){

    ret = E_NOT_OK;
}
else{
    gpio_pin_direction_intialize(&(btn->button_pin));
     ret = E_OK; 
}
return ret ; 
}
Std_ReturnType button_read_state(button_t *btn , button_state_t *state){
Std_ReturnType ret = E_NOT_OK;
logic_t btn_logic = LOGIC_LOW ;
if((NULL == state)||(NULL == btn)){

    ret = E_NOT_OK;
}
else{
    ret = gpio_pin_read_logic(&(btn->button_pin),&btn_logic);
    if(BUTTON_ACTIVE_LOW == btn->active)
    {
        if(LOGIC_LOW == btn->button_pin.logic ){
        *state = BUTTON_RELEASED ;
        }
        else{
            *state = BUTTON_PRESSED ;
        }
         
    }
    else if(BUTTON_ACTIVE_HIGH == btn->active)
    {
      if(LOGIC_HIGH == btn->button_pin.logic){
      *state = BUTTON_PRESSED ;
      }
        else{
          *state = BUTTON_RELEASED;
        }
    }
    else
    { //no statements
        
    }

  
  ret = E_OK; 
}
return ret ;
}