/**
 * ADCC Generated Driver File
 * 
 * @file adcc.c
 * 
 * @ingroup  adcc
 * 
 * @brief This file contains the API implementations for the ADCC driver.
 *
 * @version ADCC Driver Version 2.1.5
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

/**
  Section: Included Files
 */

#include <xc.h>
#include "../adcc.h"
#include "../../../mcc_generated_files/uart/uart1.h"
#include "../../../motor.h"
#include "../../../debug.h"
#include "../../../menu.h"

static void (*ADCC_ADI_InterruptHandler)(void);
static void ADCC_DefaultADI_ISR(void);

/**
  Section: ADCC Module APIs
 */

#define VREF_MV 5000
#define ACS712_OFFSET_MV 2100
#define ACS712_SENSITIVITY_MV_PER_A 100 // 100 mV/A = 100 mA per 10 mV


volatile int currentReadings = 0;
volatile bool overcurrentFlag = false;

void ADCC_Initialize(void) {
    // set the ADCC to the options selected in the User Interface
    //ADLTHL 0; 
    ADLTHL = 0x0;
    //ADLTHH 0; 
    ADLTHH = 0x0;
    //ADUTHL 0; 
    ADUTHL = 0x0;
    //ADUTHH 0; 
    ADUTHH = 0x0;
    //ADSTPTL 0; 
    ADSTPTL = 0x0;
    //ADSTPTH 0; 
    ADSTPTH = 0x0;
    //ADACCU 0x0; 
    ADACCU = 0x0;
    //ADRPT 0; 
    ADRPT = 0x0;
    //ADCHS ANA5; 
    ADPCH = 0x5;
    //ADACQL 1; 
    ADACQL = 0x1;
    //ADACQH 0; 
    ADACQH = 0x0;
    //ADCAP Additional uC disabled; 
    ADCAP = 0x0;
    //ADPREL 0; 
    ADPREL = 0x0;
    //ADPREH 0; 
    ADPREH = 0x0;
    //ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x0;
    //ADCRS 1; ADMD Basic_mode; ADACLR disabled; ADPSIS RES; 
    ADCON2 = 0x10;
    //ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x0;
    //ADMATH registers not updated; 
    ADSTAT = 0x0;
    //ADNREF VSS; ADPREF VDD; 
    ADREF = 0x0;
    //ADACT disabled; 
    ADACT = 0x0;
    //ADCCS FOSC/64; 
    ADCLK = 0x1F;
    //GO_nDONE undefined; ADFM right; ADON disabled; ADCS FOSC; ADCONT disabled; 
    ADCON0 = 0x4;

    //Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
    //Configure interrupt handlers
    ADCC_SetADIInterruptHandler(ADCC_DefaultADI_ISR);
    // Enabling ADCC interrupt.
    PIE1bits.ADIE = 1;

    //Clear the ADC Threshold interrupt flag
    PIR2bits.ADTIF = 0;

    ADCON0bits.ADON = 1;

}

void ADCC_StartConversion(adcc_channel_t channel) {


    //Selects the A/D channel
    ADPCH = channel;

    //Starts the conversion
    ADCON0bits.ADGO = 1;
}

bool ADCC_IsConversionDone(void) {
    //Starts the conversion
    return ((unsigned char) (!ADCON0bits.ADGO));
}

adc_result_t ADCC_GetConversionResult(void) {
    //Returns the result
    return ((adc_result_t) ((ADRESH << 8) + ADRESL));
}

adc_result_t ADCC_GetSingleConversion(adcc_channel_t channel) {
    //Selects the A/D channel
    ADPCH = channel;

    //Disables the continuous mode
    ADCON0bits.ADCONT = 0;

    //Starts the conversion
    ADCON0bits.ADGO = 1;


    //Waits for the conversion to finish
    while (ADCON0bits.ADGO) {
    }


    //Conversion finished, returns the result
    return ((adc_result_t) ((ADRESH << 8) + ADRESL));
}

inline void ADCC_StopConversion(void) {
    //Resets the ADGO bit.
    ADCON0bits.ADGO = 0;
}

inline void ADCC_SetStopOnInterrupt(void) {
    //Sets the ADSOI bit.
    ADCON3bits.ADSOI = 1;
}

inline void ADCC_DischargeSampleCapacitor(void) {
    //Sets the ADC channel to AVss.
    ADPCH = 0x3B;
}

void ADCC_LoadAcquisitionRegister(uint16_t acquisitionValue) {
    //Loads the ADACQH and ADACQL registers.
    ADACQH = (uint8_t) (acquisitionValue >> 8);
    ADACQL = (uint8_t) acquisitionValue;
}

void ADCC_SetPrechargeTime(uint16_t prechargeTime) {
    //Loads the ADPREH and ADPREL registers.
    ADPREH = (uint8_t) (prechargeTime >> 8);
    ADPREL = (uint8_t) prechargeTime;
}

void ADCC_SetRepeatCount(uint8_t repeatCount) {
    //Loads the ADRPT register.
    ADRPT = repeatCount;
}

uint8_t ADCC_GetCurrentCountofConversions(void) {
    //Returns the contents of ADCNT register
    return ADCNT;
}

inline void ADCC_ClearAccumulator(void) {
    //Resets the ADCON2bits.ADACLR bit.
    ADCON2bits.ADACLR = 1;
}

uint24_t ADCC_GetAccumulatorValue(void) {
    //Returns the contents of ADACCU, ADACCH and ADACCL registers
    return (((uint24_t) ADACCU << 16)+((uint24_t) ADACCH << 8) + ADACCL);
}

bool ADCC_HasAccumulatorOverflowed(void) {
    //Returns the status of ADSTATbits.ADAOV
    return ADSTATbits.ADAOV;
}

uint16_t ADCC_GetFilterValue(void) {
    //Returns the contents of ADFLTRH and ADFLTRL registers
    return ((uint16_t) ((ADFLTRH << 8) + ADFLTRL));
}

uint16_t ADCC_GetPreviousResult(void) {
    //Returns the contents of ADPREVH and ADPREVL registers
    return ((uint16_t) ((ADPREVH << 8) + ADPREVL));
}

void ADCC_DefineSetPoint(uint16_t setPoint) {
    //Sets the ADSTPTH and ADSTPTL registers
    ADSTPTH = (uint8_t) (setPoint >> 8);
    ADSTPTL = (uint8_t) setPoint;
}

void ADCC_SetUpperThreshold(uint16_t upperThreshold) {
    //Sets the ADUTHH and ADUTHL registers
    ADUTHH = (uint8_t) (upperThreshold >> 8);
    ADUTHL = (uint8_t) upperThreshold;
}

void ADCC_SetLowerThreshold(uint16_t lowerThreshold) {
    //Sets the ADLTHH and ADLTHL registers
    ADLTHH = (uint8_t) (lowerThreshold >> 8);
    ADLTHL = (uint8_t) lowerThreshold;
}

uint16_t ADCC_GetErrorCalculation(void) {
    //Returns the contents of ADERRH and ADERRL registers
    return ((uint16_t) ((ADERRH << 8) + ADERRL));
}

inline void ADCC_EnableDoubleSampling(void) {
    //Sets the ADCON1bits.ADDSEN
    ADCON1bits.ADDSEN = 1;
}

inline void ADCC_EnableContinuousConversion(void) {
    //Sets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 1;
}

inline void ADCC_DisableContinuousConversion(void) {
    //Resets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 0;
}

bool ADCC_HasErrorCrossedUpperThreshold(void) {
    //Returns the value of ADSTATbits.ADUTHR bit.
    return ADSTATbits.ADUTHR;
}

bool ADCC_HasErrorCrossedLowerThreshold(void) {
    //Returns the value of ADSTATbits.ADLTHR bit.
    return ADSTATbits.ADLTHR;
}

uint8_t ADCC_GetConversionStageStatus(void) {
    //Returns the contents of ADSTATbits.ADSTAT field.
    return ADSTATbits.ADSTAT;
}

// This function checks for overcurrent
void CheckOverCurrent(void) {
    adc_result_t adc = ADCC_GetConversionResult(); // 0?4095
    float voltage = (adc / 4095.0f) * 4.9f; // Convert ADC to volts
    float current_A = (voltage - 2.5f) / 0.1f; // ACS712-20A: 100 mV/A
    int16_t current_mA = (int16_t) (current_A * 1000.0f);
    uint16_t current = abs(current_mA);
    currentReadings++;

    
    if (currentReadings > 10 && motorState == MOTOR_CLOSE_FULL) {
        UART1_WriteString("Current: ");
        printInt(current);
        UART1_WriteString("mA\r\n");
        if (current >= overcurrentThreshold) {
            UART1_WriteString("Overcurrent detected! Stopping motor!!!\r\n");
            overcurrentFlag = true;
            motorState = MOTOR_OPEN_FULL;
            HandleMotorState();
        }
    }
}

// This function is the interrupt handler for the ADC
void ADCC_ISR(void) {
    //Clears the ADCC interrupt flag
    PIR1bits.ADIF = 0;
    CheckOverCurrent();
    if (ADCC_ADI_InterruptHandler != NULL) {
        ADCC_ADI_InterruptHandler();
    }
}

void ADCC_SetADIInterruptHandler(void (* InterruptHandler)(void)) {
    ADCC_ADI_InterruptHandler = InterruptHandler;
}

static void ADCC_DefaultADI_ISR(void) {
    //Add your interrupt code here or
    //Use ADCC_SetADIInterruptHandler() function to use Custom ISR
}
