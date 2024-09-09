/*
 * HDC2021.h
 *
 *  Created on: Sep 8, 2024
 *      Author: hamsi
 */

#ifndef INC_DRIVERS_HDC2021_H_
#define INC_DRIVERS_HDC2021_H_

#include "main.h"
#include <stdint.h>

#define HDC2021_ADDR 0x40 // 7-bit i2c address

// Register addresses
#define HDC2021_REG_TEMP_LOW 0x00
#define HDC2021_REG_TEMP_HIGH 0x01
#define HDC2021_REG_HUM_LOW 0x02
#define HDC2021_REG_HUM_HIGH 0x03
#define HDC2021_REG_CONFIG 0x0E
#define HDC2021_REG_MEAS_CONFIG 0x0F
#define HDC2021_REG_DEVICE_ID 0xFE

// Device ID
#define HDC2021_DEVICE_ID 0x07D0 // Expected device ID for HDC2021


typedef struct
{
    I2C_HandleTypeDef *hi2c;
    float temp;
    float hum;

} HDC2021;

uint8_t HDC2021_Init(HDC2021 *dev, I2C_HandleTypeDef *hi2c);

uint8_t HDC2021_Read_Temp(HDC2021 *dev);


#endif /* INC_DRIVERS_HDC2021_H_ */
