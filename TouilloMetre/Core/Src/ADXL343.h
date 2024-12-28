/*
 * ADXL343.h
 *
 *  Created on: Dec 27, 2024
 *      Author: victorx1
 */

#ifndef SRC_ADXL343_H_
#define SRC_ADXL343_H_

#include "ISensor.h"
#include "I2CHandler.h"
#include <stdint.h>
#include <stdbool.h>//pt pas de besoin

#define ADXL343_ADDRESS (0x53) /**< Adresse I2C par défaut */

/* Registre I2C  (IDÉALEMENT LE CONVERTIR EN ENUM, MAIS JUSTE POUR ÊTRE SUR CV ÊTRE DES DEFINES POUR L'INSTANT */
#define ADXL3XX_REG_DEVID (0x00)        /**< Device ID */
#define ADXL3XX_REG_THRESH_TAP (0x1D)   /**< Tap threshold */
#define ADXL3XX_REG_OFSX (0x1E)         /**< X-axis offset */
#define ADXL3XX_REG_OFSY (0x1F)         /**< Y-axis offset */
#define ADXL3XX_REG_OFSZ (0x20)         /**< Z-axis offset */
#define ADXL3XX_REG_DUR (0x21)          /**< Tap duration */
#define ADXL3XX_REG_LATENT (0x22)       /**< Tap latency */
#define ADXL3XX_REG_WINDOW (0x23)       /**< Tap window */
#define ADXL3XX_REG_THRESH_ACT (0x24)   /**< Activity threshold */
#define ADXL3XX_REG_THRESH_INACT (0x25) /**< Inactivity threshold */
#define ADXL3XX_REG_TIME_INACT (0x26)   /**< Inactivity time */
#define ADXL3XX_REG_ACT_INACT_CTL                                              \
  (0x27) /**< Axis enable control for activity and inactivity detection */
#define ADXL3XX_REG_THRESH_FF (0x28) /**< Free-fall threshold */
#define ADXL3XX_REG_TIME_FF (0x29)   /**< Free-fall time */
#define ADXL3XX_REG_TAP_AXES (0x2A)  /**< Axis control for single/double tap */
#define ADXL3XX_REG_ACT_TAP_STATUS (0x2B) /**< Source for single/double tap */
#define ADXL3XX_REG_BW_RATE (0x2C)     /**< Data rate and power mode control */
#define ADXL3XX_REG_POWER_CTL (0x2D)   /**< Power-saving features control */
#define ADXL3XX_REG_INT_ENABLE (0x2E)  /**< Interrupt enable control */
#define ADXL3XX_REG_INT_MAP (0x2F)     /**< Interrupt mapping control */
#define ADXL3XX_REG_INT_SOURCE (0x30)  /**< Source of interrupts */
#define ADXL3XX_REG_DATA_FORMAT (0x31) /**< Data format control */
#define ADXL3XX_REG_DATAX0 (0x32)      /**< X-axis data 0 */
#define ADXL3XX_REG_DATAX1 (0x33)      /**< X-axis data 1 */
#define ADXL3XX_REG_DATAY0 (0x34)      /**< Y-axis data 0 */
#define ADXL3XX_REG_DATAY1 (0x35)      /**< Y-axis data 1 */
#define ADXL3XX_REG_DATAZ0 (0x36)      /**< Z-axis data 0 */
#define ADXL3XX_REG_DATAZ1 (0x37)      /**< Z-axis data 1 */
#define ADXL3XX_REG_FIFO_CTL (0x38)    /**< FIFO control */
#define ADXL3XX_REG_FIFO_STATUS (0x39) /**< FIFO status */

#define ADXL343_MG2G_MULTIPLIER (0.004F)


/** range de mesure (±g) */
typedef enum {
    ADXL343_RANGE_16_G = 0b11, /**< ±16g */
    ADXL343_RANGE_8_G = 0b10,  /**< ±8g */
    ADXL343_RANGE_4_G = 0b01,  /**< ±4g */
    ADXL343_RANGE_2_G = 0b00   /**< ±2g */
} adxl343_range_t;

/** Rate des données */
typedef enum {
  ADXL343_DATARATE_3200_HZ = 0b1111, /**< 3200Hz Bandwidth */
  ADXL343_DATARATE_1600_HZ = 0b1110, /**< 1600Hz Bandwidth */
  ADXL343_DATARATE_800_HZ = 0b1101,  /**<  800Hz Bandwidth */
  ADXL343_DATARATE_400_HZ = 0b1100,  /**<  400Hz Bandwidth */
  ADXL343_DATARATE_200_HZ = 0b1011,  /**<  200Hz Bandwidth */
  ADXL343_DATARATE_100_HZ = 0b1010,  /**<  100Hz Bandwidth */
  ADXL343_DATARATE_50_HZ = 0b1001,   /**<   50Hz Bandwidth */
  ADXL343_DATARATE_25_HZ = 0b1000,   /**<   25Hz Bandwidth */
  ADXL343_DATARATE_12_5_HZ = 0b0111, /**< 12.5Hz Bandwidth */
  ADXL343_DATARATE_6_25HZ = 0b0110,  /**< 6.25Hz Bandwidth */
  ADXL343_DATARATE_3_13_HZ = 0b0101, /**< 3.13Hz Bandwidth */
  ADXL343_DATARATE_1_56_HZ = 0b0100, /**< 1.56Hz Bandwidth */
  ADXL343_DATARATE_0_78_HZ = 0b0011, /**< 0.78Hz Bandwidth */
  ADXL343_DATARATE_0_39_HZ = 0b0010, /**< 0.39Hz Bandwidth */
  ADXL343_DATARATE_0_20_HZ = 0b0001, /**< 0.20Hz Bandwidth */
  ADXL343_DATARATE_0_10_HZ = 0b0000, /**< 0.10Hz Bandwidth (default value) */
} adxl343_dataRate_t;


class ADXL343 : public ISensor{
private:
	static const uint8_t HTU21D_ADDR = 0x40;

	  const uint8_t _addr;
	  I2CHandler& _i2cHandler;
	  adxl343_range_t _range;

	  const char* _name;
	  char _formattedBuffer[40];
public:
	ADXL343(uint8_t addr, I2CHandler& i2cHandler);
	bool begin();
	void setRange(adxl343_range_t range);
	adxl343_range_t getRange(void);
	void setDataRate(adxl343_dataRate_t dataRate);
	adxl343_dataRate_t getDataRate(void);
	void setTrimOffsets(int8_t x, int8_t y, int8_t z);
	void getTrimOffsets(int8_t *x, int8_t *y, int8_t *z);
	bool readAcceleration(int16_t *x, int16_t *y, int16_t *z);

	  /*------------- ISensor -------------*/
	const char* getFormattedMeasurement();
	const char* getSensorName();

};

#endif /* SRC_ADXL343_H_ */
