/*
 * File:   nvm.c
 * Author: ricardobarbosa
 *
 * Created on December 31, 2024, 6:51 PM
 */


#include "../nvm.h"
#include "../../../mcc_generated_files/uart/uart1.h"
#include "../../../debug.h"


void NVM_Initialize(void) {
    NVM_StatusClear();
}

bool NVM_IsBusy(void) {
    return NVMCON0bits.GO;
}

void NVM_StatusClear(void) {
    NVMCON1bits.WRERR = 0;
}

void NVM_UnlockSequence(void){
    NVMLOCK = 0x55;
    NVMLOCK = 0xAA;
    NVMCON0bits.GO = 1;
}

uint16_t EEPROM_ReadUInt16(uint24_t addr) {
    uint8_t low = EEPROM_Read(addr);
    uint8_t high = EEPROM_Read(addr + 1);
    return ((uint16_t)high << 8) | low;
}


uint8_t EEPROM_Read(uint24_t DFM_ADDR) {
    while (NVM_IsBusy()); // Wait for any ongoing NVM operation
    
    NVMADR = DFM_ADDR;
    NVMCON1bits.NVMCMD = 0x00; // Set the byte read command
    NVMCON0bits.GO = 1;        // Start byte read
    
    while (NVM_IsBusy()); // Wait for the read operation to complete

    return NVMDATL; // Return the read data
}

void EEPROM_WriteUInt16(uint24_t addr, uint16_t value) {
    // Write low and high bytes
    EEPROM_Write(addr,     (uint8_t)(value & 0xFF));         // Low byte
    EEPROM_Write(addr + 1, (uint8_t)(value >> 8));           // High byte

    // EEPROM write: Addr 0xXXXXXX = VALUE
    DEBUG_PRINT("EEPROM write: Addr 0x");

    for (int8_t i = 2; i >= 0; i--) {
        uint8_t byte = (addr >> (i * 8)) & 0xFF;
        DEBUG_PRINT_HEX(byte >> 4);
        DEBUG_PRINT_HEX(byte & 0x0F);
    }

    DEBUG_PRINT(" = ");
    DEBUG_PRINT_INT(value);
    DEBUG_PRINT("\r\n");
}


void EEPROM_Write(uint24_t DFM_ADDR, uint8_t data) {
    
    
    uint8_t globalInterruptBitValue = INTCON0bits.GIE;


    NVMADR = DFM_ADDR;

    NVMDATL = data;
    NVMCON1bits.NVMCMD = 0x03; // Set byte write command
    INTCON0bits.GIE = 0;
    
    NVM_UnlockSequence();

    INTCON0bits.GIE = globalInterruptBitValue;

    // Wait for write to complete
    while (NVM_IsBusy());

    NVMCON1bits.NVMCMD = 0x00; // Clear the command
}