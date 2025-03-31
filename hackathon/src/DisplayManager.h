// File: DisplayManager.h
//Written by ChatGPT, edited heavily by Daly

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DisplayManager {
public:
    DisplayManager(uint8_t width, uint8_t height, TwoWire* wire, int8_t reset);
    void initDisplay();
    void updateDisplay(float temp1, float temp2, int tempThreshold);

private:
    Adafruit_SSD1306 display;

};

#endif // DISPLAY_MANAGER_H
   

