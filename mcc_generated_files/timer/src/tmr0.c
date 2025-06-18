/**
 * TMR0 Generated Driver File
 * 
 * @file tmr0.c
 * 
 * @ingroup tmr0
 * 
 * @brief  Driver implementation for the TMR0 driver
 *
 * @version TMR0 Driver Version 2.1.1
 */
/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#include <xc.h>
#include "../tmr0.h"
#include "../../../mcc_generated_files/system/pins.h"
#include "../../../mcc_generated_files/uart/uart1.h"
#include "../../../mcc_generated_files/adc/adcc.h"
#include "../../../motor.h"
#include "../../../menu.h"
#include "../../../debug.h"

volatile uint16_t timer0_ms = 0;

volatile uint16_t timeAuto = 0;

volatile uint16_t timerTMR0ReloadVal16bit;

volatile uint16_t gateOpenTimerMs = 0;

volatile uint16_t gateOpenFullMs = 0;
volatile uint16_t gateCloseFullMs = 0;

volatile bool timeoutToClose = false;
volatile bool timeoutOpenFull = false;
volatile bool timeoutCloseFull = false;

const struct TMR_INTERFACE Timer0 = {
    .Initialize = TMR0_Initialize,
    .Start = TMR0_Start,
    .Stop = TMR0_Stop,
    .PeriodCountSet = TMR0_PeriodCountSet,
    .TimeoutCallbackRegister = TMR0_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*TMR0_OverflowCallback)(void);
static void TMR0_DefaultOverflowCallback(void);

/**
  Section: TMR0 APIs
 */

void TMR0_Initialize(void) {

    //TMR0H 6; 
    TMR0H = 0x6;

    //TMR0L 0; 
    TMR0L = 0x0;

    //T0CS HFINTOSC; T0CKPS 1:1; T0ASYNC not_synchronised; 
    T0CON1 = 0x70;

    //Load TMRTMR0 value to the 16-bit reload variable
    timerTMR0ReloadVal16bit = ((uint16_t) TMR0H << 8) | TMR0L;

    //Set default callback for TMR0 overflow interrupt
    TMR0_OverflowCallbackRegister(TMR0_DefaultOverflowCallback);

    //Clear Interrupt flag before enabling the interrupt
    PIR3bits.TMR0IF = 0;

    //Enable TMR0 interrupt.
    PIE3bits.TMR0IE = 1;

    //T0OUTPS 1:1; T0EN disabled; T016BIT 16-bit; 
    T0CON0 = 0x10;
}

void TMR0_Start(void) {
    T0CON0bits.T0EN = 1;
}

void TMR0_Stop(void) {
    T0CON0bits.T0EN = 0;
}

uint16_t TMR0_Read(void) {
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow = TMR0L;
    readValHigh = TMR0H;
    readVal = ((uint16_t) readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_Write(size_t timerVal) {
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload(void) {
    TMR0H = timerTMR0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timerTMR0ReloadVal16bit;
}

void TMR0_PeriodCountSet(size_t periodVal) {
    timerTMR0ReloadVal16bit = (uint16_t) periodVal;
}

// This function handles the auto close timeout
void HandleAutoCloseTimeout(void) {
    if (motorState == MOTOR_OPEN_WAIT_CLOSE && ++gateOpenTimerMs >= timeAuto) {
        timeoutToClose = true;
        gateOpenTimerMs = 0;
        MotorControl();
    }
}

// This function handles the full speed transitions
void HandleFullSpeedTransitions(void) {
    if (openFullDuration && motorState == MOTOR_OPEN_FULL && ++gateOpenFullMs >= openFullDuration) {
        DEBUG_PRINT("TMR0 Gate Open Slow\r\n");
        motorState = MOTOR_OPEN_SLOW;
        gateOpenFullMs = 0;
        MotorControl();
    }

    if (closeFullDuration && motorState == MOTOR_CLOSE_FULL && ++gateCloseFullMs >= closeFullDuration) {
        DEBUG_PRINT("TMR0 Gate Close Slow\r\n");
        motorState = MOTOR_CLOSE_SLOW;
        gateCloseFullMs = 0;
        MotorControl();
    }
}

// This function tracks the config timing
void TrackConfigTiming(void) {
    timer0_ms++;
}

// This function is the interrupt handler for the TMR0
void TMR0_OverflowISR(void) {
    // Clear the TMR0 interrupt flag
    PIR3bits.TMR0IF = 0;

    TMR0_Reload();

    HandleAutoCloseTimeout();
    HandleFullSpeedTransitions();
    if (configFlag && (configMode == CONFIG_MODE_OPEN_FULL || configMode == CONFIG_MODE_CLOSE_FULL)) {
        TrackConfigTiming();
    }

    // Optional user callback
    if (TMR0_OverflowCallback) {
        TMR0_OverflowCallback();
    }
}

void TMR0_OverflowCallbackRegister(void (* CallbackHandler)(void)) {
    TMR0_OverflowCallback = CallbackHandler;
}

static void TMR0_DefaultOverflowCallback(void) {
    //Add your interrupt code here or
    //Use TMR0_OverflowCallbackRegister function to use Custom ISR
}

