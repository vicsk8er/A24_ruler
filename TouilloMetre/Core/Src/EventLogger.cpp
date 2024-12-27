/*
 * EventLogger.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: victorx1
 */

#include "EventLogger.h"

EventLogger::EventLogger() {
	if(mountLogger()){
		updateLoggerSpec();
	}
	for(int i = 0; i < maxSensor; i++){
		logCurrentNumber[i] = -1;
	}
	sensorCount = 0;
	_sensor = NONE;
}

/*************************************************************************************************************************/
void EventLogger::addSensor(ISensor* p_sensor){//Les sensors doivent être ajouté dans l'ordre de l'enum currentSensor
	sensors[sensorCount] = p_sensor;
	sensorCount++;
}

/*************************************************************************************************************************/
bool EventLogger::logHTU21DEvent(){//Temperature/humidity sensor
	if (sensors[HTU21D_s] == nullptr) {
		return false;// Pas de capteur HTU21D trouvé
	}
	const char* sensorName = sensors[HTU21D_s]->getSensorName();
	const char* measurement = sensors[HTU21D_s]->getFormattedMeasurement();

	int logNumber = 0; // Par défaut, premier log
	char lineBuffer[64]; // Buffer pour lire les lignes du fichier
	char logMessage[64]; // Buffer pour écrire le nouveau log

	if(logCurrentNumber[HTU21D_s] == -1){//On sait que le programme vient juste de redémaré
		if (f_open(&fil, "HTU21D.txt", FA_READ | FA_OPEN_EXISTING) == FR_OK) {
			while (f_gets(lineBuffer, sizeof(lineBuffer), &fil)) {
				// Trouver le numéro du dernier log (ligne du type "LOGX:")
				if (strncmp(lineBuffer, "LOG", 3) == 0) {
					int tempLogNumber = atoi(lineBuffer + 3); // Convertir le numéro de log.
					//Le '+ 3' permet a atoi de pointer le premier chiffre du log et il va lire les prochain char tant et aussi longtemps qu'il sont compris entre '0' et '9' pis convertir cela en string
					if (tempLogNumber > logNumber) {
						logNumber = tempLogNumber; // Garder le plus grand numéro
					}
				}
			}
			f_close(&fil);

		}
	}
	logNumber++; // Incrémenter le numéro de log pour le prochain
	if (f_open(&fil, "HTU21D.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK) {
		// Construire la nouvelle ligne de log
		snprintf(logMessage, sizeof(logMessage), "LOG%d: %s - %s\n", logNumber, sensorName, measurement);

		// Écrire la ligne dans le fichier de log
		UINT bytesWritten;
		if (f_write(&fil, logMessage, strlen(logMessage), &bytesWritten) != FR_OK || bytesWritten != strlen(logMessage)){
			f_close(&fil);
			return false; // Erreur d'écriture
		}
		//sync le tampon
		f_sync(&fil);
		f_close(&fil);
		return true;
	}
	return false;


}

/*************************************************************************************************************************/
bool EventLogger::logVL53L0XEvent(){//ToF Distance sensor
	if (sensors[VL53L0X_s] == nullptr) {
		return false;// Pas de capteur trouvé
	}
	const char* sensorName = sensors[HTU21D_s]->getSensorName();
	const char* measurement = sensors[VL53L0X_s]->getFormattedMeasurement();//Longueur la plus LONGUE: 53, longueur la plus COURTE: 48

	int logNumber = 0; // Par défaut, premier log
	char lineBuffer[64]; // Buffer pour lire les lignes du fichier
	char logMessage[64]; // Buffer pour écrire le nouveau log

	if(logCurrentNumber[VL53L0X_s] == -1){//On sait que le programme vient juste de redémaré
		if (f_open(&fil, "VL53L0X.txt", FA_READ | FA_OPEN_EXISTING) == FR_OK) {
			while (f_gets(lineBuffer, sizeof(lineBuffer), &fil)) {
				// Trouver le numéro du dernier log (ligne du type "LOGX:")
				if (strncmp(lineBuffer, "LOG", 3) == 0) {
					int tempLogNumber = atoi(lineBuffer + 3); // Convertir le numéro de log.
					//Le '+ 3' permet a atoi de pointer le premier chiffre du log et il va lire les prochain char tant et aussi longtemps qu'il sont compris entre '0' et '9' pis convertir cela en string
					if (tempLogNumber > logNumber) {
						logNumber = tempLogNumber; // Garder le plus grand numéro
					}
				}
			}
			f_close(&fil);

		}
	}
	logNumber++; // Incrémenter le numéro de log pour le prochain
	if (f_open(&fil, "VL53L0X.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK) {
		// Construire la nouvelle ligne de log
		snprintf(logMessage, sizeof(logMessage), "LOG%d: %s - %s\n", logNumber, sensorName, measurement);

		// Écrire la ligne dans le fichier
		UINT bytesWritten;
		if (f_write(&fil, logMessage, strlen(logMessage), &bytesWritten) != FR_OK || bytesWritten != strlen(logMessage)){
			f_close(&fil);
			return false; // Erreur d'écriture
		}

		// Synchroniser les tampons
		f_sync(&fil);
		f_close(&fil);
		return true; // Écriture réussie
	}
	return false;
}

/*************************************************************************************************************************/
bool EventLogger::logLTR_303ALSEvent(){//LUX sensor
	if (sensors[LTR_303ALS_s] == nullptr) {
		return false;// Pas de capteur trouvé
	}
	const char* sensorName = sensors[HTU21D_s]->getSensorName();
	const char* measurement = sensors[LTR_303ALS_s]->getFormattedMeasurement();//Longueur la plus LONGUE: 53, longueur la plus COURTE: 48

	int logNumber = 0; // Par défaut, premier log
	char lineBuffer[64]; // Buffer pour lire les lignes du fichier
	char logMessage[64]; // Buffer pour écrire le nouveau log

	if(logCurrentNumber[LTR_303ALS_s] == -1){//On sait que le programme vient juste de redémaré
		if (f_open(&fil, "LTR-303ALS.txt", FA_READ | FA_OPEN_EXISTING) == FR_OK) {
			while (f_gets(lineBuffer, sizeof(lineBuffer), &fil)) {
				// Trouver le numéro du dernier log (ligne du type "LOGX:")
				if (strncmp(lineBuffer, "LOG", 3) == 0) {
					int tempLogNumber = atoi(lineBuffer + 3); // Convertir le numéro de log.
					//Le '+ 3' permet a atoi de pointer le premier chiffre du log et il va lire les prochain char tant et aussi longtemps qu'il sont compris entre '0' et '9' pis convertir cela en string
					if (tempLogNumber > logNumber) {
						logNumber = tempLogNumber; // Garder le plus grand numéro
					}
				}
			}
			f_close(&fil);

		}
	}
	logNumber++; // Incrémenter le numéro de log pour le prochain
	if (f_open(&fil, "LTR-303ALS.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK) {
		// Construire la nouvelle ligne de log
		snprintf(logMessage, sizeof(logMessage), "LOG%d: %s - %s\n", logNumber, sensorName, measurement);

		// Écrire la ligne dans le fichier
		UINT bytesWritten;
		if (f_write(&fil, logMessage, strlen(logMessage), &bytesWritten) != FR_OK || bytesWritten != strlen(logMessage)){
			f_close(&fil);
			return false; // Erreur d'écriture
		}

		// Synchroniser les tampons
		f_sync(&fil);
		f_close(&fil);
		return true; // Écriture réussie
	}
	return false;
}

/*************************************************************************************************************************/
bool EventLogger::logADXL343Event(){//accéléromètre
	if (sensors[ADXL343_s] == nullptr) {
		return false;// Pas de capteur trouvé
	}
	const char* sensorName = sensors[HTU21D_s]->getSensorName();
	const char* measurement = sensors[ADXL343_s]->getFormattedMeasurement();//Longueur la plus LONGUE: 53, longueur la plus COURTE: 48

	int logNumber = 0; // Par défaut, premier log
	char lineBuffer[64]; // Buffer pour lire les lignes du fichier
	char logMessage[64]; // Buffer pour écrire le nouveau log

	if(logCurrentNumber[ADXL343_s] == -1){//On sait que le programme vient juste de redémaré
		if (f_open(&fil, "ADXL343.txt", FA_READ | FA_OPEN_EXISTING) == FR_OK) {
			while (f_gets(lineBuffer, sizeof(lineBuffer), &fil)) {
				// Trouver le numéro du dernier log (ligne du type "LOGX:")
				if (strncmp(lineBuffer, "LOG", 3) == 0) {
					int tempLogNumber = atoi(lineBuffer + 3); // Convertir le numéro de log.
					//Le '+ 3' permet a atoi de pointer le premier chiffre du log et il va lire les prochain char tant et aussi longtemps qu'il sont compris entre '0' et '9' pis convertir cela en string
					if (tempLogNumber > logNumber) {
						logNumber = tempLogNumber; // Garder le plus grand numéro
					}
				}
			}
			f_close(&fil);

		}
	}
	logNumber++; // Incrémenter le numéro de log pour le prochain
	if (f_open(&fil, "ADXL343.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK) {
		// Construire la nouvelle ligne de log
		snprintf(logMessage, sizeof(logMessage), "LOG%d: %s - %s\n", logNumber, sensorName, measurement);

		// Écrire la ligne dans le fichier
		UINT bytesWritten;
		if (f_write(&fil, logMessage, strlen(logMessage), &bytesWritten) != FR_OK || bytesWritten != strlen(logMessage)){
			f_close(&fil);
			return false; // Erreur d'écriture
		}

		// Synchroniser les tampons
		f_sync(&fil);
		f_close(&fil);
		return true; // Écriture réussie
	}
	return false;
}

/*************************************************************************************************************************/
bool EventLogger::logMultimetreEvent(){
	if (sensors[MULTIMETRE_s] == nullptr) {
		return false;// Pas de capteur trouvé
	}
	const char* sensorName = sensors[HTU21D_s]->getSensorName();
	const char* measurement = sensors[MULTIMETRE_s]->getFormattedMeasurement();//Longueur la plus LONGUE: 53, longueur la plus COURTE: 48

	int logNumber = 0; // Par défaut, premier log
	char lineBuffer[64]; // Buffer pour lire les lignes du fichier
	char logMessage[64]; // Buffer pour écrire le nouveau log

	if(logCurrentNumber[MULTIMETRE_s] == -1){//On sait que le programme vient juste de redémaré
		if (f_open(&fil, "MULTIMETRE.txt", FA_READ | FA_OPEN_EXISTING) == FR_OK) {
			while (f_gets(lineBuffer, sizeof(lineBuffer), &fil)) {
				// Trouver le numéro du dernier log (ligne du type "LOGX:")
				if (strncmp(lineBuffer, "LOG", 3) == 0) {
					int tempLogNumber = atoi(lineBuffer + 3); // Convertir le numéro de log.
					//Le '+ 3' permet a atoi de pointer le premier chiffre du log et il va lire les prochain char tant et aussi longtemps qu'il sont compris entre '0' et '9' pis convertir cela en string
					if (tempLogNumber > logNumber) {
						logNumber = tempLogNumber; // Garder le plus grand numéro
					}
				}
			}
			f_close(&fil);

		}
	}
	logNumber++; // Incrémenter le numéro de log pour le prochain
	if (f_open(&fil, "MULTIMETRE.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK) {
		// Construire la nouvelle ligne de log
		snprintf(logMessage, sizeof(logMessage), "LOG%d: %s - %s\n", logNumber, sensorName, measurement);

		// Écrire la ligne dans le fichier
		UINT bytesWritten;
		if (f_write(&fil, logMessage, strlen(logMessage), &bytesWritten) != FR_OK || bytesWritten != strlen(logMessage)){
			f_close(&fil);
			return false; // Erreur d'écriture
		}

		// Synchroniser les tampons
		f_sync(&fil);
		f_close(&fil);
		return true; // Écriture réussie
	}
	return false;
}

/*************************************************************************************************************************/
bool EventLogger::mountLogger(){
	if(f_mount(&FatFs, "", 1) != FR_OK){//1=mount now
		return false;
	}
	return true;
}

/*************************************************************************************************************************/
bool EventLogger::unmountLogger(){
	if(f_mount(NULL, "", 0) != FR_OK){
		return false;
	}
	return true;
}

/*************************************************************************************************************************/
bool EventLogger::updateLoggerSpec(){
	fres = f_getfree("", &fre_clust, &pfs);
	if (fres != FR_OK) {
		return false;
	}
	total = (uint32_t) ((pfs->n_fatent - 2) * pfs->csize * 0.5f);
	free_space = (uint32_t) (fre_clust * pfs->csize * 0.5f);
	return true;
}

/*************************************************************************************************************************/
uint32_t EventLogger::getLoggerTotalSpace(){
	return total;
}

/*************************************************************************************************************************/
uint32_t EventLogger::getLoggerFreeSpace(){
	return free_space;
}

/*************************************************************************************************************************/
void EventLogger::setCurrentSensor(currentSensor CurrentSensor){
	this->_sensor = CurrentSensor;
}

/*************************************************************************************************************************/
bool EventLogger::logEvent(){//pourrait être un bool
	switch(_sensor)
	{
		case HTU21D_s:
			return logHTU21DEvent();
			break;

		case VL53L0X_s:
			return logVL53L0XEvent();
			break;

		case LTR_303ALS_s:
			return logLTR_303ALSEvent();
			break;

		case ADXL343_s:
			return logADXL343Event();
			break;

		case MULTIMETRE_s:
			return logMultimetreEvent();
			break;

		case NONE:
			break;
		//C'est l'equivalent du 'NONE'
	}
	return true;

}
