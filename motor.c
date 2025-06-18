/*
 * File:   motor.c
 * Author: ricardobarbosa
 *
 * Created on June 4, 2025, 10:16 AM
 */


#include <xc.h>
#include <stdint.h>
#include "motor.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/pwm/pwm1_16bit.h"
#include "mcc_generated_files/uart/uart1.h"
#include "mcc_generated_files/timer/tmr2.h"
#include "mcc_generated_files/timer/tmr0.h"
#include "tm1637.h"
#include "menu.h"
#include "debug.h"

uint8_t speedLevel = 2;
uint16_t pwmPeriod = 3199;

int lastMotorState = MOTOR_OFF;
int lastConfigMode = CONFIG_MODE_OPEN_FULL;

volatile int motorIsRunning = 0;
volatile int emergencyFlag = 0;
volatile int userRequest = 0;
uint16_t slowdownTimeOpen_ms = 0;
uint16_t slowdownTimeClose_ms = 0;
volatile uint16_t timer0Elapsed_ms = 0;

void Motor_UpdateSpeedLevel(void) {
    // Lower pwmPeriod = higher speed (shorter period)
    const uint16_t speedTable[] = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000}; // Levels 0?8

    if (speedLevel > 8) speedLevel = 8;
    pwmPeriod = speedTable[speedLevel];
}

// This function sets the gate direction, duty cycle, and timer start/stop
void SetGate(uint8_t direction, uint16_t dutyCycle, int timerStart, const char* displayMsg) {
    if (direction) {
        DIR_SetHigh();
    } else {
        DIR_SetLow();
    }
    PWM1_PHASE_A_SetSlice1Output1DutyCycleRegister(dutyCycle);
    PWM1_PHASE_A_LoadBufferRegisters();
    PWM1_PHASE_A_Enable();
    STOP_SetHigh();

    if (timerStart) {
        TMR0_Start();
    } else {
        TMR0_Stop();
    }

    clearDisplay();
    displayString(displayMsg, 0);
}

void OpenGate(void) {
    SetGate(1, OPEN_DUTY_CYCLE, 1, emergencyFlag ? "EMRG" : "OPFL");
}

void OpenGateSlow(void) {
    SetGate(1, OPEN_DUTY_CYCLE_SLOW, 0, "OPSL");
}

void CloseGate(void) {
    SetGate(0, CLOSE_DUTY_CYCLE, 1, "CLFL");
}

void CloseGateSlow(void) {
    SetGate(0, CLOSE_DUTY_CYCLE_SLOW, 0, "CLSL");
}

void EmergencyOpen(void) {

    // Stop the motor
    motorState = MOTOR_OFF;
    gateCloseFullMs = 0;
    gateOpenFullMs = 0;
    HandleMotorState(); // Ensure immediate stop

    __delay_ms(EMERGENCY_DELAY_MS);

    // Start opening
    motorState = MOTOR_OPEN_SLOW ;
    HandleMotorState();
    gateState = GATE_FLOAT;

    while (gateState == GATE_OPEN);
    emergencyFlag = 0;

}

void StopGate(void) {
    PWM1_PHASE_A_SetSlice1Output1DutyCycleRegister(0);
    PWM1_PHASE_A_LoadBufferRegisters();
    PWM1_PHASE_A_Disable();
    STOP_SetLow();
    clearDisplay();
    displayString("STOP", 0);
}

void configOpenGate(void) {
    DIR_SetHigh();
    PWM1_PHASE_A_SetSlice1Output1DutyCycleRegister(OPEN_DUTY_CYCLE);
    PWM1_PHASE_A_LoadBufferRegisters();
    PWM1_PHASE_A_Enable();
    STOP_SetHigh();

    TMR0_Start();

    clearDisplay();
    displayString("OPFL", 0);
}

void configCloseGate(void) {
    DIR_SetLow();
    PWM1_PHASE_A_SetSlice1Output1DutyCycleRegister(CLOSE_DUTY_CYCLE);
    PWM1_PHASE_A_LoadBufferRegisters();
    PWM1_PHASE_A_Enable();
    STOP_SetHigh();

    TMR0_Start();

    clearDisplay();
    displayString("CLFL", 0);
}

// Call this function to enable ADC sampling timer when motor starts

void MotorStartSampling(void) {
    currentReadings = 0;
    TMR2_Start();
}

// Call this function to stop ADC sampling timer when motor stops

void MotorStopSampling(void) {
    currentReadings = 0;
    TMR2_Stop();
}

// Handle emergency situation immediately

static void HandleEmergency(void) {
    if (motorIsRunning && emergencyFlag) {
        DEBUG_PRINT("Emergency triggered: Executing EmergencyOpen()\r\n");
        EmergencyOpen();
    }
}

// Handle motor logic when motor is currently running and no emergency

static void HandleMotorWhileRunning(void) {
    if (!motorIsRunning || emergencyFlag) return;

    if (motorState == MOTOR_OPEN_FULL && gateState == GATE_FLOAT && timeoutOpenFull) {
        timeoutOpenFull = false;
        motorState = MOTOR_OPEN_SLOW;
        DEBUG_PRINT("Transition: MOTOR_OPEN_FULL -> MOTOR_OPEN_SLOW\r\n");
    }
    else if (motorState == MOTOR_CLOSE_FULL && gateState == GATE_FLOAT && timeoutCloseFull) {
        timeoutCloseFull = false;
        motorState = MOTOR_CLOSE_SLOW;
        DEBUG_PRINT("Transition: MOTOR_CLOSE_FULL -> MOTOR_CLOSE_SLOW\r\n");
    } else {
        // No user request - check if gate fully open or closed to stop motor
        if (gateState == GATE_OPEN) {
            if (!overcurrentFlag) {
            motorState = MOTOR_OPEN_WAIT_CLOSE;
            DEBUG_PRINT("Gate fully open: stopping motor and waiting for close\r\n");
            motorIsRunning = 0;
            TMR0_Start();
            } else if (overcurrentFlag) {
                motorState = MOTOR_OFF;
                DEBUG_PRINT("Motor stopped due to an overcurrent\r\n");
                motorIsRunning = 0;
                overcurrentFlag = false;
            }
        }
        else if (gateState == GATE_CLOSE) {
            motorState = MOTOR_OFF;
            DEBUG_PRINT("Gate fully closed: stopping motor\r\n");
        }
    }
}

// Handle motor logic when motor is stopped and no emergency

static void HandleMotorWhileStopped(void) {
    if (motorIsRunning || emergencyFlag) return;

    if (userRequest) {
        if (motorState == MOTOR_OFF && gateState == GATE_CLOSE) {
            motorState = MOTOR_OPEN_FULL;
            gateState = GATE_FLOAT;
            DEBUG_PRINT("User requested open: starting MOTOR_OPEN_FULL\r\n");
        }
        else if (gateState == GATE_OPEN) {
            motorState = MOTOR_CLOSE_FULL;
            gateState = GATE_FLOAT;
            DEBUG_PRINT("User requested close: starting MOTOR_CLOSE_FULL\r\n");
        }
    } else if (gateState == GATE_OPEN && motorState == MOTOR_OPEN_WAIT_CLOSE && timeoutToClose) {
        timeoutToClose = false;
        motorState = MOTOR_CLOSE_FULL;
        gateState = GATE_FLOAT;
        DEBUG_PRINT("Auto close timeout expired: starting MOTOR_CLOSE_FULL\r\n");
        TMR0_Stop();
    }
}

void MotorControl(void) {
    if (menuMode) return;

    HandleEmergency();
    if (emergencyFlag) return;

    HandleMotorWhileRunning();
    HandleMotorWhileStopped();

    HandleMotorState();

    DEBUG_PRINT("MotorControl cycle completed\r\n");
}

void HandleMotorState(void) {

    if (!configFlag) {
        if (lastMotorState != motorState) {
            lastMotorState = motorState;

            switch (motorState) {
                case MOTOR_OFF:
                    StopGate();
                    motorIsRunning = 0;
                    MotorStopSampling();
                    break;

                case MOTOR_OPEN_FULL:
                    OpenGate();
                    motorIsRunning = 1;
                    MotorStopSampling();
                    break;

                case MOTOR_OPEN_SLOW:
                    OpenGateSlow();
                    motorIsRunning = 1;
                    break;

                case MOTOR_CLOSE_FULL:
                    CloseGate();
                    motorIsRunning = 1;
                    MotorStartSampling();
                    break;

                case MOTOR_CLOSE_SLOW:
                    CloseGateSlow();
                    motorIsRunning = 1;
                    MotorStopSampling();
                    break;

                case MOTOR_OPEN_WAIT_CLOSE:
                    StopGate();
                    motorIsRunning = 0;
                    break;

                case MOTOR_EMERGENCY:
                    OpenGate();
                    motorIsRunning = 1;
                    break;
                    
                case MOTOR_OVER_CURRENT:
                    CloseGate();
                    motorIsRunning = 1;
                    break;
                    
                default:
                    break;
            }
        }

    }

    userRequest = 0;
}

void HandleConfigMode(void) {
    if (configFlag) {
        if (lastConfigMode != configMode) {
            lastConfigMode = configMode;

            switch (configMode) {
                case CONFIG_MODE_NONE:
                    DEBUG_PRINT("Config None\r\n");
                    StopGate();
                    motorIsRunning = 0;
                    break;

                case CONFIG_MODE_OPEN_FULL:
                    DEBUG_PRINT("Config Open Full\r\n");
                    configOpenGate();
                    motorIsRunning = 1;
                    break;

                case CONFIG_MODE_OPEN_SLOW:
                    DEBUG_PRINT("Config Open Slow\r\n");
                    OpenGateSlow();
                    motorIsRunning = 1;
                    break;

                case CONFIG_MODE_CLOSE_FULL:
                    DEBUG_PRINT("Config Close Full\r\n");
                    configCloseGate();
                    motorIsRunning = 1;
                    break;

                case CONFIG_MODE_CLOSE_SLOW:
                    DEBUG_PRINT("Config Close Slow\r\n");
                    CloseGateSlow();
                    motorIsRunning = 1;
                    break;
            }
        }
    }
}
