/*
 * ISensor.h
 *
 *  Created on: Dec 22, 2024
 *      Author: victorx1
 */

#ifndef SRC_ISENSOR_H_
#define SRC_ISENSOR_H_

class ISensor {
public:
	virtual const char* getFormattedMeasurement() = 0;
	virtual const char* getSensorName() = 0;
};

#endif /* SRC_ISENSOR_H_ */
