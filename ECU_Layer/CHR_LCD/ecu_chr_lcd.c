/* 
 * File:   ecu_chr_lcd.c
 * Author: MOAAZ
 *
 * Created on February 13, 2024, 11:52 AM
 */
#include "ecu_chr_lcd.h"
static Std_ReturnType lcd_send_4bit_command_data(const chr_lcd_4bit_t *lcd , uint8 data);
static Std_ReturnType  lcd_send_4bit_enable(const chr_lcd_4bit_t *lcd );
static Std_ReturnType  lcd_send_8bit_enable(const chr_lcd_8bit_t *lcd );
static Std_ReturnType lcd_set_cursor_8bit(const chr_lcd_8bit_t *lcd  , uint8 row , uint8 column );
static Std_ReturnType lcd_set_cursor_4bit(const chr_lcd_4bit_t *lcd  , uint8 row , uint8 column );

Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd ){
    Std_ReturnType ret = E_OK ;
    uint8 l_counter =0 ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
        ret= gpio_pin_intialize(&(lcd->pin_Rs));
            ret= gpio_pin_intialize(&(lcd->pin_en));
            for(l_counter = 0 ; l_counter < 4 ; l_counter++){
                ret = gpio_pin_intialize(&(lcd->lcd_pins[l_counter]));
            }
            __delay_ms(20);
            ret = lcd_4bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
             __delay_ms(5);
            ret = lcd_4bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
            __delay_us(150);
             ret = lcd_4bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
         
             
             ret = lcd_4bit_send_command(lcd ,LCD_CLEAR_DISPLAY);
             ret = lcd_4bit_send_command(lcd ,LCD_RETURN_HOME);
             ret = lcd_4bit_send_command(lcd ,LCD_ENTRY_MODE_);
            ///  ret = lcd_4bit_send_command(lcd , LCD_4BIT_2LINE_MODE);
             ret = lcd_4bit_send_command(lcd ,LCD_CURSOR_OFF_DISPLAY_ON);
             ret = lcd_4bit_send_command(lcd , LCD_4BIT_2LINE_MODE);
             ret = lcd_4bit_send_command(lcd ,LCD_DDRAM_START);

    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd  , uint8 command){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
        ret = gpio_pin_write_logic(&(lcd->pin_Rs) , LOGIC_LOW);
        ret = lcd_send_4bit_command_data((lcd) , command>>4);
        ret = lcd_send_4bit_enable((lcd));
         ret = lcd_send_4bit_command_data((lcd) , command);
        ret = lcd_send_4bit_enable((lcd));
   
    }
    return ret ;
    
}
Std_ReturnType lcd_4bit_send_data_char(const chr_lcd_4bit_t *lcd ,  uint8 data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
       ret = gpio_pin_write_logic(&(lcd->pin_Rs) , LOGIC_HIGH);
        ret = lcd_send_4bit_command_data((lcd) , data >> 4);
        ret = lcd_send_4bit_enable((lcd));
        ret = lcd_send_4bit_command_data((lcd) , data);
        ret = lcd_send_4bit_enable((lcd));
    }
    return ret ;
}


Std_ReturnType lcd_4bit_send_data_char_posit(const chr_lcd_4bit_t *lcd ,uint8 row , uint8 colunm , uint8 data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {  
        
      ret = lcd_set_cursor_4bit(lcd ,row , colunm);
        ret = lcd_4bit_send_data_char(lcd , data);
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_data_string(const chr_lcd_4bit_t *lcd ,  uint8 *data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
        while(*data)
        {
            ret = lcd_4bit_send_data_char(lcd , *data++);
                    
        }
        
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_data_string_posit(const chr_lcd_4bit_t *lcd ,uint8 row , uint8 colunm , uint8 *data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
         ret = lcd_set_cursor_4bit(lcd ,row , colunm);
    while(*data)
        {
            ret = lcd_4bit_send_data_char(lcd , *data++);
                    
        }
       
    }
    return ret ;
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd  , uint8 row , uint8 colunm , uint8 char_[] , uint8 mem_p ){
    Std_ReturnType ret = E_OK ;
     uint8 counter = ZERO_INIT ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
    
       ret = lcd_8bit_send_command (lcd, (LCD_CGRAM_START)+(mem_p * 8 ));
        for(counter = ZERO_INIT ; counter < 8 ; counter ++){
            ret = lcd_4bit_send_data_char(lcd ,char_[counter] );
        }
       ret = lcd_4bit_send_data_char_posit(lcd ,row,colunm,mem_p );
    }
    return ret ;
}


Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd ){
    Std_ReturnType ret = E_OK ;
    
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }
    else {
        ret = gpio_pin_intialize(&(lcd->pin_Rs));
        ret = gpio_pin_intialize(&(lcd->pin_en));
        for(int i =0 ;i<8 ;i++){
            ret =gpio_pin_intialize(&(lcd->lcd_pins[i]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
        
        ret = lcd_8bit_send_command(lcd ,LCD_CLEAR_DISPLAY);
             ret = lcd_8bit_send_command(lcd ,LCD_RETURN_HOME);
             ret = lcd_8bit_send_command(lcd ,LCD_ENTRY_MODE_);
             
             ret = lcd_8bit_send_command(lcd ,LCD_CURSOR_OFF_DISPLAY_ON);
              ret = lcd_8bit_send_command(lcd , LCD_8BIT_2LINE_MODE);
             
             ret = lcd_8bit_send_command(lcd ,LCD_DDRAM_START);
    }
   
return ret ;
}
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd  , uint8 command){
    Std_ReturnType ret = E_OK ;
    uint8 counter = 0;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
    ret = gpio_pin_write_logic(&(lcd->pin_Rs) , LOGIC_LOW);
    for(counter =0 ; counter < 8 ; counter++){
    ret =  gpio_pin_write_logic(&(lcd->lcd_pins[counter]),(command>>counter )&(uint8)(0x01));
    }
    ret = lcd_send_8bit_enable((lcd));
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_data_char(const chr_lcd_8bit_t *lcd ,  uint8 data){
    Std_ReturnType ret = E_OK ;
      uint8 counter = 0;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
    ret = gpio_pin_write_logic(&(lcd->pin_Rs) , LOGIC_HIGH);
    for(counter =0 ; counter < 8 ; counter++){
    ret =  gpio_pin_write_logic(&(lcd->lcd_pins[counter]),(data >> counter )&(uint8)0x01);
    }
    ret = lcd_send_8bit_enable((lcd));
    }
    return ret ;
}


Std_ReturnType lcd_8bit_send_data_char_posit(const chr_lcd_8bit_t *lcd ,uint8 row , uint8 colunm , uint8 data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
    ret = lcd_set_cursor_8bit(lcd ,row , colunm);
        ret = lcd_8bit_send_data_char(lcd , data);
        
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_data_string(const chr_lcd_8bit_t *lcd ,  uint8 *data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
     while(*data)
        {
            ret = lcd_8bit_send_data_char(lcd , *data++);
                    
        }
      
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_data_string_posit(const chr_lcd_8bit_t *lcd ,uint8 row , uint8 colunm , uint8 *data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
      ret = lcd_set_cursor_8bit(lcd ,row , colunm);
    
            ret = lcd_8bit_send_data_string(lcd , data);
                    

        ret= E_OK ;
    }
    return ret ;
}
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd  , uint8 row , uint8 colunm , uint8 char_[] , uint8 mem_p ){
    Std_ReturnType ret = E_OK ;
    uint8 counter = ZERO_INIT ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
        ret = lcd_8bit_send_command (lcd, (LCD_CGRAM_START)+(mem_p * 8 ));
        for(counter = ZERO_INIT ; counter <=7 ; counter ++){
            ret = lcd_8bit_send_data_char(lcd ,char_[counter] );
        }
       ret = lcd_8bit_send_data_char_posit(lcd ,row,colunm,mem_p );
    }
    return ret;
}
Std_ReturnType convert_uint8_to_string(uint8 num ,uint8 *str ){
Std_ReturnType ret = E_OK ;
    if((NULL==str)){
        ret =E_NOT_OK ;
    }else {
       memset(str , '\0', 4);
        sprintf(str , "%i" , num);
       
    }
    return ret;
}
Std_ReturnType convert_uint16_to_string(uint16 num ,uint8 *str ){
 Std_ReturnType ret = E_OK ;
 uint8 temp[6]={0};
 uint8 counter =0 ;
    if((NULL==str)){
        ret =E_NOT_OK ;
    }else {
    
        memset(str , ' ', 5);
        str[5]='\0';
        sprintf( (char *)temp , "%i" , num);
        while(temp[counter]!='\0'){
        str[counter]= temp[counter] ;
        counter++;
        }
    }
    return ret;
}
Std_ReturnType convert_uint32_to_string(uint32 num ,uint8 *str ){
    Std_ReturnType ret = E_OK ;
    if((NULL==str)){
        ret =E_NOT_OK ;
    }else {
    
          memset(str , '\0', 11);
        sprintf(str , "%i" , num);
    }
    return ret;
}

static Std_ReturnType  lcd_send_4bit_command_data(const chr_lcd_4bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_OK ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
         ret = gpio_pin_write_logic(&(lcd->lcd_pins[0]),(data>>0 )&(uint8)(0x01));
         ret = gpio_pin_write_logic(&(lcd->lcd_pins[1]),(data>>1 )&(uint8)(0x01));
          ret = gpio_pin_write_logic(&(lcd->lcd_pins[2]),(data >>2)&(uint8)(0x01));
           ret = gpio_pin_write_logic(&(lcd->lcd_pins[3]),(data >>3)&(uint8)(0x01));
         Std_ReturnType ret = E_OK ;
    }
    return ret ;
}
static Std_ReturnType  lcd_send_8bit_enable(const chr_lcd_8bit_t *lcd ){
 Std_ReturnType ret = E_OK ;

    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
         ret = gpio_pin_write_logic(&(lcd->pin_en) , LOGIC_HIGH);
         __delay_us(5);
          ret = gpio_pin_write_logic(&(lcd->pin_en) , LOGIC_LOW);
        ret= E_OK ;
    }
    return ret ;
}
 static Std_ReturnType  lcd_send_4bit_enable(const chr_lcd_4bit_t *lcd ){
 Std_ReturnType ret = E_OK ;

    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
         ret = gpio_pin_write_logic(&(lcd->pin_en) , LOGIC_HIGH);
         __delay_us(5);
          ret = gpio_pin_write_logic(&(lcd->pin_en) , LOGIC_LOW);
        ret= E_OK ;
    }
    return ret ;
}
 static Std_ReturnType lcd_set_cursor_4bit(const chr_lcd_4bit_t *lcd  , uint8 row , uint8 column ){
       Std_ReturnType ret = E_OK ;
         column-- ;
        switch(row){
      case ROW1 : ret = lcd_4bit_send_command(lcd ,( 0x80+column)); break ;
      case ROW2 : ret = lcd_4bit_send_command(lcd , (0xc0+column)); break ;
      case ROW3 : ret = lcd_4bit_send_command(lcd , (0x90+column)); break ;
      case ROW4 : ret = lcd_4bit_send_command(lcd , ( 0xd0+column)); break ;
            default : ;
      
       
        ret= E_OK ;
    }
    return ret ;
 
 
 }
 static Std_ReturnType lcd_set_cursor_8bit(const chr_lcd_8bit_t *lcd  , uint8 row , uint8 column ){
       Std_ReturnType ret = E_OK ;
       column-- ;
    if((NULL==lcd)){
        ret =E_NOT_OK ;
    }else {
        switch(row){
      case ROW1 : ret = lcd_8bit_send_command(lcd ,( 0x80+column)); break ;
      case ROW2 : ret = lcd_8bit_send_command(lcd , ( 0xc0+column)); break ;
      case ROW3 : ret = lcd_8bit_send_command(lcd , ( 0x90+column)); break ;
      case ROW4 : ret = lcd_8bit_send_command(lcd , ( 0xd0+column)); break ;
            default : ;
      
        
        }
        ret= E_OK ;
    }
    return ret ;
 
 
 }