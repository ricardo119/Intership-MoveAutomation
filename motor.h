/* 
 * File:   motor.h
 * Author: ricardobarbosa
 *
 * Created on June 4, 2025, 10:17 AM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define EMERGENCY_DELAY_MS          1000

    // Duty cycles as expressions/macros
#define OPEN_DUTY_CYCLE             (pwmPeriod / 2)
#define CLOSE_DUTY_CYCLE            (pwmPeriod)
#define OPEN_DUTY_CYCLE_SLOW        (pwmPeriod / 5)
#define CLOSE_DUTY_CYCLE_SLOW       (pwmPeriod * 3 / 10)

    extern uint8_t speedLevel;
    extern uint16_t pwmPeriod;

    typedef enum {
        MOTOR_OFF,
        MOTOR_EMERGENCY,
        MOTOR_OPEN_FULL,
        MOTOR_OPEN_SLOW,
        MOTOR_CLOSE_FULL,
        MOTOR_CLOSE_SLOW,
        MOTOR_OPEN_WAIT_CLOSE,
        MOTOR_OVER_CURRENT,
    } MotorState_t;

    volatile MotorState_t motorState = MOTOR_OFF;

    typedef enum {
        GATE_FLOAT,
        GATE_OPEN,
        GATE_CLOSE
    } GateState_t;

    volatile GateState_t gateState = GATE_CLOSE;

    extern volatile int motorIsRunning;
    extern volatile int emergencyFlag;
    extern volatile int userRequest;

    void Motor_UpdateSpeedLevel(void);

    void EmergencyOpen(void);

    void MotorControl(void);

    void HandleMotorState(void);

    void CheckGateEndPositions(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

