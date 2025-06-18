#include <xc.h>
#include "../tmr2.h"
#include "../../../mcc_generated_files/adc/adcc.h"
#include "../../../mcc_generated_files/uart/uart1.h"

const struct TMR_INTERFACE Timer2 = {
    .Initialize = TMR2_Initialize,
    .Start = TMR2_Start,
    .Stop = TMR2_Stop,
    .PeriodCountSet = TMR2_PeriodCountSet,
    .TimeoutCallbackRegister = TMR2_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*TMR2_OverflowCallback)(void) = NULL;
static void TMR2_DefaultOverflowCallback(void);

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void){

    // Set TMR2 to the options selected in the User Interface
    // TCS FOSC/4; 
    T2CLKCON = 0x1;
    // TMODE Software control; TCKSYNC Not Synchronized; TCKPOL Rising Edge; TPSYNC Not Synchronized; 
    T2HLT = 0x0;
    // TRSEL T2INPPS pin; 
    T2RST = 0x0;
    // PR 234; 
    T2PR = 0xEA;
    // TMR 0x0; 
    T2TMR = 0x0;

    // Set default overflow callback
    TMR2_OverflowCallbackRegister(TMR2_DefaultOverflowCallback);

    // Clearing IF flag before enabling the interrupt.
    PIR3bits.TMR2IF = 0;
    // Enabling TMR2 interrupt.
    PIE3bits.TMR2IE = 1;
    // TCKPS 1:128; TMRON off; TOUTPS 1:16; 
    T2CON = 0x7F;
}

void TMR2_ModeSet(TMR2_HLT_MODE mode) {
    T2HLTbits.T2MODE = mode;
}

void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset) {
    T2RSTbits.T2RSEL = reset;
}

void TMR2_Start(void) {
    T2CONbits.TMR2ON = 1;
}

void TMR2_Stop(void) {
    T2CONbits.TMR2ON = 0;
}

uint8_t TMR2_Read(void) {
    return TMR2;
}

void TMR2_Write(uint8_t timerVal) {
    TMR2 = timerVal;
}

void TMR2_PeriodCountSet(size_t periodVal) {
    PR2 = (uint8_t)periodVal;
}

void TMR2_ISR(void) {
    static volatile unsigned int CountCallBack = 0;
    PIR3bits.TMR2IF = 0;
    if (++CountCallBack >= TMR2_INTERRUPT_TICKER_FACTOR) {
        if (TMR2_OverflowCallback != NULL) {
            TMR2_OverflowCallback();
        }
        CountCallBack = 0;
        ADCC_StartConversion(channel_ANA5);
    }
}

void TMR2_OverflowCallbackRegister(void (* InterruptHandler)(void)) {
    TMR2_OverflowCallback = InterruptHandler;
}

static void TMR2_DefaultOverflowCallback(void) {
    // Default callback does nothing.
}
