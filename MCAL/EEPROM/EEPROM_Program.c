/*
 * EEPROM_Program.c
 *
 *  Created on: Aug 18, 2024
 *      Author: ibrahim 
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Config.h"
#include "EEPROM_Private.h"
#include <util/delay.h>
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;



/**
 * @Name: EEPROM_WriteByte
 * @Parameters (in): uint16_t address - The EEPROM address to write to
 *                   uint8_t data - The data byte to be written to the EEPROM
 * @return: void
 * @brief: Writes a byte of data to the specified EEPROM address.
 */

void EEPROM_WriteByte(uint16_t address, uint8_t data) {
    // Wait for completion of previous write
    while (EECR & (1 << EEWE));

    // Set up address and data registers
    EEARL = (uint8_t)address;
    EEARH = (uint8_t)(address >> 8);
    EEDR = data;

    // Write logical one to EEMWE
    EECR |= (1 << EEMWE);

    // Start EEPROM write by setting EEWE
    EECR |= (1 << EEWE);
}

/**
 * @Name: EEPROM_ReadByte
 * @Parameters (in): uint16_t address - The EEPROM address to read from
 * @return: uint8_t - The data byte read from the specified EEPROM address
 * @brief: Reads a byte of data from the specified EEPROM address.
 */

uint8_t EEPROM_ReadByte(uint16_t address) {
    // Wait for completion of previous write
    while (EECR & (1 << EEWE));

    // Set up address register
    EEARL = (uint8_t)address;
    EEARH = (uint8_t)(address >> 8);

    // Start EEPROM read by writing EERE
    EECR |= (1 << EERE);

    // Return data from data register
    return EEDR;
}

/**
 * @Name: EEPROM_WriteBlock
 * @Parameters (in): const void* src - Pointer to the source data to be written to EEPROM
 *                   void* dest - The EEPROM starting address for the block write
 *                   uint16_t size - The size of the block to be written
 * @return: void
 * @brief: Writes a block of data to EEPROM starting from the specified destination address.
 */

void EEPROM_WriteBlock(const void* src, void* dest, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
        EEPROM_WriteByte((uint16_t)dest + i, ((uint8_t*)src)[i]);
    }
}

/**
 * @Name: EEPROM_ReadBlock
 * @Parameters (in): void* dest - Pointer to the destination buffer where the EEPROM data will be stored
 *                   const void* src - The EEPROM starting address for the block read
 *                   uint16_t size - The size of the block to be read
 * @return: void
 * @brief: Reads a block of data from EEPROM starting from the specified source address and stores it in the destination buffer.
 */

void EEPROM_ReadBlock(void* dest, const void* src, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
        ((uint8_t*)dest)[i] = EEPROM_ReadByte((uint16_t)src + i);
    }
}
