#ifndef DEBUG_H
#define DEBUG_H

#include "mcc_generated_files/uart/uart1.h"

#ifndef DEBUG
#define DEBUG 0
#endif



#if DEBUG
#define DEBUG_PRINT(msg) UART1_WriteString(msg)

static inline void DEBUG_PRINT_INT(uint16_t value) {
    char buffer[6]; // Enough for "65535\0"
    uint8_t i = 0;

    if (value == 0) {
        UART1_Write('0');
        return;
    }

    // Convert number to string in reverse
    while (value > 0 && i < sizeof (buffer) - 1) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    // Send characters in correct order
    while (i > 0) {
        UART1_Write(buffer[--i]);
    }
}

static inline void DEBUG_PRINT_HEX(uint8_t digit) {
    const char hexChars[] = "0123456789ABCDEF";
    if (digit < 16) {
        putch(hexChars[digit]);
    }
}

#else


#define DEBUG_PRINT(msg) ((void)0)

void UART1_Deinitialize();

static inline void DEBUG_PRINT_INT(uint16_t value) {
    (void) value;
}

static inline void DEBUG_PRINT_HEX(uint8_t digit) {
    (void) digit;
}
#endif

#endif // DEBUG_H
