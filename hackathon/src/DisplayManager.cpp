// File: DisplayManager.cpp

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DisplayManager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("SSD1306 allocation failed"));
		while (true);
	}
	display.clearDisplay();
	display.display();
}

void updateDisplay(float temp1, float temp2, int tempThreshold, int servoAngle, bool overThreshold) {
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0, 0);
	display.print("Temp1: "); display.print(temp1); display.println(" C");
	display.print("Temp2: "); display.print(temp2); display.println(" C");
	display.print("Thresh: "); display.print(tempThreshold); display.println(" C");
	display.print("Servo: "); display.print(servoAngle); display.println(" deg");

	if (overThreshold) {
		display.setCursor(0, 50);
		display.print("Temp Exceeds Desired Temp");
		display.setCursor(0, 58);
		display.print("Opening Window");
	}

	display.display();
}
