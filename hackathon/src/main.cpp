// File: main.cpp

#include <Arduino.h>
#include <Servo.h>
#include "LocalSensor.h"
#include "Encoder.h"
#include "DisplayManager.h"

// Pin assignments
#define DHTPIN1 2
#define DHTPIN2 3
#define DHTTYPE DHT11
#define ENCODEPINCLK 4
#define ENCODEPINDT 5
#define ENCODEPINSW 6
#define SERVO_PIN 7

// Object instantiations
LocalSensor sensor1(DHTPIN1, DHTTYPE);
LocalSensor sensor2(DHTPIN2, DHTTYPE);
Encoder encoder(ENCODEPINCLK, ENCODEPINDT, ENCODEPINSW);
Servo motor;

int servoAngle = 90;
bool windowOpened = false;

void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.println("System Initializing...");

	sensor1.begin();
	sensor2.begin();
	motor.attach(SERVO_PIN);
	motor.write(servoAngle);

	initDisplay();
}

void loop() {
	sensor1.update();
	sensor2.update();
	float temp1 = sensor1.getTemperature();
	float temp2 = sensor2.getTemperature();
	int tempThreshold = encoder.selectTemperature();

	bool overThreshold = temp1 > tempThreshold || temp2 > tempThreshold;

	if (overThreshold && !windowOpened) {
		servoAngle = 0;
		motor.write(servoAngle);
		windowOpened = true;
	}
	else if (!overThreshold && windowOpened) {
		servoAngle = 90;
		motor.write(servoAngle);
		windowOpened = false;
	}

	updateDisplay(temp1, temp2, tempThreshold, servoAngle, overThreshold);
	delay(1000);
}
