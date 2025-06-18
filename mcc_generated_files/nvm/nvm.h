#ifndef NVM_H
#define NVM_H

#include <xc.h>
#include <stdbool.h>

#define EEPROM_ADDR_OPEN_DURATION   0x380000
#define EEPROM_ADDR_CLOSE_DURATION  0x380002
#define EEPROM_ADDR_OVERCURRENT     0x380004
#define EEPROM_ADDR_SPEED_LEVEL     0x380006
#define EEPROM_ADDR_TIME_AUTO       0x380008

typedef uint8_t eeprom_data_t;

typedef uint24_t eeprom_address_t;


typedef enum {
    NVM_OK, /**<0 - The NVM operation succeeded.*/
    NVM_ERROR /**<1 - The NVM operation failed.*/
} nvm_status_t;

void NVM_Initialize(void);

bool NVM_IsBusy(void);

void NVM_StatusClear(void);

void NVM_UnlockSequence(void);

uint16_t EEPROM_ReadUInt16(uint24_t addr);

eeprom_data_t EEPROM_Read(eeprom_address_t address);

void EEPROM_Write(eeprom_address_t address, eeprom_data_t data);

void EEPROM_WriteUInt16(uint24_t addr, uint16_t value);

#endif