// File: DisplayManager.cpp
//Written by ChatGPT, prompted by Jaden
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t width, uint8_t height, TwoWire* wire, int8_t reset)
    : display(width, height, wire, reset) {}

    //init display for setup()
void DisplayManager::initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    display.clearDisplay();
    display.display();
}

//update screen with changing temperature
void DisplayManager::updateDisplay(float temp1, float temp2, int tempThreshold) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Inside: "); display.print(temp1); display.println(" C");
    display.print("Outside: "); display.print(temp2); display.println(" C");
    display.print("Target: "); display.print(tempThreshold); display.println(" C");

    display.display();
}
