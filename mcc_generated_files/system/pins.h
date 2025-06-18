/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>
#include <stdbool.h>

extern volatile bool buttonPressedFlag;
extern volatile uint16_t buttonHoldTimeMs;

extern volatile uint16_t openFullDuration;
extern volatile uint16_t closeFullDuration;

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 aliases
#define DOWN_TRIS                 TRISAbits.TRISA2
#define DOWN_LAT                  LATAbits.LATA2
#define DOWN_PORT                 PORTAbits.RA2
#define DOWN_WPU                  WPUAbits.WPUA2
#define DOWN_OD                   ODCONAbits.ODCA2
#define DOWN_ANS                  ANSELAbits.ANSELA2
#define DOWN_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define DOWN_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define DOWN_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define DOWN_GetValue()           PORTAbits.RA2
#define DOWN_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define DOWN_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define DOWN_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define DOWN_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define DOWN_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define DOWN_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define DOWN_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define DOWN_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)
#define RA2_SetInterruptHandler  DOWN_SetInterruptHandler

// get/set RA4 aliases
#define BACK_TRIS                 TRISAbits.TRISA4
#define BACK_LAT                  LATAbits.LATA4
#define BACK_PORT                 PORTAbits.RA4
#define BACK_WPU                  WPUAbits.WPUA4
#define BACK_OD                   ODCONAbits.ODCA4
#define BACK_ANS                  ANSELAbits.ANSELA4
#define BACK_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define BACK_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define BACK_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define BACK_GetValue()           PORTAbits.RA4
#define BACK_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define BACK_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define BACK_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define BACK_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define BACK_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define BACK_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define BACK_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define BACK_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)
#define RA4_SetInterruptHandler  BACK_SetInterruptHandler

// get/set RA5 aliases
#define ADC_TRIS                 TRISAbits.TRISA5
#define ADC_LAT                  LATAbits.LATA5
#define ADC_PORT                 PORTAbits.RA5
#define ADC_WPU                  WPUAbits.WPUA5
#define ADC_OD                   ODCONAbits.ODCA5
#define ADC_ANS                  ANSELAbits.ANSELA5
#define ADC_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define ADC_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define ADC_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define ADC_GetValue()           PORTAbits.RA5
#define ADC_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define ADC_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define ADC_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define ADC_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define ADC_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define ADC_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define ADC_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define ADC_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RB4 aliases
#define UP_TRIS                 TRISBbits.TRISB4
#define UP_LAT                  LATBbits.LATB4
#define UP_PORT                 PORTBbits.RB4
#define UP_WPU                  WPUBbits.WPUB4
#define UP_OD                   ODCONBbits.ODCB4
#define UP_ANS                  ANSELBbits.ANSELB4
#define UP_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define UP_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define UP_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define UP_GetValue()           PORTBbits.RB4
#define UP_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define UP_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define UP_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define UP_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define UP_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define UP_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define UP_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define UP_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)
#define RB4_SetInterruptHandler  UP_SetInterruptHandler

// get/set RB5 aliases
#define RX_TRIS                 TRISBbits.TRISB5
#define RX_LAT                  LATBbits.LATB5
#define RX_PORT                 PORTBbits.RB5
#define RX_WPU                  WPUBbits.WPUB5
#define RX_OD                   ODCONBbits.ODCB5
#define RX_ANS                  ANSELBbits.ANSELB5
#define RX_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RX_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RX_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RX_GetValue()           PORTBbits.RB5
#define RX_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RX_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define RX_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define RX_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define RX_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define RX_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define RX_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RB6 aliases
#define TX_TRIS                 TRISBbits.TRISB6
#define TX_LAT                  LATBbits.LATB6
#define TX_PORT                 PORTBbits.RB6
#define TX_WPU                  WPUBbits.WPUB6
#define TX_OD                   ODCONBbits.ODCB6
#define TX_ANS                  ANSELBbits.ANSELB6
#define TX_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define TX_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define TX_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define TX_GetValue()           PORTBbits.RB6
#define TX_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define TX_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define TX_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define TX_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define TX_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define TX_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define TX_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set RB7 aliases
#define PWM_TRIS                 TRISBbits.TRISB7
#define PWM_LAT                  LATBbits.LATB7
#define PWM_PORT                 PORTBbits.RB7
#define PWM_WPU                  WPUBbits.WPUB7
#define PWM_OD                   ODCONBbits.ODCB7
#define PWM_ANS                  ANSELBbits.ANSELB7
#define PWM_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define PWM_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define PWM_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define PWM_GetValue()           PORTBbits.RB7
#define PWM_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define PWM_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define PWM_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define PWM_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define PWM_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define PWM_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define PWM_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define PWM_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC0 aliases
#define GATE_TRIS                 TRISCbits.TRISC0
#define GATE_LAT                  LATCbits.LATC0
#define GATE_PORT                 PORTCbits.RC0
#define GATE_WPU                  WPUCbits.WPUC0
#define GATE_OD                   ODCONCbits.ODCC0
#define GATE_ANS                  ANSELCbits.ANSELC0
#define GATE_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define GATE_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define GATE_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define GATE_GetValue()           PORTCbits.RC0
#define GATE_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define GATE_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define GATE_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define GATE_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define GATE_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define GATE_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define GATE_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define GATE_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)
#define RC0_SetInterruptHandler  GATE_SetInterruptHandler

// get/set RC1 aliases
#define PHOTOCELL_TRIS                 TRISCbits.TRISC1
#define PHOTOCELL_LAT                  LATCbits.LATC1
#define PHOTOCELL_PORT                 PORTCbits.RC1
#define PHOTOCELL_WPU                  WPUCbits.WPUC1
#define PHOTOCELL_OD                   ODCONCbits.ODCC1
#define PHOTOCELL_ANS                  ANSELCbits.ANSELC1
#define PHOTOCELL_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define PHOTOCELL_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define PHOTOCELL_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define PHOTOCELL_GetValue()           PORTCbits.RC1
#define PHOTOCELL_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define PHOTOCELL_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define PHOTOCELL_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define PHOTOCELL_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define PHOTOCELL_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define PHOTOCELL_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define PHOTOCELL_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define PHOTOCELL_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)
#define RC1_SetInterruptHandler  PHOTOCELL_SetInterruptHandler

// get/set RC2 aliases
#define BUTTON_TRIS                 TRISCbits.TRISC2
#define BUTTON_LAT                  LATCbits.LATC2
#define BUTTON_PORT                 PORTCbits.RC2
#define BUTTON_WPU                  WPUCbits.WPUC2
#define BUTTON_OD                   ODCONCbits.ODCC2
#define BUTTON_ANS                  ANSELCbits.ANSELC2
#define BUTTON_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define BUTTON_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define BUTTON_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define BUTTON_GetValue()           PORTCbits.RC2
#define BUTTON_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define BUTTON_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define BUTTON_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define BUTTON_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define BUTTON_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define BUTTON_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define BUTTON_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define BUTTON_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)
#define RC2_SetInterruptHandler  BUTTON_SetInterruptHandler

// get/set RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSELC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSELC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define ENTER_TRIS                 TRISCbits.TRISC5
#define ENTER_LAT                  LATCbits.LATC5
#define ENTER_PORT                 PORTCbits.RC5
#define ENTER_WPU                  WPUCbits.WPUC5
#define ENTER_OD                   ODCONCbits.ODCC5
#define ENTER_ANS                  ANSELCbits.ANSELC5
#define ENTER_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define ENTER_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define ENTER_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define ENTER_GetValue()           PORTCbits.RC5
#define ENTER_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define ENTER_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define ENTER_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define ENTER_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define ENTER_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define ENTER_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define ENTER_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define ENTER_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)
#define RC5_SetInterruptHandler  ENTER_SetInterruptHandler

// get/set RC6 aliases
#define STOP_TRIS                 TRISCbits.TRISC6
#define STOP_LAT                  LATCbits.LATC6
#define STOP_PORT                 PORTCbits.RC6
#define STOP_WPU                  WPUCbits.WPUC6
#define STOP_OD                   ODCONCbits.ODCC6
#define STOP_ANS                  ANSELCbits.ANSELC6
#define STOP_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define STOP_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define STOP_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define STOP_GetValue()           PORTCbits.RC6
#define STOP_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define STOP_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define STOP_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define STOP_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define STOP_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define STOP_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define STOP_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define STOP_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 aliases
#define DIR_TRIS                 TRISCbits.TRISC7
#define DIR_LAT                  LATCbits.LATC7
#define DIR_PORT                 PORTCbits.RC7
#define DIR_WPU                  WPUCbits.WPUC7
#define DIR_OD                   ODCONCbits.ODCC7
#define DIR_ANS                  ANSELCbits.ANSELC7
#define DIR_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define DIR_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define DIR_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define DIR_GetValue()           PORTCbits.RC7
#define DIR_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define DIR_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define DIR_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define DIR_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define DIR_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define DIR_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define DIR_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define DIR_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the DOWN pin functionality
 * @param none
 * @return none
 */
void DOWN_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for DOWN pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for DOWN at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void DOWN_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for DOWN pin.
 *        This is a dynamic interrupt handler to be used together with the DOWN_SetInterruptHandler() method.
 *        This handler is called every time the DOWN ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*DOWN_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for DOWN pin. 
 *        This is a predefined interrupt handler to be used together with the DOWN_SetInterruptHandler() method.
 *        This handler is called every time the DOWN ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void DOWN_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the BACK pin functionality
 * @param none
 * @return none
 */
void BACK_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BACK pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for BACK at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void BACK_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for BACK pin.
 *        This is a dynamic interrupt handler to be used together with the BACK_SetInterruptHandler() method.
 *        This handler is called every time the BACK ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*BACK_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BACK pin. 
 *        This is a predefined interrupt handler to be used together with the BACK_SetInterruptHandler() method.
 *        This handler is called every time the BACK ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void BACK_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the UP pin functionality
 * @param none
 * @return none
 */
void UP_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for UP pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for UP at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void UP_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for UP pin.
 *        This is a dynamic interrupt handler to be used together with the UP_SetInterruptHandler() method.
 *        This handler is called every time the UP ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*UP_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for UP pin. 
 *        This is a predefined interrupt handler to be used together with the UP_SetInterruptHandler() method.
 *        This handler is called every time the UP ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void UP_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the GATE pin functionality
 * @param none
 * @return none
 */
void GATE_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for GATE pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for GATE at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void GATE_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for GATE pin.
 *        This is a dynamic interrupt handler to be used together with the GATE_SetInterruptHandler() method.
 *        This handler is called every time the GATE ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*GATE_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for GATE pin. 
 *        This is a predefined interrupt handler to be used together with the GATE_SetInterruptHandler() method.
 *        This handler is called every time the GATE ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void GATE_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the PHOTOCELL pin functionality
 * @param none
 * @return none
 */
void PHOTOCELL_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PHOTOCELL pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for PHOTOCELL at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void PHOTOCELL_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for PHOTOCELL pin.
 *        This is a dynamic interrupt handler to be used together with the PHOTOCELL_SetInterruptHandler() method.
 *        This handler is called every time the PHOTOCELL ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*PHOTOCELL_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PHOTOCELL pin. 
 *        This is a predefined interrupt handler to be used together with the PHOTOCELL_SetInterruptHandler() method.
 *        This handler is called every time the PHOTOCELL ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void PHOTOCELL_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the BUTTON pin functionality
 * @param none
 * @return none
 */
void BUTTON_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BUTTON pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for BUTTON at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void BUTTON_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for BUTTON pin.
 *        This is a dynamic interrupt handler to be used together with the BUTTON_SetInterruptHandler() method.
 *        This handler is called every time the BUTTON ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*BUTTON_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BUTTON pin. 
 *        This is a predefined interrupt handler to be used together with the BUTTON_SetInterruptHandler() method.
 *        This handler is called every time the BUTTON ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void BUTTON_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the ENTER pin functionality
 * @param none
 * @return none
 */
void ENTER_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for ENTER pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for ENTER at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void ENTER_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for ENTER pin.
 *        This is a dynamic interrupt handler to be used together with the ENTER_SetInterruptHandler() method.
 *        This handler is called every time the ENTER ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*ENTER_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for ENTER pin. 
 *        This is a predefined interrupt handler to be used together with the ENTER_SetInterruptHandler() method.
 *        This handler is called every time the ENTER ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void ENTER_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/