/*
 * leds.h
 *
 *  Created on: Sep 4, 2024
 *      Author: hamsi
 *
 *      ledController:
 *      Driver for status LEDs
 */

#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <stdint.h>

// Initializes all LEDs
void LED_Manager_Init(void);

// Functions to control the LEDs
void LED_Manager_StartBlinking(int led_index, uint32_t interval_ms);
void LED_Manager_StopBlinking(int led_index);
void LED_Manager_LED_On(int led_index);
void LED_Manager_LED_Off(int led_index);
void LED_Manager_LED_All_Off(void);
void LED_Manager_LED_Toggle(int led_index);
void LED_Manager_Update(void);

#endif
