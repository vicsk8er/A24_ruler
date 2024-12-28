/*
 * LTR303ALS.h
 *
 *  Created on: Dec 27, 2024
 *      Author: victorx1
 */

#ifndef SRC_LTR303ALS_H_
#define SRC_LTR303ALS_H_
#include "ISensor.h"
#include "I2CHandler.h"


// LTR303 registre I2C
#define LTR303_CONTR         0x80
#define LTR303_MEAS_RATE     0x85
#define LTR303_PART_ID       0x86
#define LTR303_MANUFAC_ID    0x87
#define LTR303_DATA_CH1_0    0x88
#define LTR303_DATA_CH1_1    0x89
#define LTR303_DATA_CH0_0    0x8A
#define LTR303_DATA_CH0_1    0x8B
#define LTR303_STATUS		 0x8C
#define LTR303_INTERRUPT     0x8F
#define LTR303_THRES_UP_0    0x97
#define LTR303_THRES_UP_1	 0x98
#define LTR303_THRES_LOW_0   0x99
#define LTR303_THRES_LOW_1   0x9A
#define LTR303_INTR_PERS     0x9E
class LTR303ALS : public ISensor{
private:
	static const uint8_t LTR_303ALS_s = 0x29;

	const uint8_t _addr;
	I2CHandler& _i2cHandler;

	const char* _name;
	char _formattedBuffer[40];
public:
	LTR303ALS(uint8_t addr, I2CHandler& i2cHandler);

	bool begin();
	bool setPowerUp();
	bool setPowerDown();
	bool setControl(uint8_t gain, bool reset, bool mode);
	bool getControl(uint8_t* gain, bool reset, bool mode);
	bool setMeasurementRate(uint8_t integrationTime, uint8_t measurementRate);
	bool getMeasurementRate(uint8_t* integrationTime, uint8_t* measurementRate);
	bool getData(uint16_t* CH0, uint16_t* CH1);
	bool getLux(uint8_t gain, uint8_t integrationTime, unsigned int CH0, unsigned int CH1, double* lux);
  /*------------- ISensor -------------*/
	const char* getFormattedMeasurement();
	const char* getSensorName();

};

#endif /* SRC_LTR303ALS_H_ */
