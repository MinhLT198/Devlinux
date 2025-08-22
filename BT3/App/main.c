#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <stdbool.h>
#include "led_driver.h"


int main() {
    printf ("LED Driver Test\n");
    // Initialize the LED driver with 10 pixels
    if (led_init(10) != 0) {
        printf("LED initialization failed.\n");
        return -1;
    }
    
    const uint32_t *led_buffer = led_get_buffer();
    size_t pixel_count = led_get_pixel_count();

    if (led_buffer == NULL || pixel_count == 0) {
        printf("LED buffer not initialized.\n");
        return -1;
    }
    
    printf("LED driver initialized with %ld pixels.\n", pixel_count);
    printf("LED buffer Initialize:\n");

    for (size_t i = 0; i < pixel_count; i++) {
        printf("0x%08X\t", led_buffer[i]);
    }
    printf("\n");

    led_set_pixel_color(0, 255, 0, 0); // Set first pixel to red
    led_set_pixel_color(9, 0, 0, 255); // Set last pixel to blue
    led_set_pixel_color(4, 255, 255, 255); // Set middle pixel to white
    printf("LED buffer after setting colors:\n");
    for (size_t i = 0; i < pixel_count; i++) {
        printf("0x%08X\t", led_buffer[i]);
    }
    printf("\n");

    led_fill(0, 255, 0); // Fill all pixels with green
    printf("LED buffer after filling with green:\n");
    for (size_t i = 0; i < pixel_count; i++) {
        printf("0x%08X\t", led_buffer[i]);
    }
    printf("\n");

    led_clear(); // Clear the LED buffer
    printf("LED buffer after clearing:\n");
    for (size_t i = 0; i < pixel_count; i++) {
        printf("0x%08X\t", led_buffer[i]);
    }
    printf("\n");

    // Shutdown the LED driver
    Led_shutdown();
    printf("LED driver shutdown.\n");

    return 0;
}