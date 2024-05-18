#include "hal_eeprom.h"

/* SECTION : functions definition */
void Wait_to_Cycle()
{
    while(EECON1bits.WR)
    {
    //waiting...
    }
};
Std_ReturnType EEPROM_Write_Data(uint16 S_Add , uint8 ddata){
    Std_ReturnType ret =E_OK;
    //It is strongly recommended that interrupts be disabled during this code segment.
    uint8 Global_Interrupt_Statue = INTCONbits.GIE ;
    
// the address must  first be written to the EEADR register and the data written to the EEDATA register 
    EEADRH = (uint8)((S_Add >> 8)&0x03);
    EEADR = (uint8)(S_Add & 0xFF);
    
    // The write will not begin if this sequence is not exactly followed (write 55h to EECON2, write 0AAh to EECON2, then set WR bit) for each byte.
     EECON2 = 0x55 ;
     EECON2 = 0xAA ;
     // Put data in EEDATA..
      EEDATA = ddata ;
     //the WREN bit in EECON1 must be set to enable writes.
     EECON1bits.WREN = 1; 
     //Access data EEPROM memory
     EECON1bits.EEPGD = 0 ;
     //Access Flash program or data EEPROM memory
     EECON1bits.CFGS = 0 ;   
     // Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle
     INTCONbits.GIE = 0 ;
     EECON1bits.WR =1 ;
     //Wait for some times ... 
     Wait_to_Cycle();
     // The WREN bit should be kept clear at all times, except when updating
     //the EEPROM. The WREN bit is not cleared by hardware.
    EECON1bits.WREN = 0; 
         //restore interrupt statue 
     INTCONbits.GIE =Global_Interrupt_Statue ; 
    return ret;
}
Std_ReturnType EEPROM_Read_Data(uint16 S_Add , uint8 *ddata){
    Std_ReturnType ret = E_OK ;
    
    if(NULL == ddata){
    ret = E_NOT_OK ;
    }
    else{
    // the user must write the address to the EEADR register
     EEADR = (uint8)(S_Add & 0xFF);
     EEADRH = (uint8)((S_Add>>8)&0x03);
    // clear the EEPGD control bit of the EECON1 register and then set control bit, RD.
       INTCONbits.GIE = 0 ;
      EECON1bits.EEPGD = 0 ;
      EECON1bits.CFGS = 0 ;
         EECON1bits.RD = 1;
         NOP();
                  NOP();
         *ddata = EEDATA ;
    }
    return ret ;
}
