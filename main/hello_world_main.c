/*
 * Task 3: Simple LED Blink Program
 * Makes LED turn on and off every second
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

#define LED_PIN 2  // LED is connected to pin 2

void app_main(void)
{
    // Tell ESP32 that pin 2 is an output (so we can control it)
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    printf("Program started!\n");
    
    // Variable to track if LED should be on (1) or off (0)
    int led_on = 0;
    
    // Loop forever
    while(1) 
    {
        // Flip the LED state: if it was 0, make it 1; if it was 1, make it 0
        led_on = !led_on;
        
        // Actually turn the LED on or off based on our variable
        // 1 = LED on (3.3V output), 0 = LED off (0V output)
        gpio_set_level(LED_PIN, led_on);
        
        // Only print message when LED toggles from OFF to ON
        if (led_on == 1) {
            // Get current time in microseconds, convert to milliseconds
            int64_t time_ms = esp_timer_get_time() / 1000;
            printf("Hello World! Timestamp: %lld ms\n", time_ms);
        }
        
        // Wait 1 second (1000 milliseconds) before doing the next loop
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}