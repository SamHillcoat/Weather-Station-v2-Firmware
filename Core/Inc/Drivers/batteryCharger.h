/*
 * battery_status.h
 *
 *  Created on: Sep 4, 2024
 *      Author: Sam
 *
 *Status Driver for Bq25185 Battery Charging and Power Management Chip
 */

#ifndef INC_BATTERYCHARGER_H_
#define INC_BATTERYCHARGER_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"



// Based on BQ25185 Datasheet Status Pins Table
typedef enum {
	BATTERY_CHARGER_STATUS_UNKNOWN = 0,
	BATTERY_CHARGER_STATUS_CHARGING,
	BATTERY_CHARGER_STATUS_CHARGE_DONE,
	BATTERY_CHARGER_STATUS_SOFT_FAULT,
	BATTERY_CHARGER_STATUS_HARD_FAULT,
	BATTERY_CHARGER_STATUS_NO_BATTERY,
} BatteryChargerStatus_t ;

typedef struct {
	GPIO_TypeDef *statusPort;
	uint16_t statusPin1;
	uint16_t statusPin2;
} BatteryCharger ;


// API Functions
BatteryChargerStatus_t BatteryCharger_getStatus(BatteryCharger *dev);
void BatteryCharger_Init(BatteryCharger *charger, GPIO_TypeDef *port, uint16_t stat1, uint16_t stat2);

#endif /* INC_BATTERYCHARGER_H_ */
