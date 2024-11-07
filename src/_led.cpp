#include <Arduino.h>

void InitLED() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void LedRed() {
    neopixelWrite(LED_BUILTIN, RGB_BRIGHTNESS,0,0);  // Turn the LED on   
}

void LedGreen() {
    neopixelWrite(LED_BUILTIN, 0,RGB_BRIGHTNESS,0);  // Turn the LED on   
}

void LedBlue() {
    neopixelWrite(LED_BUILTIN, 0,0,RGB_BRIGHTNESS);  // Turn the LED on   
}