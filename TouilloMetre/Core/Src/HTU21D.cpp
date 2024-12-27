/*
 * HTU21D.cpp
 *
 *  Created on: Nov. 18, 2024
 *      Author: victorx1
 */

#include "HTU21D.h"
#include <stdio.h>
#include <stdlib.h>

static const uint8_t HTU21D_DELAY_T[] = {50, 13, 25, 7};
static const uint8_t HTU21D_DELAY_H[] = {16, 3, 5, 8};
static const float HTU21D_TCoeff = -0.15;
const float temperatureFactor = 175.72 / 65536.0;
const float humidityFactor = 125.0 / 65536.0;

HTU21D::HTU21D(uint8_t addr, I2CHandler& i2cHandler) : _addr(addr), _i2cHandler(i2cHandler), _resolution(RESOLUTION_RH12_T14), _name("HTU21D")  {
}

/*************************************************************************************************************************/
bool HTU21D::checkCRC8(uint8_t data[]) {
  uint8_t crc = 0;
  for(int i = 0; i < 2; i++) {
    crc ^= data[i];
    for(int b = 7; b >= 0; b--) {
      if(crc & 0x80) crc = (crc << 1) ^ 0x31;
      else crc = (crc << 1);
    }
  }

  return crc == data[2];
}

/*************************************************************************************************************************/
float HTU21D::constrain(float number_tested, float min_tolerance , float max_tolerance){
	if(number_tested < min_tolerance){
		return min_tolerance;
	}
	if(number_tested > max_tolerance){
		return max_tolerance;
	}
	return number_tested;

}

/*************************************************************************************************************************/
bool HTU21D::measureTemperature() {
	uint8_t cmd = TRIGGER_TEMP_MEAS_NH; // Commande pour lancer une mesure de température

	// Envoyer la commande de mesure de température
	if (_i2cHandler.write(_addr, &cmd, 1) != HAL_OK) {
		return false; // Échec d'écriture
	}

	// Attente en fonction de la résolution configurée
	HAL_Delay(HTU21D_DELAY_T[_resolution]);

	// Lecture des 3 octets de données (MSB, LSB, CRC)
	uint8_t data[3] = {0,0,0};
	if (_i2cHandler.read(_addr, data, 3) != HAL_OK) {
		return false; // Échec de lecture
	}

	// Vérification du CRC
	if (!checkCRC8(data)) {
		return false; // CRC invalide
	}

	// Conversion des données pour obtenir la température
	uint16_t St = (data[0] << 8) | (data[1] & 0xFC);
	temperature = -46.85 +  temperatureFactor * St;

	return true; // Mesure réussie
}

/*************************************************************************************************************************/
bool HTU21D::measureHumidity() {
	uint8_t command = TRIGGER_HUM_MEAS_NH;
	if(_i2cHandler.write(_addr, &command, 1) != HAL_OK){
		return false;
	}

	HAL_Delay(HTU21D_DELAY_H[_resolution]);

	uint8_t data[3] = {0,0,0};
	if (_i2cHandler.read(_addr, data, 3) != HAL_OK) {
		return false; // Échec de lecture
	}

	if(!checkCRC8(data)){
		return false;
	}
	uint16_t Srh = (data[0] << 8) | (data[1] & 0xFC);
	humidity = -6.0 + humidityFactor * Srh;
	humidity += (25.0 - temperature) * HTU21D_TCoeff;
	humidity = constrain(humidity, 0.0, 100.0);

	return true;
}

/*************************************************************************************************************************/
bool HTU21D::measure() {
  temperature = 0.0F;
  humidity = 0.0F;

  /* NOTE: Order is important as the temperature is needed to correct the humidity reading */
  if(!measureTemperature()) return false;
  if(!measureHumidity()) return false;
  return true;
}

/*************************************************************************************************************************/
bool HTU21D::setResolution(HTU21DResolution resolution) {
	uint8_t data[2] = {0,0};
	data[0] = WRITE_USER_REG;
	data[1] = (resolution & 0x01) | ((resolution & 0x02) << 6) | 0x02;
	if(_i2cHandler.write(_addr, data, 2) != HAL_OK){
		return false;
	}
	_resolution = resolution;
	return true;
}

/*************************************************************************************************************************/
HTU21DResolution HTU21D::getResolution() {
  return _resolution;
}

/*************************************************************************************************************************/
bool HTU21D::begin() {
  return reset();
}

/*************************************************************************************************************************/
bool HTU21D::reset() {
	uint8_t softResetCmd = SOFT_RESET;
	if (_i2cHandler.write(_addr, &softResetCmd, 1) != HAL_OK) {
		return false;// can't I2C write
	}

	//wait 15ms before sending command
	HAL_Delay(15);

	//check if the soft reset was properly execute
	uint8_t readUserRegCmd = READ_USER_REG;
	if (_i2cHandler.write(_addr, &readUserRegCmd, 1) != HAL_OK) {
		return false; // can't I2C write
	}
	//read the user register (to compare with the logical value that the soft reset did make)
	uint8_t userRegValue;
	if (_i2cHandler.read(_addr, &userRegValue, 1) != HAL_OK) {
		return false; // Échec de lecture du registre utilisateur
	}

	// compare the value of the user register
	if (userRegValue != 0x02) {
		return false;
	}

	//the soft reset put the default value of resolution which is 12 bits for Relative Humidity ant 14 for Temperature
	_resolution = RESOLUTION_RH12_T14;

	return true;
}

/*************************************************************************************************************************/
float HTU21D::getTemperature() const {
	return temperature;
}

/*************************************************************************************************************************/
float HTU21D::getHumidity() const {
  return humidity;
}

/*************************************************************************************************************************/
uint8_t HTU21D::readUserRegister(){
	uint8_t readUserRegCmd = READ_USER_REG;
	if (_i2cHandler.write(_addr, &readUserRegCmd, 1) != HAL_OK) {
		return 0x00; // can't I2C write
	}
	//read the user register (to compare with the logical value that the soft reset did make)
	uint8_t userRegValue;
	if (_i2cHandler.read(_addr, &userRegValue, 1) != HAL_OK) {
		return 0x00; // Échec de lecture du registre utilisateur
	}
	return userRegValue;
}

/*************************************************************************************************************************/
const char* HTU21D::getFormattedMeasurement(){//Longueur la plus LONGUE: 53, longueur la plus COURTE: 48
	if(measure()){
		int humidity_int = (int)(humidity);                  // Partie entière de l'humidité
		int humidity_frac =  (int)(abs((humidity - humidity_int) * 100));// Partie fractionnaire de l'humidité
		int temperature_int =  (int)(temperature);            // Partie entière de la température
		int temperature_frac =  (int)(abs((temperature - temperature_int) * 100)); // Partie fractionnaire de la température

		snprintf(_formattedBuffer, sizeof(_formattedBuffer), "H= %d.%02d%%, T= %d.%02dC", humidity_int, humidity_frac, temperature_int, temperature_frac);
	}

	return _formattedBuffer;
	/*Note personnel sur le formatage de la string*/
	//1. On sépare la partie réelle de la partie décimal
	//2. On affiche le nom du sensor avec (%s)
	//3. On affiche la valeur de l'humidité réelle (%d)
	//4. On affiche un '.' puis on affiche avec 2 chiffre décimal en mettant des zeros padding devant si celui-ci est plus petit que 2 décimal (ex 5 = 05, 11 = 11)
	//5. On répète la même oppération pour la température

}

/*************************************************************************************************************************/
const char* HTU21D::getSensorName(){
	return _name;
}


//#include <stdio.h>
//#include <iostream>
//#include <string.h>
//const char* _name = "HTU21D";
//char _formattedBuffer[100];
//float _humidity = -144.58;
//float _temperature = 22.35;
//const char* getFormattedMeasurement(){
//	int humidity_int = (int)(_humidity);                  // Partie entière de l'humidité
//	int humidity_frac =  (int)(abs((_humidity - humidity_int) * 100));// Partie fractionnaire de l'humidité
//	int temperature_int =  (int)(_temperature);            // Partie entière de la température
//	int temperature_frac =  (int)(abs((_temperature - temperature_int) * 100)); // Partie fractionnaire de la température
//
//	snprintf(_formattedBuffer, sizeof(_formattedBuffer),
//			 "%s - Humidity: %d.%02d%%, Temperature: %d.%02d°C",
//			 _name,
//			 humidity_int, humidity_frac,
//			 temperature_int, temperature_frac);
//
//	return _formattedBuffer;
//}
//
//int main()
//{
//    const char* str = getFormattedMeasurement();
//    int size = strlen(str);
//    printf("size of formattedBuffer: %d\n", size );
//    printf("%s", getFormattedMeasurement());
//
//    return 0;
//}

