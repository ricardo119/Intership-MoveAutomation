/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
 */

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
 */
#include "mcc_generated_files/system/system.h"
#include "motor.h"
#include "mcc_generated_files/system/pins.h"
#include "tm1637.h"
#include "mcc_generated_files/adc/adcc.h"
#include "menu.h"
#include "debug.h"
#include "mcc_generated_files/uart/uart1.h"

/*
    Main application
 */

void projectInitialize(void) {
    
    
    speedLevel = EEPROM_ReadUInt16(EEPROM_ADDR_SPEED_LEVEL);
    openFullDuration = EEPROM_ReadUInt16(EEPROM_ADDR_OPEN_DURATION);
    closeFullDuration = EEPROM_ReadUInt16(EEPROM_ADDR_CLOSE_DURATION);
    overcurrentThreshold = EEPROM_ReadUInt16(EEPROM_ADDR_OVERCURRENT);
    timeAuto = EEPROM_ReadUInt16(EEPROM_ADDR_TIME_AUTO);
    
    DEBUG_PRINT_INT(speedLevel);
    DEBUG_PRINT("\r\n");
    DEBUG_PRINT_INT(openFullDuration);
    DEBUG_PRINT("\r\n");
    DEBUG_PRINT_INT(closeFullDuration);
    DEBUG_PRINT("\r\n");
    DEBUG_PRINT_INT(overcurrentThreshold);
    DEBUG_PRINT("\r\n");
    DEBUG_PRINT_INT(timeAuto);
    DEBUG_PRINT("\r\n");

    if (openFullDuration != 0xFFFF && closeFullDuration != 0xFFFF && speedLevel != 0xFF && overcurrentThreshold != 0xFFFF && timeAuto != 0xFFFF) {
        configDone = true;
    } else {
        speedLevel = 6;
        openFullDuration = 2000;
        closeFullDuration = 3000;
        overcurrentThreshold = 5000;
        timeAuto = 2000;
        
        configDone = true;
    }

}

int main(void) {
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    //CalibrateZeroCurrent();
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable();

    projectInitialize();


    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    UART1_WriteString("Intership project started\r\n");


    while (1) {

        /*PWM1_PHASE_A_SetSlice1Output1DutyCycleRegister(1280);
        PWM1_PHASE_A_LoadBufferRegisters();
        PWM1_PHASE_A_Enable();
        STOP_SetHigh();*/


    }
}