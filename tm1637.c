/*****************************************************
 *              DIYfan.blogspot.com                  *
 *                                                   *
 * Small library for driving a 4-digit dsplay module *
 * with TM1637 chip.                                 *
 *                                                   *
 *****************************************************/

#include "tm1637.h"

#define COMMAND1_WRITE_AUTO 0b01000000
#define COMMAND1_WRITE_FIX 0b01000100
#define COMMAND2_ADDRESS 0b11000000
#define COMMAND3_DISPLAY_ON 0b10001000
#define COMMAND3_DISPLAY_OFF 0b10000000
#define DOT_ON 0b10000000
#define BLANK_INDEX 10
#define LOW 0
#define HIGH 1

// If the display module doesn't work and has 10nF capacitors on the 
// DIO and CLK buses to the ground, then either 
// 1. remove them or replace them with 82-100pF
// or 
// 2. uncomment the SLOW definition bellow and adjust the delay time from 5 to 50 uS

//#define SLOW
#ifdef SLOW
    #define bitDelay(); __delay_us(5);
#else
    #define bitDelay();
#endif


// Defines the LED segments for every symbol
// The bits are in reverse order and the most significant bit is for the dot
// New characters can be added at the end. 
// The same new characters must be added in the string 'allChars'
const uint8_t segments[] = {
  // xGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b00000000,    // blank
  0b01000000,    // -
  0b01111100,    // b
  0b01010000,    // r
  0b01001000,    // =
  0b01100011,    // degree symbol (*)
  0b01110111,    // A
  0b01111100,    // B (same as b)
  0b00111001,    // C
  0b01011110,    // D
  0b01111001,    // E
  0b01110001,    // F
  0b01111100,    // G
  0b01110110,    // H
  0b00000110,    // I (same as 1)
  0b00011110,    // J
  0b01110110,    // K (approx. same as H)
  0b00111000,    // L
  0b00110111,    // M (approx. custom)
  0b01010100,    // N (approx.)
  0b00111111,    // O (same as 0)
  0b01110011,    // P
  0b01100111,    // Q
  0b01010000,    // R
  0b01101101,    // S (same as 5)
  0b01111000,    // T
  0b00111110,    // U
  0b00111110,    // V (same as U)
  0b00101010,    // W (approx. custom)
  0b01110110,    // X (same as H/K)
  0b01101110,    // Y
  0b01011011     // Z (same as 2)
};

#define ALL_CHARS_COUNT sizeof(segments)
#define DIGIT_COUNT 10

// Character map: must match the order of `segments[]`
const char* allChars = "0123456789 -br=*ABCDEFGHIJKLMNOPQRSTUVWXYZ";

uint8_t TM1637_Brightness;


void TM1637_init()
{    
    TM1637_CLK_DIR = 0;
    TM1637_DIO_DIR = 0;
    TM1637_DIO = 1;
    TM1637_CLK = 1;
    clearDisplay();
    TM1637_Brightness = NORMAL_BRIGHTNESS;
    setBrightness(TM1637_Brightness);
}

// starts the serial data transmission
void start()
{
    TM1637_CLK = HIGH;
    bitDelay();
    TM1637_DIO = HIGH;
    bitDelay();
    TM1637_DIO = LOW;
    bitDelay();
    TM1637_CLK = LOW;
    bitDelay();
}

// stops the serial data transmission
void stop()
{
    TM1637_CLK = LOW;
    bitDelay();
    TM1637_DIO = LOW;
    bitDelay();
    TM1637_CLK = HIGH;
    bitDelay();
    TM1637_DIO = HIGH;
    bitDelay();
}

// send one byte to the display controller
void writeByte(uint8_t data)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        TM1637_CLK = LOW;
        bitDelay();
        TM1637_DIO = data & 0x01;
        bitDelay();
        data >>= 1;
        TM1637_CLK = HIGH;
        bitDelay();
    }
    TM1637_CLK = LOW;
    bitDelay();
    TM1637_DIO = HIGH;
    bitDelay();
    TM1637_CLK = HIGH;
    bitDelay();
    TM1637_DIO_DIR = HIGH;
    bitDelay();
    
    if (TM1637_DIO == LOW)
    {
        TM1637_DIO_DIR = LOW;
        bitDelay();
        TM1637_DIO = LOW;
        bitDelay();
    }
    TM1637_DIO_DIR = LOW;
    bitDelay();
}

void setBrightness(uint8_t br)
{
    if (br < MAX_BRIGHTNESS)
    {
        TM1637_Brightness = br;
        start();
            writeByte(COMMAND3_DISPLAY_ON | br);
        stop();
    }
}


void displayOFF() 
{
    start();
        writeByte(COMMAND3_DISPLAY_OFF);
    stop();
}


void displayON()
{
    setBrightness(TM1637_Brightness);
}

// return the index of a character 'ch' in the 'segments' array
// if the character is not found, return the index of the blank char
uint8_t findChar(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    
    for(uint8_t i = DIGIT_COUNT; i < ALL_CHARS_COUNT; i++)
        if (ch == allChars[i])
            return i;
    
    return BLANK_INDEX; // return index of the blank char
}


void displayChar(char ch, uint8_t pos, uint8_t dotFlag)
{
    uint8_t data = 0;
    data = segments[findChar(ch)];
    if (pos > 3) return;
    if (dotFlag) 
        data |= DOT_ON;
    
    start();
        writeByte(COMMAND1_WRITE_FIX); // set the write mode and address mode
    stop();
    
    start();
        writeByte(COMMAND2_ADDRESS | pos); // set the position of the digit
        writeByte(data); // write the digit data
    stop();
}

// This function displays a string on the display
void displayString(const char str[], uint8_t startPos)
{
    uint8_t pos = startPos;
    uint8_t dotFlag = 0;
    while (pos <= MAX_POSITION && *str)
    {
        if (*(str+1) == '.')
            dotFlag = 1;
        displayChar(*str, pos, dotFlag);
        if (dotFlag)
        {
            str++;
            dotFlag = 0;
        }
        str++;
        pos++;
    }
}

// This function displays a number on the display
void displayNumber(int16_t num, int8_t precision, uint8_t startPosition)
{
    char str[8];
    int8_t pos = 6, minusFlag = 0;
    str[sizeof(str)-1] = 0;
    if (num < 0)
    {
        minusFlag = 1;
        num = -num;
    }
    do
    {
        str[pos] = (num % 10) + '0';
        num /= 10;
        pos--;
        precision--;
        if (precision == 0)
        {
            str[pos] = '.';
            pos--;
            if (num == 0)
            {
                str[pos] = '0';
                pos--;
            }
        }
    } while (num > 0 || precision > 0);
    if (minusFlag)
        str[pos] = '-';
    else
        pos++;
    displayString(str+pos, startPosition);
}
