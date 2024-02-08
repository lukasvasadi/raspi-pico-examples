/**
 * Pico serial echo
 *
 * Adapted from Reddit discussion (https://www.reddit.com/r/raspberrypipico/comments/16ibwpk/comment/k0joo2s/)
 */

#include <stdio.h>
#include <tusb.h>
#include "pico/stdlib.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#define MAX_MESSAGE_LENGTH 99

int main() {
    stdio_init_all();

    // Create a place to hold the incoming message
    static char buffer[MAX_MESSAGE_LENGTH];
    static unsigned int index = 0;

    while (!tud_cdc_connected())
        sleep_ms(100);

    printf("Device connected\n");

    while (true) {
        // Check to see if anything is available in the serial receive buffer
        while (tud_cdc_available()) {
            // Read the next available byte in the serial receive buffer
            char inByte = getchar();
            // Parse incoming message: check not terminating character and guard for over message size
            if (inByte != '\n' && (index < MAX_MESSAGE_LENGTH - 1)) {
                // Add the incoming byte to buffer
                buffer[index] = inByte;
                index++;
            } else {
                // Add null character to terminate string
                buffer[index] = '\0';
                printf("%s\n", buffer);
                // Reset for the next message
                index = 0;
            }
        }
    }
}

#pragma clang diagnostic pop
