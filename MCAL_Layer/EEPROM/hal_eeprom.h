/* 
 * File:   hal_eeprom.h
 * Author: MOAAZ
 *
 * Created on February 22, 2024, 11:08 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/* SECTION : includes*/
#include"../Mcal_Std_Types.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL_Layer/Interrupt/mcal_external_interrupt.h"

#define NOP() __nop()

/* SECTION : functions declaration*/
Std_ReturnType EEPROM_Write_Data(uint16 S_Add , uint8 ddata);
Std_ReturnType EEPROM_Read_Data(uint16 S_Add , uint8 *ddata);

#endif	/* HAL_EEPROM_H */

