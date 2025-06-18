/*****************************************************
 *  DIYfan.blogspot.com                              *
 *                                                   *
 * Small library for driving a 4 digit dsplay module *
 * with TM1637 chip.                                 *
 *                                                   *
 *****************************************************/

#ifndef TM1637_H
#define	TM1637_H

// Change the ports to suit your project
// For microcontrollers with LAT registers RA. RB, RC can be replaced with LATA, LATB, LATC ets.
#define TM1637_CLK RC3
#define TM1637_CLK_DIR TRISC3
#define TM1637_DIO RC4
#define TM1637_DIO_DIR TRISC4

#define MAX_BRIGHTNESS 7
#define NORMAL_BRIGHTNESS 4
#define MAX_POSITION 3

#include <xc.h>


// Sets the defined pins as outputs and clear the display.
// This function must be called first.
void TM1637_init(void);

// Sets the brightness of the display. 
// If the brigtness is bigger than 7, the function will not change the brightness.
// @param brightness: 0..7
void setBrightness(uint8_t brightness);

// Displays a single character at specified position and with or without the dot
// @param ch:      the character to be displayed. If the character is not defined, displays blank
// @param pos:     0..3 - position of the character 
// @param dotFlag: 0 - dot off; 1 - dot on
void displayChar(char ch, uint8_t pos, uint8_t dotFlag);

// Displays a string from startPos, 
// If in the string have dots, they will be displayed
// @param str:      null-terminated string
// @param startPos: 0..3
void displayString(const char str[], uint8_t startPos);

// displays a number between -999 to 9999 with specified number of digits after the dot
// It will be left adjusted
// displayNumber(1234, 3, 0) -> "1.234"; displayNumber(123, 3, 0) -> "0.123"
// displayNumber(-123, 3, 0) -> "-0.12"; displayNumber(123, 0, 0) -> "123 "
// @param num:           -999..9999
// @param precision:     0..3 - number of digit after the dot, 0 for no dot
// @param startPosition: 0..3
void displayNumber(int16_t num, int8_t precision, uint8_t startPostition);

// Switch off the display. The content stays in the memory.
void displayOFF(void);

// Switch on the display and shows the content stored in the memory
void displayON(void);

// Clears the display
#define clearDisplay() displayString("    ", 0)


#endif	/* TM1637_H */

