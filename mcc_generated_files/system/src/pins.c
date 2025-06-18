/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.1
 */

/*
? [2025] Microchip Technology Inc. and its subsidiaries.

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

#define PWM_PERIOD 1280

#include "../pins.h"
#include "../../../mcc_generated_files/pwm/pwm1_16bit.h"
#include "../../../mcc_generated_files/uart/uart1.h"
#include "../../../mcc_generated_files/nvm/nvm.h"
#include "../../../motor.h"
#include "../../../menu.h"
#include "../../../debug.h"

#define DEBOUNCE_DELAY_MS 50

int lastGateState = GATE_CLOSE;

volatile bool buttonPressedFlag = false;
volatile uint16_t buttonHoldTimeMs = 0;

volatile uint16_t openFullDuration = 0;
volatile uint16_t closeFullDuration = 0;

void (*DOWN_InterruptHandler)(void);
void (*BACK_InterruptHandler)(void);
void (*UP_InterruptHandler)(void);
void (*GATE_InterruptHandler)(void);
void (*PHOTOCELL_InterruptHandler)(void);
void (*BUTTON_InterruptHandler)(void);
void (*ENTER_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void) {
    /**
     LATx registers
     */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x0;
    /**
    ODx registers
     */
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;

    /**
    TRISx registers
     */
    TRISA = 0x3F;
    TRISB = 0x30;
    TRISC = 0x27;

    /**
    ANSELx registers
     */
    ANSELA = 0x23;
    ANSELB = 0x80;
    ANSELC = 0x0;

    /**
    WPUx registers
     */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;


    /**
    SLRCONx registers
     */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;

    /**
    INLVLx registers
     */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;

    /**
     RxyI2C | RxyFEAT registers   
     */
    RB4I2C = 0x0;
    RB6I2C = 0x0;
    /**
    PPS registers
     */
    U1RXPPS = 0xD; //RB5->UART1:RX1;
    RB6PPS = 0x10; //RB6->UART1:TX1;
    RB7PPS = 0x0A; //RB7->PWM1_16BIT:PWM11;

    /**
     IOCx registers 
     */
    IOCAP = 0x0;
    IOCAN = 0x14;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x10;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x27;
    IOCCF = 0x0;

    DOWN_SetInterruptHandler(DOWN_DefaultInterruptHandler);
    BACK_SetInterruptHandler(BACK_DefaultInterruptHandler);
    UP_SetInterruptHandler(UP_DefaultInterruptHandler);
    GATE_SetInterruptHandler(GATE_DefaultInterruptHandler);
    PHOTOCELL_SetInterruptHandler(PHOTOCELL_DefaultInterruptHandler);
    BUTTON_SetInterruptHandler(BUTTON_DefaultInterruptHandler);
    ENTER_SetInterruptHandler(ENTER_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1;
}

void PIN_MANAGER_IOC(void) {
    // interrupt on change for pin DOWN
    if (IOCAFbits.IOCAF2 == 1) {
        DOWN_ISR();
    }
    // interrupt on change for pin BACK
    if (IOCAFbits.IOCAF4 == 1) {
        BACK_ISR();
    }
    // interrupt on change for pin UP
    if (IOCBFbits.IOCBF4 == 1) {
        UP_ISR();
    }
    // interrupt on change for pin GATE
    if (IOCCFbits.IOCCF0 == 1) {
        GATE_ISR();
    }
    // interrupt on change for pin PHOTOCELL
    if (IOCCFbits.IOCCF1 == 1) {
        PHOTOCELL_ISR();
    }
    // interrupt on change for pin BUTTON
    if (IOCCFbits.IOCCF2 == 1) {
        BUTTON_ISR();
    }
    // interrupt on change for pin ENTER
    if (IOCCFbits.IOCCF5 == 1) {
        ENTER_ISR();
    }
}

void DOWN_ISR(void) {
    // Add your DOWN interrupt handling code here
    __delay_ms(20);
    while(DOWN_GetValue());
    IOCAFbits.IOCAF2 = 0; // Clear the interrupt flag

    if (!menuMode)
        return;

    DEBUG_PRINT("DOWN pressed, passing to menu handler\r\n");
    Menu_HandleDown();

    // Call the interrupt handler callback if set
    if (DOWN_InterruptHandler) {
        DOWN_InterruptHandler();
    }


}

void DOWN_SetInterruptHandler(void (* InterruptHandler)(void)) {
    DOWN_InterruptHandler = InterruptHandler;
}

void DOWN_DefaultInterruptHandler(void) {
    // Add your default interrupt handler code for DOWN here
}

/**
   BACK Interrupt Service Routine
 */
void BACK_ISR(void) {

     __delay_ms(20);
    while(BACK_GetValue()); // Wait for the button to be released
    IOCAFbits.IOCAF4 = 0;

    if (!menuMode)
        return;
    // Add custom BACK code
    DEBUG_PRINT("BACK pressed, passing to menu handler\r\n");
    Menu_HandleBack();

    // Call the interrupt handler for the callback registered at runtime
    if (BACK_InterruptHandler) {
        BACK_InterruptHandler();
    }

}

/**
  Allows selecting an interrupt handler for BACK at application runtime
 */
void BACK_SetInterruptHandler(void (* InterruptHandler)(void)) {
    BACK_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for BACK
 */
void BACK_DefaultInterruptHandler(void) {
    // add your BACK interrupt custom code
    // or set custom function using BACK_SetInterruptHandler()
}

/**
   UP Interrupt Service Routine
 */
void UP_ISR(void) {

     __delay_ms(20);
    while(UP_GetValue());
    IOCBFbits.IOCBF4 = 0;

    if (!menuMode)
        return;

    DEBUG_PRINT("UP pressed, passing to menu handler\r\n");
    Menu_HandleUp();

    // Call the interrupt handler for the callback registered at runtime
    if (UP_InterruptHandler) {
        UP_InterruptHandler();
    }

}

/**
  Allows selecting an interrupt handler for UP at application runtime
 */
void UP_SetInterruptHandler(void (* InterruptHandler)(void)) {
    UP_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for UP
 */
void UP_DefaultInterruptHandler(void) {
    // add your UP interrupt custom code
    // or set custom function using UP_SetInterruptHandler()
}

/**
   GATE Interrupt Service Routine
 */
void GATE_ISR(void) {

     __delay_ms(20);
    while(GATE_GetValue());
    IOCCFbits.IOCCF0 = 0; // Clear interrupt flag
    
    if (menuMode && userRequest)
        return;

    // Simulate gate reaching end position based on motor direction
    if (motorState == MOTOR_OPEN_SLOW && motorIsRunning) {
        gateState = GATE_OPEN;
        motorState = MOTOR_OPEN_WAIT_CLOSE;
        DEBUG_PRINT("Gate reached fully open limit\r\n");
    }

    if (motorState == MOTOR_CLOSE_SLOW && motorIsRunning) {
        gateState = GATE_CLOSE;
        DEBUG_PRINT("Gate reached fully closed limit\r\n");
    }

    if (emergencyFlag && motorIsRunning) {
        gateState = GATE_OPEN;
        motorState = MOTOR_OPEN_WAIT_CLOSE;
        DEBUG_PRINT("Gate reached fully closed limit (Emergency mode)\r\n");
        emergencyFlag = 0;
    }

    lastGateState = gateState;
    MotorControl(); // This will stop the motor if needed
    
}

/**
  Allows selecting an interrupt handler for GATE at application runtime
 */
void GATE_SetInterruptHandler(void (* InterruptHandler)(void)) {
    GATE_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for GATE
 */
void GATE_DefaultInterruptHandler(void) {
    // add your GATE interrupt custom code
    // or set custom function using GATE_SetInterruptHandler()
}

/**
   PHOTOCELL Interrupt Service Routine
 */
void PHOTOCELL_ISR(void) {

     __delay_ms(20);
    while(PHOTOCELL_GetValue());
    IOCCFbits.IOCCF1 = 0; // Clear interrupt flag
    
    if (configFlag)
        return;

    if (!PHOTOCELL_GetValue()) { // Obstacle detected
        __delay_ms(20);
        DEBUG_PRINT("Photocell Interrupt\r\n");
        if (motorState == MOTOR_CLOSE_FULL || motorState == MOTOR_CLOSE_SLOW) {
            emergencyFlag = 1;
            DEBUG_PRINT("Emergency Flag Set\r\n");
        } if (motorState == MOTOR_OPEN_WAIT_CLOSE) {
            gateOpenTimerMs = 0;
            DEBUG_PRINT("Reset Time Count for Auto Close\r\n");
        }
    }
    MotorControl();
    
}

/**
  Allows selecting an interrupt handler for PHOTOCELL at application runtime
 */
void PHOTOCELL_SetInterruptHandler(void (* InterruptHandler)(void)) {
    PHOTOCELL_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for PHOTOCELL
 */
void PHOTOCELL_DefaultInterruptHandler(void) {
    // add your PHOTOCELL interrupt custom code
    // or set custom function using PHOTOCELL_SetInterruptHandler()
}

/**
   BUTTON Interrupt Service Routine
 */

void BUTTON_ISR(void) {
    
     __delay_ms(20);
    while(BUTTON_GetValue());
    IOCCFbits.IOCCF2 = 0; // Clear interrupt flag ASAP

    DEBUG_PRINT("Button Pressed\r\n");

    if (menuMode) {
        
        HandleButtonMenuConfig();
    } else if (!configDone) {

        DEBUG_PRINT("Gate not opening because it is not configured\r\n");
        return;
    } else {
        // Normal operation: toggle or trigger motor action
        userRequest = 1;
        MotorControl(); // Trigger gate action
    }
}

/**
  Allows selecting an interrupt handler for BUTTON at application runtime
 */
void BUTTON_SetInterruptHandler(void (* InterruptHandler)(void)) {
    BUTTON_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for BUTTON
 */
void BUTTON_DefaultInterruptHandler(void) {
    // add your BUTTON interrupt custom code
    // or set custom function using BUTTON_SetInterruptHandler()
}

/**
   ENTER Interrupt Service Routine
 */
void ENTER_ISR(void) {

     __delay_ms(20);
    while(ENTER_GetValue());
    IOCCFbits.IOCCF5 = 0;
    menuMode = true; // or toggle if you want enter to toggle config mode

    // Call menu handler for enter key
    Menu_HandleEnterPress();
    if (ENTER_InterruptHandler) {
        ENTER_InterruptHandler();
    }
    
}

/**
  Allows selecting an interrupt handler for ENTER at application runtime
 */
void ENTER_SetInterruptHandler(void (* InterruptHandler)(void)) {
    ENTER_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for ENTER
 */
void ENTER_DefaultInterruptHandler(void) {
    // add your ENTER interrupt custom code
    // or set custom function using ENTER_SetInterruptHandler()
}
/**
 End of File
 */