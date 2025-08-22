/**
 * @file led_driver.c
 * @brief LED Strip Driver for Addressable RGB LEDs (e.g., WS2812B). 
 *
 * This file provides functions to initialize, control, and free
 * the LED buffer for on addressable RGB LED strip.
 */
#include <stdlib.h> // malloc, free
#include <stdint.h> // uint8_t, uint32_t
#include <stddef.h> // size_t
#include "led_driver.h" // Header file for LED functions

 /** @brief Pointer to LED pixel buffer (RGB format). */
 static uint32_t *led_buffer = NULL;

 /** @brief Number of pixels in the LED trip. */
 static size_t led_count = 0;
 
/**
 * @brief Initialize the LED buffer for a given number of pixels.
 * 
 * This function allocates a memory buffer to store RGB values for each pixel. Each pixel is represented by a 32 bit integer.
 * where each pixel uses 24 bits (RGB888 format).
 * The highest 8 bits are unused and set to 0.
 * If a buffer already exists, it will be freed and replaced with the new one. 
 *
 * @param num_pixels Number of LEDs in the strip.
 * @return
 * - '0' : Initialization successful.
 * - '-1' : Memory allocation failed.
 *
 * @note After initialization, all pixels are set to 0x00000000 (off).
 */
int led_init(size_t num_pixels) {
    // Free exitting buuffer if a buffer already exists
    if(led_buffer != NULL) {
        free(led_buffer);
        led_buffer = NULL;
    }

    // Store number of pixels
    led_count = num_pixels;

    // Allocate memory: 3 bytes per LED
    led_buffer = (uint32_t *)malloc(led_count * sizeof(uint32_t));
    if(led_buffer == NULL) {
        led_count = 0;
        return -1; // Memory allocation failed
    }
    
    // Initialize all pixels to off (0x00000000)
    for (size_t i = 0; i < led_count; i++) {
        led_buffer[i] = 0x00000000; // Set pixel to off
    }
    
    return 0; // Initialization successful
}

/** 
 * @brief Shutdown the LED buffer.
 * 
 * This function frees the memory allocated for the LED strip.
 * @param None
 * @return None
 *
 * @note
 * */
void Led_shutdown() {
    if (led_buffer == NULL) {
        return; // No buffer to free
    }

    free(led_buffer);
    led_buffer = NULL;
    led_count = 0; // Reset pixel count
}

/** 
 * @brief Set the color of a specific pixel.
 * 
 * This function sets the color of a specific pixel at the given 'index'.
 * Use 3 separate 8-bit values for Red, Green, and Blue.
 * @param index, r, g, b
 * - index: The index of the pixel to set (0-based).
 * - r: Red component (0-255).
 * - g: Green component (0-255).
 * - b: Blue component (0-255).
 * @return None
 *
 * @note 
 * If the index is out of bounds, the function does nothing.
*/
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b) {
    if (led_buffer == NULL || index >= led_count || index < 0) {
        return; // No buffer or index out of bounds
    }

    // Set pixel color in RGB888 format (highest 8 bits unused)
    led_buffer[index] = (r << 16) | (g << 8) | b;
}

/** 
 * @brief Fills the entire strip with a single color.
 *
 * @param r, g, b
 * - r: Red component (0-255).
 * - g: Green component (0-255).
 * - b: Blue component (0-255).
 * @return None
 *
 * @note 
 * This function sets all pixels in the buffer to the same color.
 * If the buffer is not initialized or has zero pixels, it does nothing.
 */
void led_fill(uint8_t r, uint8_t g, uint8_t b) {
    if (led_buffer == NULL || led_count == 0) {
        return; // No buffer or no pixels to fill
    }

    uint32_t color = (r << 16) | (g << 8) | b; // Create RGB888 color
    for (size_t i = 0; i < led_count; i++) {
        led_buffer[i] = color; // Set each pixel to the specified color
    }
}

/** @brief  Clear the LED buffer.
 *
 * This function turns off all pixels (by setting their color to black).
 * @param None
 * @return None
 *
 * @note 
 * */
void led_clear() {
    if (led_buffer == NULL || led_count == 0) {
        return; // No buffer to clear
    }

    for (size_t i = 0; i < led_count; i++) {
        led_buffer[i] = 0x00000000; // Set pixel to off
    }
}

/**
 * @brief Get the pointer to the LED buffer.
 *
 * This function gets a constant (read-only) pointer to the data buffer, ready to be "sent" out.
 * Used for testing purposes in this exercise.
 * @param None
 * @return
 * - Pointer to the LED buffer (constant).
 *
 * @note 
 * The buffer should not be modified directly; use led_set_pixel_color() or led_fill() instead.
 * The buffer must be initialized before calling this function.
 * If the buffer is not initialized, it returns NULL.
*/
const uint32_t* led_get_buffer() {
    if (led_buffer == NULL) {
        return NULL; // Buffer not initialized
    }
    return (const uint32_t *)led_buffer; // Return constant pointer to the buffer
}

/**
 * @brief Gets the number of pixels on the LED trip.
 *
 * This function returns the number of pixels in the LED strip.
 * @param None
 * @return
 * - Number of pixels in the LED strip.
 *
 * @note 
 * If the buffer is not initialized, it returns 0.
 * This function is useful to know how many pixels are available for control.  
 */
size_t led_get_pixel_count() {
    return led_count; // Return the number of pixels
}

