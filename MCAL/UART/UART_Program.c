/*
 * UART_prog.c
 *
 *  Created on: May 24, 2024
 *      Author: ibrahim 
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "UART_Config.h"
#include "UART_Interface.h"
#include "UART_Private.h"
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;


/**
 * @Name: UART_init
 * @Parameters (in): None
 * @return: void
 * @brief: Initializes the UART module by enabling RX and TX, setting the data format to 8-bit, and setting the baud rate using the prescaler.
 */

void UART_init(void) {
    UCSRB |= (1 << RXEN) | (1 << TXEN); // Enable RX and TX
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // 8-bit data
    UBRRL = BAUD_PRESCALE;
    UBRRH = (BAUD_PRESCALE >> 8);
}

/**
 * @Name: UART_TxChar
 * @Parameters (in): char ch - The character to be transmitted
 * @return: void
 * @brief: Transmits a single character over UART.
 */

void UART_TxChar(char ch) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = ch;
}

/**
 * @Name: UART_RxChar
 * @Parameters (in): None
 * @return: char - The received character from the UART
 * @brief: Receives a single character from UART. Waits until a character is available.
 */

char UART_RxChar(void) {
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}

/**
 * @Name: UART_SendString
 * @Parameters (in): const char* str - A null-terminated string to be transmitted
 * @return: void
 * @brief: Transmits a null-terminated string over UART.
 */

void UART_SendString(const char* str) {
    while (*str) {
        UART_TxChar(*str++);
    }
}

/**
 * @Name: UART_ReceiveString
 * @Parameters (in): char* buffer - The buffer where the received string will be stored
 *                  uint8_t size - The maximum size of the string to be received, including null terminator
 * @return: void
 * @brief: Receives a string of characters until a newline or carriage return is received, or the buffer is full. The string is null-terminated.
 */

void UART_ReceiveString(char* buffer, uint8_t size) {
    uint8_t i = 0;
    char received_char;

    while (i < size - 1) {
        received_char = UART_RxChar();
        if (received_char == '\r' || received_char == '\n') {
            break;
        }
        buffer[i++] = received_char;
    }
    buffer[i] = '\0';  // Null-terminate the string
}
