/*
 * LTR303ALS.cpp
 *
 *  Created on: Dec 27, 2024
 *      Author: victorx1
 */

#include "LTR303ALS.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
LTR303ALS::LTR303ALS(uint8_t addr, I2CHandler& i2cHandler): _addr(addr), _i2cHandler(i2cHandler), _name("LTR303ALS"){

}

bool LTR303ALS::begin(){
	//return setPowerUp();

	if(setControl(0, false, false)){
		if(setMeasurementRate(1,1)){
			if(setPowerUp()){
				return true;
			}
		}
		return false;

	}
	return false;



}

bool LTR303ALS::setPowerUp(){
	uint8_t data[2] = {0,0};
	data[0] = LTR303_CONTR;
	data[1] = 0x03;
	if(_i2cHandler.write(_addr,data , sizeof(data)) != HAL_OK ){
		return false;
	}
	return true;
}
bool LTR303ALS::setPowerDown(){
	uint8_t data[2] = {0,0};
	data[0] = LTR303_CONTR;
	data[1] = 0x00;
	if(_i2cHandler.write(_addr,data , sizeof(data)) != HAL_OK ){
		return false;
	}
	return true;

}
bool LTR303ALS::setControl(uint8_t gain = 0x00, bool reset = false, bool mode = false){//mettre reset et mode a false par défaut
	// Valeur par défaut : 0x00
	// Si gain = 0, le gain est réglé à 1X (valeur par défaut)
	// Si gain = 1, le gain est réglé à 2X
	// Si gain = 2, le gain est réglé à 4X
	// Si gain = 3, le gain est réglé à 8X
	// Si gain = 4, invalide
	// Si gain = 5, invalide
	// Si gain = 6, le gain est réglé à 48X
	// Si gain = 7, le gain est réglé à 96X
	//----------------------------------------
	// Si reset = false (0), la procédure de démarrage initiale n'est pas lancée (valeur par défaut)
	// Si reset = true (1), la procédure de démarrage initiale est lancée
	//----------------------------------------
	// Si mode = false (0), mode veille (par défaut)
	// Si mode = true (1), mode actif

	uint8_t control = 0x00;  // Valeur par défaut

	if (gain > 3 && gain < 6) {
		gain = 0x00;  // Si gain est entre 4 et 5, je le met à 0 (1X)
	}
	else if (gain >= 7) {
		gain = 0x00;  // Si gain >= 7, je le met à 0 (1X)
	}

	control |= (gain << 2);
	if (reset) {
		control |= 0x02;  // Si reset est vrai, j'active le bit de reset
	}

	if (mode) {
		control |= 0x01;  // Si mode est vrai, j'active le bit de mode actif
	}

	uint8_t data[2] = {LTR303_CONTR, control};

	if (_i2cHandler.write(_addr, data, sizeof(data)) != HAL_OK) {
		return false;
	}

	return true;

}
bool LTR303ALS::getControl(uint8_t* gain, bool reset, bool mode){
	uint8_t command = LTR303_CONTR;
	if (_i2cHandler.write(_addr, &command, 1) != HAL_OK) {
		return false;
	}
	uint8_t controlRegister;
	if (_i2cHandler.read(_addr, &controlRegister, 1) != HAL_OK) {
		return false;
	}
	*gain = (controlRegister & 0x1C) >> 2;

	if (controlRegister & 0x02) {
	    reset = true;
	}
	else {
	    reset = false;
	}

	if (controlRegister & 0x01) {
	    mode = true;
	}
	else {
	    mode = false;
	}

	return true;

}
bool LTR303ALS::setMeasurementRate(uint8_t integrationTime, uint8_t measurementRate){
	// Définit le temps d'intégration et le taux de mesure du capteur
	// integrationTime est le temps de mesure pour chaque cycle ALS
	// measurementRate est l'intervalle entre les mises à jour des DATA_REGISTERS
	// measurementRate doit être égal ou supérieur à integrationTime
	// La valeur par défaut est 0x03
	// Si integrationTime = 0, integrationTime sera de 100ms (valeur par défaut)
	// Si integrationTime = 1, integrationTime sera de 50ms
	// Si integrationTime = 2, integrationTime sera de 200ms
	// Si integrationTime = 3, integrationTime sera de 400ms
	// Si integrationTime = 4, integrationTime sera de 150ms
	// Si integrationTime = 5, integrationTime sera de 250ms
	// Si integrationTime = 6, integrationTime sera de 300ms
	// Si integrationTime = 7, integrationTime sera de 350ms
	//------------------------------------------------------
	// Si measurementRate = 0, measurementRate sera de 50ms
	// Si measurementRate = 1, measurementRate sera de 100ms
	// Si measurementRate = 2, measurementRate sera de 200ms
	// Si measurementRate = 3, measurementRate sera de 500ms (valeur par défaut)
	// Si measurementRate = 4, measurementRate sera de 1000ms
	// Si measurementRate = 5, measurementRate sera de 2000ms
	// Si measurementRate = 6, measurementRate sera de 2000ms
	// Si measurementRate = 7, measurementRate sera de 2000ms
	uint8_t measurement = 0x00;

	if (integrationTime >= 0x07) {
		integrationTime = 0x00;
	}

	if (measurementRate >= 0x07) {
		measurementRate = 0x00;
	}

	// Combine les valeurs dans le byte 'measurement'
	measurement |= integrationTime << 3;
	measurement |= measurementRate;

	uint8_t data[2] = {0, 0};
	data[0] = LTR303_MEAS_RATE;
	data[1] = measurement;

	if (_i2cHandler.write(_addr, data, sizeof(data)) != HAL_OK) {
		return false;
	}

	return true;
}
bool LTR303ALS::getMeasurementRate(uint8_t* integrationTime, uint8_t* measurementRate){
	uint8_t command = LTR303_MEAS_RATE;
	if (_i2cHandler.write(_addr, &command, 1) != HAL_OK) {
		return false;
	}
	uint8_t measureRegister;
	if (_i2cHandler.read(_addr, &measureRegister, 1) != HAL_OK) {
		return false;
	}
	*integrationTime = (measureRegister & 0x38) >> 3;

	*measurementRate = measureRegister & 0x07;

}
bool LTR303ALS::getData(uint16_t* CH0, uint16_t* CH1){
	uint8_t data[2];

	data[0] = LTR303_DATA_CH0_0;
	if (_i2cHandler.write(_addr, data, 1) != HAL_OK) {
		return false;
	}

	if (_i2cHandler.read(_addr, data, 2) != HAL_OK) {
		return false;
	}
	*CH0 = (data[0] << 8) | data[1];  //on combine les 2 octets du CH0 en 1 seule valeur



	data[0] = LTR303_DATA_CH1_0;
	if (_i2cHandler.write(_addr, data, 1) != HAL_OK) {
		return false;
	}

	if (_i2cHandler.read(_addr, data, 2) != HAL_OK) {
		return false;
	}
	*CH1 = (data[0] << 8) | data[1];   //on combine les 2 octets du CH1 en 1 seule valeur

	return true;
}
bool LTR303ALS::getLux(uint8_t gain, uint8_t integrationTime, unsigned int CH0, unsigned int CH1, double* lux){
	//vérifier si un des 2 capteurs a saturé
	if ((CH0 == 0xFFFF) || (CH1 == 0xFFFF)) {
		*lux = 0.0;
		return false;
	}

	double d0 = (double)CH0;
	double d1 = (double)CH1;

	// Calcul du ratio
	double ratio = d1 / d0;

	// Normaliser selon le temps d'intégration
	d0 *= (402.0 / integrationTime);
	d1 *= (402.0 / integrationTime);

	// Normaliser selon le gain
	if (gain == 0) {
		d0 *= 16;
		d1 *= 16;
	}

	// Calcul de lux selon les équations du datasheet
	if (ratio < 0.5) {
		*lux = 0.0304 * d0 - 0.062 * d0 * pow(ratio, 1.4);
		return true;
	}

	if (ratio < 0.61) {
		*lux = 0.0224 * d0 - 0.031 * d1;
		return true;
	}

	if (ratio < 0.80) {
		*lux = 0.0128 * d0 - 0.0153 * d1;
		return true;
	}

	if (ratio < 1.30) {
		*lux = 0.00146 * d0 - 0.00112 * d1;
		return true;
	}

	// Si le ratio est supérieur à 1.30, retourner lux = 0.0
	*lux = 0.0;
	return true;
}

const char* LTR303ALS::getFormattedMeasurement(){

	uint16_t data0, data1;
	double lux;

	if (getData(&data0,&data1)) {
		if(getLux(0,1,data0,data1, &lux)){
			snprintf(_formattedBuffer, sizeof(_formattedBuffer), "LUX= %d", (int)lux);
		}
	}


	return _formattedBuffer;
}
const char* LTR303ALS::getSensorName(){
	return _name;
}
