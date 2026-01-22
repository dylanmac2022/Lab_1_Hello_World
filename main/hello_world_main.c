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
        
        // Only print message when LED turns on (not when it turns off)
        if (led_on) {
            // Get current time in microseconds and print it
            printf("Hello World! Timestamp: %lld us\n", esp_timer_get_time());
        }
        
        // Wait 1 second (1000 milliseconds) before doing the next loop
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}