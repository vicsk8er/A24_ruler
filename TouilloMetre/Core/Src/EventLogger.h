/*
 * EventLogger.h
 *
 *  Created on: Dec 21, 2024
 *      Author: victorx1
 */

#ifndef SRC_EVENTLOGGER_H_
#define SRC_EVENTLOGGER_H_
#include "ISensor.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


enum currentSensor{
	HTU21D_s,
	VL53L0X_s,
	LTR_303ALS_s,
	ADXL343_s,
	MULTIMETRE_s,
	NONE,
};
class EventLogger {
private:
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT fres; //Result after operations
	/********************** Card capacity details **********************/
	FATFS *pfs;
	DWORD fre_clust;
	uint32_t total, free_space;
	/*******************************************************************/

	static const int maxSensor = 5;
	int logCurrentNumber[maxSensor];
	int sensorCount;
	ISensor* sensors[maxSensor];
	currentSensor _sensor;
	bool logHTU21DEvent();//Temperature/humidity sensor
	bool logVL53L0XEvent();//ToF Distance sensor
	bool logLTR_303ALSEvent();//LUX sensor
	bool logADXL343Event();//accéléromètre
	bool logMultimetreEvent();


public:
	EventLogger();
	void addSensor(ISensor* p_sensor);//Les sensors doivent être ajouté dans l'ordre de l'enum currentSensor
	bool mountLogger();
	bool unmountLogger();
	bool updateLoggerSpec();
	uint32_t getLoggerTotalSpace();
	uint32_t getLoggerFreeSpace();
	void setCurrentSensor(currentSensor CurrentSensor);
	bool logEvent();//pourrait être un bool
};

#endif /* SRC_EVENTLOGGER_H_ */

//a chaque fois qu'on rentre dans un menu, on va set le current senor
