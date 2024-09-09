/*
 * battery_status.c
 *
 *  Created on: Sep 4, 2024
 *      Author: Sam Hillcoat
 */
#include <stdint.h>
#include "batteryCharger.h"
#include <stdbool.h>

BatteryChargerStatus_t BatteryCharger_getStatus(BatteryCharger *self) {
    // Read the initial status of STAT1 and STAT2
	uint8_t status1 = HAL_GPIO_ReadPin(self->statusPort, self->statusPin1);
	uint8_t status2_initial = HAL_GPIO_ReadPin(self->statusPort, self->statusPin2);

	// From Datasheet:
	// When there is no battery present, the device will charge the capacitor on
	// the BAT pin and toggle between charging done, charge completed.
	// So STAT1 pin will be stable where as STAT2 pin will toggle between HIGH and LOW

	// Delay a short period to allow for toggling (adjust delay as needed)
	HAL_Delay(40);  // 10 ms delay, adjust based on the expected toggle frequency

	// Read the STAT2 pin again to check for toggling
	uint8_t status2_final = HAL_GPIO_ReadPin(self->statusPort, self->statusPin2);

	// Determine if STAT2 is toggling (high to low or low to high)
	bool status2isToggling = (status2_initial != status2_final);

    // Determine the status based on the GPIO pin readings
    if (status1 == GPIO_PIN_SET && status2isToggling) {
        return BATTERY_CHARGER_STATUS_NO_BATTERY;
    } else if (status1 == GPIO_PIN_SET && status2_final == GPIO_PIN_RESET) {
    	return BATTERY_CHARGER_STATUS_CHARGING;
    } else if (status1 == GPIO_PIN_RESET && status2_final == GPIO_PIN_SET) {
        return BATTERY_CHARGER_STATUS_SOFT_FAULT;
    } else if (status1 == GPIO_PIN_SET && status2_final == GPIO_PIN_SET) {
        return BATTERY_CHARGER_STATUS_CHARGE_DONE;
    } else if (status1 == GPIO_PIN_RESET && status2_final == GPIO_PIN_RESET) {
        return BATTERY_CHARGER_STATUS_HARD_FAULT;
    } else {
        return BATTERY_CHARGER_STATUS_UNKNOWN;
    }
}

void BatteryCharger_Init(BatteryCharger *charger, GPIO_TypeDef *port, uint16_t stat1, uint16_t stat2) {
	charger->statusPort = port;
	charger->statusPin1 = stat1;
	charger->statusPin2 = stat2;
}

