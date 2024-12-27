/*
 * I2CHandler.h
 *
 *  Created on: Nov 30, 2024
 *      Author: victorx1
 */

#ifndef SRC_I2CHANDLER_H_
#define SRC_I2CHANDLER_H_



#include "stm32l0xx_hal.h"  // Inclure les définitions HAL

//VALIDER LA DIFFÉRENCE ENTRE LES 2 TYPES D'INCLUDE

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include "stm32l0xx_hal.h"  // HAL pour STM32
//
//#ifdef __cplusplus
//}
//#endif

class I2CHandler {
public:
    I2CHandler(I2C_HandleTypeDef *hi2c);
    HAL_StatusTypeDef write(uint16_t devAddress, uint8_t *data, uint16_t size);
    HAL_StatusTypeDef read(uint16_t devAddress, uint8_t *data, uint16_t size);

private:
    I2C_HandleTypeDef *m_hi2c;
};
#endif /* SRC_I2CHANDLER_H_ */




























//#include "stm32l0xx_hal.h"  // Inclure les définitions HAL
//class I2CHandler {
//private:
//    static I2CHandler* instance; // Pointeur vers l'instance unique
//    I2C_HandleTypeDef& hi2c;     // Référence au handle généré par CubeMX
//
//    // Constructeur privé pour empêcher l'instanciation directe
//    I2CHandler(I2C_HandleTypeDef& hi2c1);
//public:
//    // Supprimer le constructeur par copie et l'opérateur d'affectation
//    I2CHandler(const I2CHandler&) = delete;
//    I2CHandler& operator=(const I2CHandler&) = delete;
//
//    // Méthode pour obtenir l'instance unique
//    static I2CHandler& getInstance(I2C_HandleTypeDef& hi2c1) {
//        if (!instance) {
//            instance = new I2CHandler(hi2c1);//FAIRE DES NEW STATIC ET NON DYNAMIQUE UNE FOIS QUE TOUT FONCTIONNE
//        }
//        return *instance;
//    }
//
//    // Méthodes I2C simplifiées
//    HAL_StatusTypeDef write(uint16_t devAddress, uint8_t* data, uint16_t size);
//
//    HAL_StatusTypeDef read(uint16_t devAddress, uint8_t* data, uint16_t size);
//
//    // Ajoutez d'autres méthodes spécifiques selon vos besoins
//};
//
//// Initialisation du pointeur static
//I2CHandler* I2CHandler::instance = nullptr;


