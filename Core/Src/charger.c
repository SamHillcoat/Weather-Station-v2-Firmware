/*
 * charger.c
 *
 *  Created on: Sep 5, 2024
 *      Author: hamsi
 */
#include "charger.h"
#include "batteryCharger.h"
#include "led_manager.h"
#include "main.h"

void startChargerStatusTask(void *argument) {
	// Task Init

	BatteryChargerStatus_t status;
	BatteryChargerStatus_t last_status = BATTERY_CHARGER_STATUS_UNKNOWN;
	BatteryCharger charger;

	BatteryCharger_Init(&charger, BATCHG_STAT1_GPIO_Port, BATCHG_STAT1_Pin, BATCHG_STAT2_Pin);
	// Infinite Loop

	for (;;) {
		LED_Manager_Update();

		status = BatteryCharger_getStatus(&charger);

		if (status != last_status) {
			LED_Manager_LED_All_Off();

			switch (status) {
				case BATTERY_CHARGER_STATUS_NO_BATTERY:
					LED_Manager_LED_On(1);
					LED_Manager_LED_On(2);
					break;
				case BATTERY_CHARGER_STATUS_CHARGING:
					LED_Manager_LED_On(0);
					LED_Manager_StartBlinking(0,1000);
					break;
				case BATTERY_CHARGER_STATUS_SOFT_FAULT:
					LED_Manager_LED_On(3);
					break;
				case BATTERY_CHARGER_STATUS_HARD_FAULT:
					LED_Manager_LED_On(1);
					LED_Manager_LED_On(2);
					break;
				case BATTERY_CHARGER_STATUS_CHARGE_DONE:
					//LED_Manager_LED_On(1);
					break;
				}
			last_status = status;
		}


	}


}
