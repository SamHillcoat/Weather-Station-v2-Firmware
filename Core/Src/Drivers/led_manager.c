#include "led_manager.h"
#include "main.h"


#define LED_COUNT 3  // Number of LEDs in the system

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t blink_interval;
    uint32_t last_toggle_time;
    uint8_t is_blinking;
} LED_t;

// Array to hold each LED's configuration
static LED_t leds[LED_COUNT];

// Internal function to retrieve LED by index
static LED_t* getLEDByIndex(int led_index) {
    if (led_index < LED_COUNT) {
        return &leds[led_index];
    }
    return NULL;
}

// Initializes the LEDs with their respective GPIO pins
void LED_Manager_Init(void) {
    // Define the pin configurations for each LED
    leds[0].port = GPIOC; leds[0].pin = MCU_LED1_Pin;
    leds[1].port = GPIOC; leds[1].pin = MCU_LED2_Pin;
    leds[2].port = GPIOC; leds[2].pin = MCU_LED3_Pin;

}

// Starts blinking the LED with a specific interval (non-blocking)
void LED_Manager_StartBlinking(int led_index, uint32_t interval_ms) {
    LED_t *led = getLEDByIndex(led_index);
    if (led != NULL) {
    	if (led->is_blinking == 0) { // If not already blinking
			led->blink_interval = interval_ms;
			led->last_toggle_time = HAL_GetTick();
			led->is_blinking = 1;  // Set LED to blink mode
    	}
    }
}

// Stops blinking the LED
void LED_Manager_StopBlinking(int led_index) {
    LED_t *led = getLEDByIndex(led_index);
    if (led != NULL) {
        led->is_blinking = 0;  // Disable blink mode
        HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);  // Ensure the LED is off
    }
}

// Toggles the LED state (on/off)
void LED_Manager_Toggle(int led_index) {
    LED_t *led = getLEDByIndex(led_index);
    if (led != NULL) {
        HAL_GPIO_TogglePin(led->port, led->pin);  // Toggle the LED pin
    }
}

void LED_Manager_LED_On(int led_index) {
	LED_t *led = getLEDByIndex(led_index);
	if (led != NULL) {
	    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);  //Turn on LED pin
	}
}

void LED_Manager_LED_Off(int led_index) {
	LED_t *led = getLEDByIndex(led_index);
	if (led != NULL) {
	    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);  //Turn off LED pin
	}
}


void LED_Manager_LED_All_Off(void) {
	for (int i = 0; i < LED_COUNT; i++) {
		LED_t *led = &leds[i];
		HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);  //Turn off LED pin
	}
}


// Updates the LEDs for non-blocking blinking
void LED_Manager_Update(void) {
    uint32_t current_time = HAL_GetTick();  // Get the current system tick

    // Check each LED and handle blinking if enabled
    for (int i = 0; i < LED_COUNT; i++) {
        LED_t *led = &leds[i];

        if (led->is_blinking) {
            // Check if it's time to toggle the LED based on the blink interval
            if ((current_time - led->last_toggle_time) >= led->blink_interval) {
                HAL_GPIO_TogglePin(led->port, led->pin);  // Toggle the LED pin
                led->last_toggle_time = current_time;  // Update the last toggle time
            }
        }
    }
}
