/**
 * UART1 Generated Driver API Header File
 * 
 * @file uart1.c
 * 
 * @ingroup uart1
 * 
 * @brief This is the generated driver implementation file for the UART1 driver using the Universal Asynchronous Receiver and Transmitter (UART) module.
 *
 * @version UART1 Driver Version 3.0.6
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
#include "../uart1.h"

/**
  Section: Macro Declarations
*/

/**
  Section: Driver Interface
 */

const uart_drv_interface_t UART1 = {
    .Initialize = &UART1_Initialize,
    .Deinitialize = &UART1_Deinitialize,
    .Read = &UART1_Read,
    .Write = &UART1_Write,
    .IsRxReady = &UART1_IsRxReady,
    .IsTxReady = &UART1_IsTxReady,
    .IsTxDone = &UART1_IsTxDone,
    .TransmitEnable = &UART1_TransmitEnable,
    .TransmitDisable = &UART1_TransmitDisable,
    .AutoBaudSet = &UART1_AutoBaudSet,
    .AutoBaudQuery = &UART1_AutoBaudQuery,
    .BRGCountSet = NULL,
    .BRGCountGet = NULL,
    .BaudRateSet = NULL,
    .BaudRateGet = NULL,
    .AutoBaudEventEnableGet = NULL,
    .ErrorGet = &UART1_ErrorGet,
    .TxCompleteCallbackRegister = NULL,
    .RxCompleteCallbackRegister = NULL,
    .TxCollisionCallbackRegister = NULL,
    .FramingErrorCallbackRegister = &UART1_FramingErrorCallbackRegister,
    .OverrunErrorCallbackRegister = &UART1_OverrunErrorCallbackRegister,
    .ParityErrorCallbackRegister = &UART1_ParityErrorCallbackRegister,
    .EventCallbackRegister = NULL,
};

/**
  Section: UART1 variables
*/
volatile uart1_status_t uart1RxLastError;

/**
  Section: UART1 APIs
*/

void (*UART1_FramingErrorHandler)(void);
void (*UART1_OverrunErrorHandler)(void);
void (*UART1_ParityErrorHandler)(void);

static void UART1_DefaultFramingErrorCallback(void);
static void UART1_DefaultOverrunErrorCallback(void);
static void UART1_DefaultParityErrorCallback(void);

/**
  Section: UART1  APIs
*/

void UART1_Initialize(void)
{

    // Set the UART1 module to the options selected in the user interface.

    //
    U1RXB = 0x0; 
    //RXCHK disabled; 
    U1RXCHK = 0x0; 
    //TXB disabled; 
    U1TXB = 0x0; 
    //TXCHK disabled; 
    U1TXCHK = 0x0; 
    //P1L 0x0; 
    U1P1L = 0x0; 
    //P1H 0x0; 
    U1P1H = 0x0; 
    //P2L 0x0; 
    U1P2L = 0x0; 
    //P2H 0x0; 
    U1P2H = 0x0; 
    //P3L 0x0; 
    U1P3L = 0x0; 
    //P3H 0x0; 
    U1P3H = 0x0; 
    //MODE Asynchronous 8-bit mode; RXEN enabled; TXEN enabled; ABDEN disabled; BRGS high speed; 
    U1CON0 = 0xB0; 
    //SENDB disabled; BRKOVR disabled; RXBIMD Set RXBKIF on rising RX input; WUE disabled; ON enabled; 
    U1CON1 = 0x80; 
    //FLO off; TXPOL not inverted; C0EN Add all TX and RX characters; STP Transmit 1Stop bit, receiver verifies first Stop bit; RXPOL not inverted; RUNOVF RX input shifter stops all activity; 
    U1CON2 = 0x8; 
    //BRGL 130; 
    U1BRGL = 0x82; 
    //BRGH 6; 
    U1BRGH = 0x6; 
    //TXBE empty; STPMD in middle of first Stop bit; TXWRE No error; 
    U1FIFO = 0x2E; 
    //ABDIE disabled; ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; 
    U1UIR = 0x0; 
    //TXCIF equal; RXFOIF not overflowed; RXBKIF No Break detected; FERIF no error; CERIF No Checksum error; ABDOVF Not overflowed; PERIF no parity error; TXMTIF empty; 
    U1ERRIR = 0x80; 
    //TXCIE disabled; RXFOIE disabled; RXBKIE disabled; FERIE disabled; CERIE disabled; ABDOVE disabled; PERIE disabled; TXMTIE disabled; 
    U1ERRIE = 0x0; 

    UART1_FramingErrorCallbackRegister(UART1_DefaultFramingErrorCallback);
    UART1_OverrunErrorCallbackRegister(UART1_DefaultOverrunErrorCallback);
    UART1_ParityErrorCallbackRegister(UART1_DefaultParityErrorCallback);

    uart1RxLastError.status = 0;  
}

void UART1_Deinitialize(void)
{
    U1RXB = 0x00;
    U1RXCHK = 0x00;
    U1TXB = 0x00;
    U1TXCHK = 0x00;
    U1P1L = 0x00;
    U1P1H = 0x00;
    U1P2L = 0x00;
    U1P2H = 0x00;
    U1P3L = 0x00;
    U1P3H = 0x00;
    U1CON0 = 0x00;
    U1CON1 = 0x00;
    U1CON2 = 0x00;
    U1BRGL = 0x00;
    U1BRGH = 0x00;
    U1FIFO = 0x00;
    U1UIR = 0x00;
    U1ERRIR = 0x00;
    U1ERRIE = 0x00;
}

inline void UART1_Enable(void)
{
    U1CON1bits.ON = 1; 
}

inline void UART1_Disable(void)
{
    U1CON1bits.ON = 0; 
}

inline void UART1_TransmitEnable(void)
{
    U1CON0bits.TXEN = 1;
}

inline void UART1_TransmitDisable(void)
{
    U1CON0bits.TXEN = 0;
}

inline void UART1_ReceiveEnable(void)
{
    U1CON0bits.RXEN = 1;
}

inline void UART1_ReceiveDisable(void)
{
    U1CON0bits.RXEN = 0;
}

inline void UART1_SendBreakControlEnable(void)
{
    U1CON1bits.SENDB = 1;
}

inline void UART1_SendBreakControlDisable(void)
{
    U1CON1bits.SENDB = 0;
}

inline void UART1_AutoBaudSet(bool enable)
{
    if(enable)
    {
        U1CON0bits.ABDEN = 1; 
    }
    else
    {
      U1CON0bits.ABDEN = 0;  
    }
}


inline bool UART1_AutoBaudQuery(void)
{
    return (bool)U1UIRbits.ABDIF; 
}

inline void UART1_AutoBaudDetectCompleteReset(void)
{
    U1UIRbits.ABDIF = 0; 
}

inline bool UART1_IsAutoBaudDetectOverflow(void)
{
    return (bool)U1ERRIRbits.ABDOVF; 
}

inline void UART1_AutoBaudDetectOverflowReset(void)
{
    U1ERRIRbits.ABDOVF = 0; 
}

bool UART1_IsRxReady(void)
{
    return (bool)(!U1FIFObits.RXBE);
}

bool UART1_IsTxReady(void)
{
    return (bool)(U1FIFObits.TXBE && U1CON0bits.TXEN);
}

bool UART1_IsTxDone(void)
{
    return U1ERRIRbits.TXMTIF;
}

size_t UART1_ErrorGet(void)
{
    uart1RxLastError.status = 0;
    
    if(U1ERRIRbits.FERIF)
    {
        uart1RxLastError.ferr = 1;
        if(NULL != UART1_FramingErrorHandler)
        {
            UART1_FramingErrorHandler();
        }  
    }
    if(U1ERRIRbits.RXFOIF)
    {
        uart1RxLastError.oerr = 1;
        if(NULL != UART1_OverrunErrorHandler)
        {
            UART1_OverrunErrorHandler();
        }   
    }

    return uart1RxLastError.status;
}

uint8_t UART1_Read(void)
{
    return U1RXB;
}


void UART1_Write(uint8_t txData)
{
    while (!UART1_IsTxReady());
    U1TXB = txData; 
}


void UART1_WriteString(const char* str) {
    while (*str != '\0') {
        putch(*str++);
    }
}

void UART1_WriteUInt(uint16_t value) {
    char buffer[6]; // Enough for "65535\0"
    uint8_t i = 0;

    if (value == 0) {
        UART1_Write('0');
        return;
    }

    // Convert number to string in reverse
    while (value > 0 && i < sizeof(buffer) - 1) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    // Send characters in correct order
    while (i > 0) {
        UART1_Write(buffer[--i]);
    }
}



int getch(void)
{
    while(!(UART1_IsRxReady()));
    return UART1_Read();
}

void putch(char txData)
{
    while(!(UART1_IsTxReady()));
    return UART1_Write(txData);   
}


static void UART1_DefaultFramingErrorCallback(void)
{
    
}

static void UART1_DefaultOverrunErrorCallback(void)
{
    
}

static void UART1_DefaultParityErrorCallback(void)
{
    
}

void UART1_FramingErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        UART1_FramingErrorHandler = callbackHandler;
    }
}

void UART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        UART1_OverrunErrorHandler = callbackHandler;
    }    
}

void UART1_ParityErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        UART1_ParityErrorHandler = callbackHandler;
    } 
}

void UART1_WriteHexDigit(uint8_t digit) {
    const char hexChars[] = "0123456789ABCDEF";
    if (digit < 16) {
        putch(hexChars[digit]);
    }
}




// Simple helper: print a string
void printString(const char* str) {
    while (*str) {
        putch(*str++);
    }
    
}

// Simple helper: print integer as decimal
void printInt(uint16_t value) {
    char buf[10];
    int i = 0;
    if (value == 0) {
        putch('0');
        return;
    }
    
    while (value > 0) {
        buf[i++] = (value % 10) + '0';
        value /= 10;
    }
    while (i--) {
        putch(buf[i]);
    }
    
}

// Print current in format: Current: -x.yy A\r\n
void printCurrent(uint16_t current_mA) {
    
    uint16_t amps = current_mA / 1000;
    uint16_t hundredths = (current_mA % 1000) / 10;

    UART1_WriteString("Current: ");
    printInt(amps);
    putch('.');
    if (hundredths < 10) putch('0'); // leading zero for decimals < 10
    printInt(hundredths);
    UART1_WriteString(" A\r\n");

}

