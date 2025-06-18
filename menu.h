/* 
 * File:   menu.h
 * Author: ricardobarbosa
 *
 * Created on June 6, 2025, 1:39 PM
 */

#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

typedef enum {
    MENU_OPTION_SPEED = 0,
    MENU_OPTION_CONFIG_MOTOR,
    MENU_OPTION_OVERCURRENT,
    MENU_OPTION_TIME,
    MENU_OPTION_SAVE_EXIT,
    MENU_OPTION_COUNT
} MenuOption_t;

typedef enum {
    STATE_NORMAL,
    STATE_MENU,
    STATE_CONFIG
} SystemState_t;

extern volatile SystemState_t systemState;

typedef enum {
    CONFIG_MODE_NONE, // Not in config mode
    CONFIG_MODE_OPEN_FULL, // Opening at full speed
    CONFIG_MODE_OPEN_SLOW, // Opening at slow speed (before end stop)
    CONFIG_MODE_CLOSE_FULL, // Closing at full speed
    CONFIG_MODE_CLOSE_SLOW, // Closing at slow speed (before end stop)
    CONFIG_MODE_OVERCURRENT // Overcurrent        
} ConfigMode_t;

extern volatile ConfigMode_t configMode;

extern volatile bool menuMode;

extern volatile bool configFlag;

extern volatile bool configDone;

extern volatile uint16_t overcurrentThreshold;

void HandleConfigMode(void);
void Menu_Init(void);
void Menu_HandleEnterPress(void);
void Menu_HandleUp(void);
void Menu_HandleDown(void);
void Menu_HandleBack(void);
void HandleButtonMenuConfig(void);


#endif