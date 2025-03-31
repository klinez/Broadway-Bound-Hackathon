// File: OledScreen.ino

#include <Wire.h>                             // I2C communication library
#include <Adafruit_GFX.h>                     // Core graphics library for OLED
#include <Adafruit_SSD1306.h>                 // OLED display driver
#include <Servo.h>                             // Servo motor library
#include "LocalSensor.h"                      // LocalSensor abstraction for DHT11
#include "Encoder.h"                          // Encoder input handler

// OLED display config
#define SCREEN_WIDTH 128                      // OLED display width in pixels
#define SCREEN_HEIGHT 64                      // OLED display height in pixels
#define OLED_RESET     -1                     // Reset pin not used
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensor and encoder pin definitions
#define DHTPIN1 2                              // DHT11 sensor #1 on GPIO2
#define DHTPIN2 3                              // DHT11 sensor #2 on GPIO3
#define DHTTYPE DHT11                          // Sensor type is DHT11
#define ENCODEPINCLK 4                         // Rotary encoder CLK pin
#define ENCODEPINDT 5                          // Rotary encoder DT pin
#define ENCODEPINSW 6                          // Rotary encoder button pin
#define SERVO_PIN 7                            // Servo control pin

// Objects for sensor and input handling
LocalSensor sensor1(DHTPIN1, DHTTYPE);
LocalSensor sensor2(DHTPIN2, DHTTYPE);
Encoder encoder(ENCODEPINCLK, ENCODEPINDT, ENCODEPINSW);
Servo motor;
int servoAngle = 90;                           // Default servo angle
bool windowOpened = false;                    // Tracks if window was already opened

void setup() {
	Serial.begin(115200);                       // Start serial communication

	// Initialize OLED display
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("SSD1306 allocation failed"));
		for (;;);
	}
	display.clearDisplay();
	display.display();

	// Initialize sensors
	sensor1.begin();
	sensor2.begin();

	// Attach servo to pin
	motor.attach(SERVO_PIN);
	motor.write(servoAngle);
}

void loop() {
	// Update and retrieve sensor readings
	sensor1.update();
	sensor2.update();
	float temp1 = sensor1.getTemperature();
	float temp2 = sensor2.getTemperature();

	// Read target temp from encoder interface
	int tempThreshold = encoder.selectTemperature();

	// Check if temperature exceeds threshold
	bool overThreshold = temp1 > tempThreshold || temp2 > tempThreshold;

	// If over threshold and window not yet opened, trigger servo
	if (overThreshold && !windowOpened) {
		servoAngle = 0;                          // Open window
		motor.write(servoAngle);
		windowOpened = true;
	}
	else if (!overThreshold && windowOpened) {
		servoAngle = 90;                         // Close window
		motor.write(servoAngle);
		windowOpened = false;
	}

	// Display values on OLED
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0, 0);
	display.print("Temp1: "); display.print(temp1); display.println(" C");
	display.print("Temp2: "); display.print(temp2); display.println(" C");
	display.print("Thresh: "); display.print(tempThreshold); display.println(" C");
	display.print("Servo: "); display.print(servoAngle); display.println(" deg");

	// If over threshold, flash a warning message
	if (overThreshold) {
		display.setTextSize(1);
		display.setCursor(0, 50);
		display.print("Temp Exceeds Desired Temp");
		display.setCursor(0, 58);
		display.print("Opening Window");
	}

	display.display();
	delay(1000);                                // Update once per second
}
