/*
 * File:   menu.c
 * Author: ricardobarbosa
 *
 * Created on June 6, 2025, 1:38 PM
 */


#include <xc.h>

#include "menu.h"
#include "mcc_generated_files/uart/uart1.h"
#include <string.h>
#include "debug.h"
#include "mcc_generated_files/nvm/nvm.h"
#include "motor.h"

volatile SystemState_t systemState = STATE_NORMAL;
static MenuOption_t currentOption = MENU_OPTION_SPEED;
volatile ConfigMode_t configMode = CONFIG_MODE_NONE;

volatile bool menuMode = false;

volatile bool configFlag = false;

volatile bool configDone = false;

volatile uint16_t overcurrentThreshold = 5000;

static const char* menuOptionNames[] = {
    "Set Speed",
    "Config Mode",
    "Overcurrent",
    "Time Config",
    "Save and Exit"
};

void Menu_PrintCurrentOption(void) {
    DEBUG_PRINT("Option: ");
    DEBUG_PRINT(menuOptionNames[currentOption]);
    DEBUG_PRINT("\r\n");

    // Display only the first 4 uppercase letters (or a mapped string)
    char shortLabel[5] = "----"; // Default filler

    switch (currentOption) {
        case MENU_OPTION_SPEED:
            strcpy(shortLabel, "SPED");
            break;
        case MENU_OPTION_CONFIG_MOTOR:
            strcpy(shortLabel, "CONF");
            break;
        case MENU_OPTION_OVERCURRENT:
            strcpy(shortLabel, "OVRC");
            break;
        case MENU_OPTION_TIME:
            strcpy(shortLabel, "TIME");
            break;
        case MENU_OPTION_SAVE_EXIT:
            strcpy(shortLabel, "SAVE");
            break;
        case MENU_OPTION_COUNT:
            break;
        default:
            break;
    }

    displayString(shortLabel, 0);
}

void Menu_SaveSettings(void) {
    
    EEPROM_WriteUInt16(EEPROM_ADDR_SPEED_LEVEL, speedLevel);
    EEPROM_WriteUInt16(EEPROM_ADDR_OPEN_DURATION, openFullDuration);
    EEPROM_WriteUInt16(EEPROM_ADDR_CLOSE_DURATION, closeFullDuration);
    EEPROM_WriteUInt16(EEPROM_ADDR_OVERCURRENT, overcurrentThreshold);
    EEPROM_WriteUInt16(EEPROM_ADDR_TIME_AUTO, timeAuto);

    DEBUG_PRINT("Settings Saved\r\n");
    
    configDone = 1;

}

void Menu_AdjustSpeed(bool increase) {
    if (increase && speedLevel < 8) {
        speedLevel++;
    } else if (!increase && speedLevel > 0) {
        speedLevel--;
    } else {
        return;
    }

    Motor_UpdateSpeedLevel(); // Update PWM period

    char label[5] = "SPD ";
    label[3] = '0' + speedLevel; // SPD0 - SPD4
    displayString(label, 0);

    DEBUG_PRINT("Speed Level set to: ");
    DEBUG_PRINT_INT(speedLevel);
    DEBUG_PRINT(", PWM Period: ");
    DEBUG_PRINT_INT(pwmPeriod);
    DEBUG_PRINT("\r\n");
}

void Menu_AdjustOvercurrent(bool increase) {
    if (increase && overcurrentThreshold < 9000) {
        overcurrentThreshold += 1000;
    } else if (!increase && overcurrentThreshold > 1000) {
        overcurrentThreshold -= 1000;
    } else {
        return; // Out of bounds, do nothing
    }

    char label[5] = "OVR ";
    label[3] = '0' + (overcurrentThreshold / 1000); // e.g., '5' for 5000
    displayString(label, 0);

    DEBUG_PRINT("Overcurrent set to: ");
    DEBUG_PRINT_INT(overcurrentThreshold);
    DEBUG_PRINT(" mA\r\n");
}

void Menu_AdjustTime(bool increase) {
    if (increase && timeAuto < 9000) {
        timeAuto += 1000;
    } else if (!increase && timeAuto > 1000) {
        timeAuto -= 1000;
    } else {
        return;
    }
    
    char label[5] = "TME ";
    label[3] = '0' + (timeAuto / 1000);
    displayString(label, 0);

    DEBUG_PRINT("Time for Auto Close set to: ");
    DEBUG_PRINT_INT(timeAuto);
    DEBUG_PRINT(" ms\r\n");
    
}

 void HandleButtonMenuConfig(void) {
    switch (configMode) {
        case CONFIG_MODE_NONE:
            configMode = CONFIG_MODE_OPEN_FULL;
            DEBUG_PRINT("Start OPEN FULL\r\n");
            break;

        case CONFIG_MODE_OPEN_FULL:
            configMode = CONFIG_MODE_OPEN_SLOW;
            openFullDuration = timer0_ms;
            DEBUG_PRINT("Switched to OPEN SLOW after ");
            DEBUG_PRINT_INT(openFullDuration);
            UART1_WriteUInt(openFullDuration);
            DEBUG_PRINT(" ms\r\n");
            break;

        case CONFIG_MODE_OPEN_SLOW:
            timer0_ms = 0;
            configMode = CONFIG_MODE_CLOSE_FULL;
            DEBUG_PRINT("Start CLOSE FULL\r\n");
            break;

        case CONFIG_MODE_CLOSE_FULL:
            configMode = CONFIG_MODE_CLOSE_SLOW;
            closeFullDuration = timer0_ms;
            DEBUG_PRINT("Switched to CLOSE SLOW after ");
            DEBUG_PRINT_INT(closeFullDuration);
            UART1_WriteUInt(closeFullDuration);
            DEBUG_PRINT(" ms\r\n");
            break;

        case CONFIG_MODE_CLOSE_SLOW:
            configMode = CONFIG_MODE_NONE;
            timer0_ms = 0;
            DEBUG_PRINT("Configuration complete.\r\n");
            break;
    }

    HandleConfigMode();
}


void Menu_HandleEnterPress(void) {
    DEBUG_PRINT("Entered Menu\r\n");
    
    configFlag = true;
    switch (systemState) {
        case STATE_NORMAL:
            systemState = STATE_MENU;
            DEBUG_PRINT("\r\n--- Menu Mode ---\r\n");
            clearDisplay();
            displayString("CONF", 0);
            Menu_PrintCurrentOption();
            break;

        case STATE_MENU:
            systemState = STATE_CONFIG;
            DEBUG_PRINT("-> Configuring: ");
            DEBUG_PRINT(menuOptionNames[currentOption]);
            DEBUG_PRINT("\r\n");

            // Handle each menu config option here
            switch (currentOption) {
                case MENU_OPTION_SPEED:
                    DEBUG_PRINT("Entered Speed Config\r\n");
                    clearDisplay();
                    displayString("SPD", 0);
                    break;

                case MENU_OPTION_CONFIG_MOTOR:
                    clearDisplay();
                    displayString("MOTR", 0);
                    break;

                case MENU_OPTION_OVERCURRENT:
                    DEBUG_PRINT("Entered Overcurrent Config\r\n");
                    clearDisplay();
                    displayString("OVR", 0);
                    break;
                    
                case MENU_OPTION_TIME:
                    DEBUG_PRINT("Entered Time Config\r\n");
                    clearDisplay();
                    displayString("TIM", 0);
                    break;

                case MENU_OPTION_SAVE_EXIT:
                    DEBUG_PRINT("Saving Settings and Exiting\r\n");
                    Menu_SaveSettings();
                    systemState = STATE_NORMAL;
                    clearDisplay();
                    configFlag = 0;
                    menuMode = 0;
                    break;
            }
            break;

    }
}

void Menu_HandleUp(void) {
    if (systemState == STATE_MENU) {
        if (currentOption == 0) {
            currentOption = MENU_OPTION_COUNT - 1;
        } else {
            currentOption--;
        }
        Menu_PrintCurrentOption();
    } else if (systemState == STATE_CONFIG && currentOption == MENU_OPTION_OVERCURRENT) {
        Menu_AdjustOvercurrent(true);   // Increase Overcurrent
    } else if (systemState == STATE_CONFIG && currentOption == MENU_OPTION_SPEED) {
        Menu_AdjustSpeed(true);         // Increase Speed
    } else if (systemState == STATE_CONFIG && currentOption == MENU_OPTION_TIME) {
        Menu_AdjustTime(true);          // Increase Time
    }

}

void Menu_HandleDown(void) {
    if (systemState == STATE_MENU) {
        currentOption = (currentOption + 1) % MENU_OPTION_COUNT;
        Menu_PrintCurrentOption();
    } else if (systemState == STATE_CONFIG && currentOption == MENU_OPTION_OVERCURRENT) {
        Menu_AdjustOvercurrent(false);  // Decrease Overcurrent
    } else if (systemState == STATE_CONFIG && currentOption == MENU_OPTION_SPEED) {
        Menu_AdjustSpeed(false);        // Decrease Speed
    } else if (systemState == STATE_CONFIG && currentOption == MENU_OPTION_TIME) {
        Menu_AdjustTime(false);        // Decrease Time
    }

}

void Menu_HandleBack(void) {
    if (systemState == STATE_CONFIG) {
        // From config mode, go back to menu mode
        systemState = STATE_MENU;
        DEBUG_PRINT("Back to Menu\r\n");
        Menu_PrintCurrentOption();
    } else if (systemState == STATE_MENU) {
        // From menu mode, go back to normal mode
        systemState = STATE_NORMAL;
        configFlag = 0;
        menuMode = 0;
        configDone = true;
        DEBUG_PRINT("Exiting Menu\r\n");
        clearDisplay();
    }
    // If already in normal mode, do nothing or handle accordingly
}