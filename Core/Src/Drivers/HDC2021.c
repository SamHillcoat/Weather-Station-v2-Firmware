/*
 * HDC2021.c
 *
 *  Created on: Sep 8, 2024
 *      Author: hamsi
 * 
 * Driver for HDC2021 temperature and humidity sensor
 */

#include "HDC2021.h"

// Function Prototypes
HAL_StatusTypeDef HDC2021_ReadReg(HDC2021 *dev, uint8_t reg, uint8_t *data, uint8_t len);
HAL_StatusTypeDef HDC2021_WriteReg(HDC2021 *dev, uint8_t reg, uint8_t *data, uint8_t len);
HAL_StatusTypeDef HDC2021_Configure_TriggerMode(HDC2021 *dev);
HAL_StatusTypeDef HDC2021_Measure_Config(HDC2021 *dev);


// Functions
uint8_t HDC2021_Init(HDC2021 *dev, I2C_HandleTypeDef *hi2c)
{
    dev->hi2c = hi2c;
    dev->temp = 0;
    dev->hum = 0;


    // Check if the sensor is connected
    uint8_t data;
    if(HDC2021_ReadReg(dev, HDC2021_REG_DEVICE_ID, &data, 1) != HAL_OK)
    {
        return 1;
    }

    // Setup Config
    if (HDC2021_Configure_TriggerMode(dev) != HAL_OK)
    {
        return 2;
    }
    
    if (HDC2021_Measure_Config(dev) != HAL_OK)
    {
        return 3;
    }

    return 0;
}

uint8_t HDC2021_Read_Temp(HDC2021 *dev)
{
    uint8_t data[2];
    uint8_t config = 0x01; // Set trigger bit to 1

    // Trigger a temperature measurement
    if (HDC2021_WriteReg(dev, HDC2021_REG_MEAS_CONFIG, &config, 1) != HAL_OK)
    {
        return 1;
    }

    osDelay(5); // Wait for the measurement to complete

    if(HDC2021_ReadReg(dev, HDC2021_REG_TEMP_LOW, data, 2) != HAL_OK)
    {
        return 1;
    }

    uint16_t raw_temp = (data[1] << 8) | data[0];
    dev->temp = (float)raw_temp / 65536.0 * 165.0 - 40.0;

    return 0;
}


HAL_StatusTypeDef HDC2021_Configure_TriggerMode(HDC2021 *dev)
{
    uint8_t config = 0x00; // Set to trigger mode
    return HDC2021_WriteReg(dev, HDC2021_REG_CONFIG, &config, 1);
}

HAL_StatusTypeDef HDC2021_Measure_Config(HDC2021 *dev)
{
   // Set the measurement configuration register
    
    uint8_t config =  0x00 << 7 // 14-bit temp resolution
                    | 0x00 << 5 // 14-bit hum resolution
                    | 0x00 << 3 // Reserved
                    | 0x00 << 2; // Temp + Humidity measurement

    return HDC2021_WriteReg(dev, HDC2021_REG_CONFIG, &config, 1);
}

// Low Level Functions




HAL_StatusTypeDef HDC2021_ReadReg(HDC2021 *dev, uint8_t reg, uint8_t *data, uint8_t len)
{
    return HAL_I2C_Mem_Read(dev->hi2c, HDC2021_ADDR << 1, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

HAL_StatusTypeDef HDC2021_WriteReg(HDC2021 *dev, uint8_t reg, uint8_t *data, uint8_t len)
{
    return HAL_I2C_Mem_Write(dev->hi2c, HDC2021_ADDR << 1, reg, 1, data, len, HAL_MAX_DELAY);
}

