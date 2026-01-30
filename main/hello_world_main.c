/*
 * Task 3: Simple LED Blink Program
 * Blink 1Hz on GPIO2 and prove GPIO_FUNC2_OUT_SEL is set to 256
 */

// Standard input/output library for printf()
#include <stdio.h>

// FreeRTOS headers - the operating system running on ESP32
#include "freertos/FreeRTOS.h"     // Core FreeRTOS functions
#include "freertos/task.h"          // Task management (delays, scheduling)

// ESP-IDF GPIO driver - high-level functions to control GPIO pins
#include "driver/gpio.h"

// Logging and timing utilities
#include "esp_log.h"                // Logging functions (not used in this code)
#include "esp_timer.h"              // Timer functions to get timestamps

// Low-level register access (for advanced users who want direct hardware control)
#include "soc/gpio_reg.h"           // GPIO register definitions
#include "soc/gpio_sig_map.h"       // GPIO signal mapping definitions (SIG_GPIO_OUT_IDX)
#include "soc/soc.h"                // General SoC definitions

// Define which GPIO pin the LED is connected to
#define LED_PIN 2  // LED is connected to GPIO2 (IO2)

// Main application entry point - this function runs when the ESP32 boots
void app_main(void)
{
    // ========== STEP 1: Configure GPIO2 as an OUTPUT ==========
    
    // Create a configuration structure to tell the ESP32 how we want GPIO2 set up
    gpio_config_t io_conf = {
        // Select GPIO2 using bit shifting (bit 2 = GPIO2)
        .pin_bit_mask = (1ULL << LED_PIN),
        
        // Set this pin as OUTPUT so we can control the LED
        .mode = GPIO_MODE_OUTPUT,

    };
    
    // Apply the configuration to GPIO2
    // This function call triggers the entire call chain:
    // gpio_config() → gpio_hal_func_sel() → gpio_output_enable() → 
    // gpio_hal_matrix_out_default() → writes 256 to GPIO_FUNC2_OUT_SEL register
    gpio_config(&io_conf);

    // ========== STEP 2: LED Blinking Loop ==========
    
    // Variable to track LED state (0 = off, 1 = on)
    int led_on = 0;
    
    // Infinite loop - blink the LED forever
    while (1) {
        // Toggle the LED state (if it was 0, make it 1; if it was 1, make it 0)
        led_on = !led_on;
        
        // Write the new state to GPIO2 (turns LED on or off)
        gpio_set_level(LED_PIN, led_on);
        
        // If we just turned the LED ON, print a message
        if (led_on) {
            // Get the current time in microseconds since boot
            int64_t time_us = esp_timer_get_time();
            
            // Convert microseconds to milliseconds
            int64_t time_ms = time_us / 1000;
            
            // Print "Hello World!" with the timestamp
            printf("Hello World! Timestamp: %lld ms\n", time_ms);
        }
        
        // Wait 500 milliseconds before changing the LED state again
        // 500ms ON + 500ms OFF = 1000ms total = 1Hz (once per second)
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}