/*
 * main.c
 *
 *  Created on: Aug 1, 2024
 *      Author: ibrahim 
 */

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/DIO/DIO_Config.h"
#include "MCAL/DIO/DIO_Private.h"
#include "MCAL/GLOBAL_INT/GLOB_INT_Interface.h"
#include "MCAL/EXT_INT/EXT_INT_Interface.h"
#include "MCAL/TIMER/TIMER_Interface.h"
#include "MCAL/TIMER/TIMER_Config.h"
#include "MCAL/TIMER/TIMER_Private.h"
#include "HAL/LCD/LCD_Config.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/LCD/LCD_Private.h"
#include "HAL/LED/LED_Config.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/KEYPAD/KPD_Config.h"
#include "HAL/KEYPAD/KPD_Interface.h"
#include "HAL/KEYPAD/KPD_Private.h"
#include "MCAL/UART/UART_Config.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/UART/UART_Private.h"
#include "MCAL/EEPROM/EEPROM_Config.h"
#include "MCAL/EEPROM/EEPROM_Interface.h"
#include "MCAL/EEPROM/EEPROM_Private.h"
#include "HAL/SOLENOID/SOL_Interface.h"
#include "HAL/SOLENOID/SOL_Config.h"
#include "HAL/BUZZER/BUZ_Interface.h"  // Include Buzzer interface
#include "HAL/BUZZER/BUZ_Config.h"     // Include Buzzer config


#include <util/delay.h>

#define F_CPU 8000000UL

#define PASSWORD_SIZE 4
#define NUM_USERS 10

char predefined_passwords[NUM_USERS][PASSWORD_SIZE + 1] = {
    "1234", "2345", "3456", "4567", "5678",
    "6789", "7890", "8901", "9012", "0123"
};

void EEPROM_WritePasswords(void) {
    for (uint8_t i = 0; i < NUM_USERS; i++) {
        EEPROM_WriteBlock(predefined_passwords[i], (void*)(i * PASSWORD_SIZE), PASSWORD_SIZE);
    }
}

void EEPROM_ReadPassword(uint8_t user_id, char* password) {
    EEPROM_ReadBlock(password, (const void*)(user_id * PASSWORD_SIZE), PASSWORD_SIZE);
    password[PASSWORD_SIZE] = '\0'; // Null-terminate the string
}

int main(void) {
    char received_username;
    char received_password[PASSWORD_SIZE + 1];
    char stored_password[PASSWORD_SIZE + 1];
    uint8_t attempts = 3;
    uint8_t user_id = 0;

    UART_init();
    LED_init();
    Solenoid_init();
    Buzzer_init();  // Initialize the buzzer

    // Write predefined passwords to EEPROM (only once)
    EEPROM_WritePasswords();

    while (1) {
        do {
            UART_SendString("Enter user ID (1-10): ");
            received_username = UART_RxChar() - '1'; // Convert '1'-'9' to 0-9

            if (received_username < 0 || received_username >= NUM_USERS) {
                UART_SendString("Invalid User ID.\n");
            }
        } while (received_username < 0 || received_username >= NUM_USERS);

        user_id = received_username;

        while (attempts > 0) {
            UART_SendString("Enter password: ");
            UART_ReceiveString(received_password, PASSWORD_SIZE + 1);  // Receive the password

            // Read stored password from EEPROM for the selected user
            EEPROM_ReadPassword(user_id, stored_password);

            // Debug: Print received and stored passwords
            UART_SendString("\nReceived password: ");
            UART_SendString(received_password);
            UART_SendString("\n");

            if (strcmp(received_password, stored_password) == 0) {
                UART_SendString("Access granted.\n");

                // Activate the solenoid for 5 seconds
                Solenoid_activate();
                UART_SendString("Solenoid activated.\n");
                _delay_ms(5000);  // Solenoid remains active for 5 seconds
                Solenoid_deactivate();
                UART_SendString("Solenoid deactivated.\n");

                // Ask user if they want to control the LED
                UART_SendString("Press 1 to turn on LED, or 0 to turn off LED: ");
                char led_control = UART_RxChar();

                if (led_control == '1') {
                    LED_On();  // Turn on LED
                    UART_SendString("\nLED turned on.\n");
                } else if (led_control == '0') {
                    LED_Off();  // Turn off LED
                    UART_SendString("\nLED turned off.\n");
                } else {
                    UART_SendString("\nInvalid input. No action taken.\n");
                }
                break;
            } else {
                UART_SendString("Access denied.\n");
                attempts--;
            }
        }

        if (attempts == 0) {
            UART_SendString("Too many attempts. Alarm!\n");
            Buzzer_On();  // Turn on buzzer
            _delay_ms(10000);  // Buzzer remains on for 10 seconds
            Buzzer_Off();  // Turn off buzzer
        }

        attempts = 3; // Reset attempts for the next user
    }

    return 0;
}
