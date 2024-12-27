/*
 * HTU21D.h
 *
 *  Created on: Nov. 18, 2024
 *      Author: victorx1
 */
/*+ gros que 22 char sa crap */
#ifndef SRC_HTU21D_H_
#define SRC_HTU21D_H_

#include "ISensor.h"
#include "I2CHandler.h"

enum HTU21DResolution {
  RESOLUTION_RH12_T14 = 0, //!< 12 bit for RH and 14 bit for temperature
  RESOLUTION_RH8_T12 = 1,  //!< 8 bit for RH and 12 bit for temperature
  RESOLUTION_RH10_T13 = 2, //!< 10 bit for RH and 13 bit for temperature
  RESOLUTION_RH11_T11 = 3  //!< 11 bit for RH and 11 bit for temperature
};

/**
 * HTU21D Sensor Driver
 */
class HTU21D: public ISensor {
private:
  static const uint8_t HTU21D_ADDR = 0x40;

  const uint8_t _addr;
  I2CHandler& _i2cHandler;
  HTU21DResolution _resolution;

  float temperature;
  float humidity;
  const char* _name;
  char _formattedBuffer[100];

  /* Hold master vs No Hold master */
  //Hold master: Force le master (MCU) a attendre que les données soit prête.
  //Cela est fait en tirant la ligne SCK en bas jusqu'à ce qu'elle soit remise a haut (pour signifier que les données sont prête)
  //No Hold master: permet a d'autre communication I2C d'être effectuté sur le bus pendant que les données sont mesuré.
  //On envoie la commande et on peux revenir vérifier plus tard la valeur que cela nous a donnée de température sens blocker la ligne I2C
  enum HTU21DCmd {
    TRIGGER_TEMP_MEAS_H = 0xE3,//Hold master
    TRIGGER_HUM_MEAS_H = 0xE5,//Hold master
    TRIGGER_TEMP_MEAS_NH = 0xF3,//No Hold master
    TRIGGER_HUM_MEAS_NH = 0xF5,//No Hold master
    WRITE_USER_REG = 0xE6,
    READ_USER_REG = 0xE7,
    SOFT_RESET = 0xFE
  };



  bool checkCRC8(uint8_t data[]);
  float constrain(float number_tested, float min_tolerance, float max_tolerance);
  bool measureHumidity();//a remettre privé après
  bool measureTemperature();//a remettre privé après
public:
  HTU21D(uint8_t addr, I2CHandler& i2cHandler);

  bool measure();
  float getTemperature(void) const;
  float getHumidity(void) const;
  bool setResolution(HTU21DResolution resolution);
  HTU21DResolution getResolution(void);
  bool reset(void);
  bool begin(void);
  uint8_t readUserRegister();

  /*------------- ISensor -------------*/
  const char* getFormattedMeasurement();//Longueur la plus LONGUE: 53, longueur la plus COURTE: 48
  const char* getSensorName();


};

#endif /* SRC_HTU21D_H_ */
