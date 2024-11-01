#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <HCSR04.h>

// Define the I2C screen address
const int screenAddress = 0x27;

// Define the DHT11 sensor pin
const int dhtPin = 4;

// Define the HCSR04 sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Define the MQ135 sensor pin
const int mq135Pin = A0;

// Create an instance of the I2C screen
LiquidCrystal_I2C screen(screenAddress, 16, 2);

// Create an instance of the DHT11 sensor
DHT dht(dhtPin, DHT11);

// Create an instance of the HCSR04 sensor
HCSR04 hcsr04(trigPin, echoPin);

void setup() {
  // Initialize the I2C screen
  screen.init();
  screen.backlight();

  // Initialize the DHT11 sensor
  dht.begin();

  // Initialize the HCSR04 sensor
  hcsr04.begin();

  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read the distance from the HCSR04 sensor
  float distance = hcsr04.distanceInCentimeters();

  // Read the gas level from the MQ135 sensor
  int gasLevel = analogRead(mq135Pin);

  // Display the data on the I2C screen
  screen.setCursor(0, 0);
  screen.print("Temp: ");
  screen.print(temperature);
  screen.print("C");
  screen.setCursor(0, 1);
  screen.print("Humidity: ");
  screen.print(humidity);
  screen.print("%");
  screen.setCursor(0, 2);
  screen.print("Distance: ");
  screen.print(distance);
  screen.print("cm");
  screen.setCursor(0, 3);
  screen.print("Gas Level: ");
  screen.print(gasLevel);

  // Wait for 1 second before updating the display again
  delay(1000);
}
