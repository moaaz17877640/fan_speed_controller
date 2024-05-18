/* 
 * File:   ecu_chr_lcd.h
 * Author: MOAAZ
 *
 * Created on February 13, 2024, 11:52 AM
 */         

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H
/* SECTION : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* SECTION :macro declarations */
#define ROW1    1
#define ROW2    2
#define ROW3    3
#define ROW4    4

#define LCD_CLEAR_DISPLAY              0x01
#define LCD_RETURN_HOME                0x02
#define LCD_SHIFT_DISPLAY_OFF_DEC      0x04
#define LCD_SHIIFT_DISPLAY_ON_DEC      0x05 
#define LCD_ENTRY_MODE_                0x06
#define LCD_SHIFT_DISPLAY_ON_INC       0x07
//#define LCD_CURSOR_OFF_DISPLAY_OFF     0x08
#define LCD_CURSOR_OFF_DISPLAY_ON      0x0C
#define LCD_CURSOR_ON_DISPLAY_ON       0x0E
#define LCD_CUR_ON_DISPLAY_ON_BLINK_ON 0x0F 
#define LCD_DISPLAY_SHIFT_LEFT         0x18
#define LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define LCD_4BIT_2LINE_MODE            0x28
#define LCD_8BIT_2LINE_MODE            0x38
#define LCD_CGRAM_START                0x40
#define LCD_DDRAM_START                0x80
/* SECTION : datatype declarations */
typedef struct{
    pin_config_t pin_Rs ;
    pin_config_t pin_en ;
    pin_config_t lcd_pins[4];
}chr_lcd_4bit_t;
typedef struct{
    pin_config_t pin_Rs ;
    pin_config_t pin_en ;
    pin_config_t lcd_pins[8];
}chr_lcd_8bit_t;
/* SECTION : functions declaration*/
/**
 * 
 * @param lcd
 * @return Std_ReturnType ok if true n_ok if false 
 * @brief --> this interface for init the charactwer lcd pins as input and output.. and proform basic commands
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd );

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd  , uint8 command);
Std_ReturnType lcd_4bit_send_data_char(const chr_lcd_4bit_t *lcd ,  uint8 data);
Std_ReturnType lcd_4bit_send_data_char_posit(const chr_lcd_4bit_t *lcd ,uint8 row , uint8 colunm , uint8 data);
Std_ReturnType lcd_4bit_send_data_string(const chr_lcd_4bit_t *lcd ,  uint8 *data);
Std_ReturnType lcd_4bit_send_data_string_posit(const chr_lcd_4bit_t *lcd ,uint8 row , uint8 colunm , uint8 *data);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd  , uint8 row , uint8 colunm , uint8 char_[] , uint8 mem_p );

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd );
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd  , uint8 command);
Std_ReturnType lcd_8bit_send_data_char(const chr_lcd_8bit_t *lcd ,  uint8 data);
Std_ReturnType lcd_8bit_send_data_char_posit(const chr_lcd_8bit_t *lcd ,uint8 row , uint8 colunm , uint8 data);
Std_ReturnType lcd_8bit_send_data_string(const chr_lcd_8bit_t *lcd ,  uint8 *data);
Std_ReturnType lcd_8bit_send_data_string_posit(const chr_lcd_8bit_t *lcd ,uint8 row , uint8 colunm , uint8 *data);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd  , uint8 row , uint8 colunm , uint8 char_[] , uint8 mem_p );
Std_ReturnType convert_uint8_to_string(uint8 num ,uint8 *str );
Std_ReturnType convert_uint16_to_string(uint16 num ,uint8 *str );
Std_ReturnType convert_uint32_to_string(uint32 num ,uint8 *str );
#endif	/* ECU_CHR_LCD_H */

