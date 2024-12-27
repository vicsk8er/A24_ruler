/*
 * I2CHandler.cpp
 *
 *  Created on: Nov 30, 2024
 *      Author: victorx1
 */

#include "I2CHandler.h"

I2CHandler::I2CHandler(I2C_HandleTypeDef *hi2c) : m_hi2c(hi2c) {}

HAL_StatusTypeDef I2CHandler::write(uint16_t devAddress, uint8_t *data, uint16_t size) {
    return HAL_I2C_Master_Transmit(m_hi2c, devAddress << 1, data, size, 50);
}

HAL_StatusTypeDef I2CHandler::read(uint16_t devAddress, uint8_t *data, uint16_t size) {
    return HAL_I2C_Master_Receive(m_hi2c, devAddress << 1, data, size, 50);
}





























////--Essayer de remplacer le HAL_MAX_DELAY par 50--//
//I2CHandler::I2CHandler(I2C_HandleTypeDef& hi2c1) : hi2c(hi2c1) {}
//
//HAL_StatusTypeDef I2CHandler::write(uint16_t devAddress, uint8_t *data, uint16_t size) {
//    return HAL_I2C_Master_Transmit(&hi2c, devAddress << 1 | 0x00, data, size, HAL_MAX_DELAY);//LSB = 0x00 car on veux write
//}
//
//HAL_StatusTypeDef I2CHandler::read(uint16_t devAddress, uint8_t *data, uint16_t size) {
//    return HAL_I2C_Master_Receive(&hi2c, devAddress << 1 | 0x01, data, size, HAL_MAX_DELAY);//LSB = 0x01 car on veux read
//}

/* Voici les 4 fonctions que nous allons utiliser pour le I2C */
// HAL_I2C_Master_Transmit(&hi2c, devAddress << 1, data, size, HAL_MAX_DELAY);
// HAL_I2C_Master_Receive(&hi2c, devAddress << 1, data, size, HAL_MAX_DELAY);
// HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout)
// HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout)

/* Description des fonctions */
// HAL_I2C_Master_Transmit : Fonction qu'on utilise quand on veux write du data. On l'utilise de cette manière:



// HAL_I2C_Master_Receive :Fonction pour read la merde
// HAL_I2C_Mem_Write :
// HAL_I2C_Mem_Read :
