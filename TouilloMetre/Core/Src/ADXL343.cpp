/*
 * ADXL343.cpp
 *
 *  Created on: Dec 27, 2024
 *      Author: victorx1
 */

#include "ADXL343.h"
#include <stdio.h>
#include <stdlib.h>

ADXL343::ADXL343(uint8_t addr, I2CHandler& i2cHandler) : _addr(addr), _i2cHandler(i2cHandler), _name("ADXL343"){

}

bool ADXL343::begin(){

	uint8_t readDeviceIDCmd = ADXL3XX_REG_DEVID;
	if (_i2cHandler.write(_addr, &readDeviceIDCmd, 1) != HAL_OK) {
		return false; // can't I2C write
	}
	 uint8_t device_id;
	// on va lire le registre du device ID pour valider qu'il est connecté
	if (_i2cHandler.read(_addr, &device_id, 1) != HAL_OK || device_id != 0xE5) {
		return false;
	}

	_range = ADXL343_RANGE_2_G;

	uint8_t data[2] = {0,0};
	data[0] = ADXL3XX_REG_INT_ENABLE;
	data[1] = 0;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	data[0] = ADXL3XX_REG_THRESH_TAP;
	data[1] = 20;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	data[0] = ADXL3XX_REG_DUR;
	data[1] = 50;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	data[0] = ADXL3XX_REG_LATENT;
	data[1] = 0;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	data[0] = ADXL3XX_REG_WINDOW;
	data[1] = 0;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	data[0] = ADXL3XX_REG_TAP_AXES;
	data[1] = 0x7;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	data[0] = ADXL3XX_REG_POWER_CTL;
	data[1] = 0x08;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){return false;}

	return true;
}

void ADXL343::setRange(adxl343_range_t range){

	uint8_t format;

	uint8_t readRegDataFormatCmd = ADXL3XX_REG_DATA_FORMAT;
	if (_i2cHandler.write(_addr, &readRegDataFormatCmd, 1) != HAL_OK) {
		return; // can't I2C write
	}
	// Lire le registre DATA_FORMAT
	if (_i2cHandler.read(_addr, &format, 1) != HAL_OK) {
		return;
	}

	// Modifier les bits du range (bits 0 et 1)
	format &= ~0x03;
	format |= (range & 0x03);

	// Activer le bit FULL_RES (bit 3)
	format |= 0x08;

	uint8_t data[2] = {0,0};
	data[0] = ADXL3XX_REG_DATA_FORMAT;
	data[1] = format;
	// Écrire le registre modifié
	if (_i2cHandler.write(_addr,data, 2) != HAL_OK) {
		return;
	}
	_range = range;

}

adxl343_range_t ADXL343::getRange(void) {
    uint8_t regValue = 0;
    uint8_t readCmd = ADXL3XX_REG_DATA_FORMAT;

    // Envoyer la commande pour lire le bhay
    if (_i2cHandler.write(_addr, &readCmd, 1) != HAL_OK) {
        return (adxl343_range_t)0xFF;
    }

    // Lire le bhay
    if (_i2cHandler.read(_addr, &regValue, 1) != HAL_OK) {
        return (adxl343_range_t)0xFF;
    }

    // Extraire les bits 0 et 1 pour obtenir la plage
    regValue &= 0x03;

    return (adxl343_range_t)regValue;
}

void ADXL343::setDataRate(adxl343_dataRate_t dataRate){
    uint8_t data[2] = {ADXL3XX_REG_BW_RATE, (uint8_t)dataRate};

    if (_i2cHandler.write(_addr, data, 2) != HAL_OK) {
        return;
    }
}

adxl343_dataRate_t ADXL343::getDataRate(void) {
    uint8_t regValue = 0;
    uint8_t readCmd = ADXL3XX_REG_BW_RATE;

    // Lire le registre BW_RATE
    if (_i2cHandler.write(_addr, &readCmd, 1) != HAL_OK) {
        return  (adxl343_dataRate_t)0xFF;
    }

    if (_i2cHandler.read(_addr, &regValue, 1) != HAL_OK) {
        return (adxl343_dataRate_t)0xFF;
    }

    // Extraire les 4 bits de poids faible (truss)
    regValue &= 0x0F;

    return (adxl343_dataRate_t)regValue;
}


void ADXL343::getTrimOffsets(int8_t *x, int8_t *y, int8_t *z) {
    uint8_t regValue = 0;

    // Lire l'offset X
    if (x != NULL) {
        uint8_t readCmd = ADXL3XX_REG_OFSX;
        if (_i2cHandler.write(_addr, &readCmd, 1) == HAL_OK &&
            _i2cHandler.read(_addr, &regValue, 1) == HAL_OK) {
            *x = (int8_t)regValue;
        }
    }

    // Lire l'offset Y
    if (y != NULL) {
        uint8_t readCmd = ADXL3XX_REG_OFSY;
        if (_i2cHandler.write(_addr, &readCmd, 1) == HAL_OK &&
            _i2cHandler.read(_addr, &regValue, 1) == HAL_OK) {
            *y = (int8_t)regValue;
        }
    }

    // Lire l'offset Z
    if (z != NULL) {
        uint8_t readCmd = ADXL3XX_REG_OFSZ;
        if (_i2cHandler.write(_addr, &readCmd, 1) == HAL_OK &&
            _i2cHandler.read(_addr, &regValue, 1) == HAL_OK) {
            *z = (int8_t)regValue;
        }
    }
}

void ADXL343::setTrimOffsets(int8_t x, int8_t y, int8_t z) {
    uint8_t data[2] = {0, 0};

    // Écrire l'offset X
    data[0] = ADXL3XX_REG_OFSX;
    data[1] = (uint8_t)x;
    if (_i2cHandler.write(_addr, data, 2) != HAL_OK) {
        return; // Erreur lors de l'écriture
    }

    // Écrire l'offset Y
    data[0] = ADXL3XX_REG_OFSY;
    data[1] = (uint8_t)y;
    if (_i2cHandler.write(_addr, data, 2) != HAL_OK) {
        return; // Erreur lors de l'écriture
    }

    // Écrire l'offset Z
    data[0] = ADXL3XX_REG_OFSZ;
    data[1] = (uint8_t)z;
    if (_i2cHandler.write(_addr, data, 2) != HAL_OK) {
        return; // Erreur lors de l'écriture
    }
}


bool ADXL343::readAcceleration(int16_t *x, int16_t *y, int16_t *z){
	uint8_t readAccelerationCmd = ADXL3XX_REG_DATAX0;
	if (_i2cHandler.write(_addr, &readAccelerationCmd, 1) != HAL_OK) {
		return false;
	}


	 uint8_t buffer[6]; // Buffer pour lire les 6 octets des registres X, Y, Z

	 if(_i2cHandler.read(_addr, buffer, 6) != HAL_OK){
		 return false;
	 }

	x = (int16_t*)((buffer[1] << 8) | buffer[0]);
	y = (int16_t*)((buffer[3] << 8) | buffer[2]);
	z = (int16_t*)((buffer[5] << 8) | buffer[4]);
	return true;


}

const char* ADXL343::getFormattedMeasurement(){
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;
	if(readAcceleration(&x, &y, &z)){
		snprintf(_formattedBuffer, sizeof(_formattedBuffer), "X= %d, Y= %d, Z= %d", x, y, z);
	}

	return _formattedBuffer;

}
const char* ADXL343::getSensorName(){
	return _name;

}
