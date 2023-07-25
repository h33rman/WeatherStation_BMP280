#include <Arduino.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/* WiFi connection parameters for the ESP8266 board */
const char* ssid = "ESP8266";  // SSID name
const char* password = "Test1234!";  // Password
/* IP address and gateway */
IPAddress local_ip(192, 168, 3, 1);
IPAddress gateway(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);
ESP8266WebServer server(80);

#define BMP280_ADDRESS 0x76

Adafruit_BMP280 bmp; // I2C

float temperature = 0.0;
float pressure = 0.0;
float altitude = 0.0;

// Read of the temperature & Pressure
void readSensorData() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() /100;
  altitude = bmp.readAltitude();
}

// Function to send the HTML file to the client
void handleRoot() {
  String html;
  File webfile = LittleFS.open("/index.html", "r"); // Use LittleFS to open the file
  if (webfile) {
    html = webfile.readString();
    webfile.close();
  } else {
    html = "Page web not found : Error opening file";
  }
  server.send(200, "text/html", html);
}

void handleData() {
  readSensorData();
  String data = "{\"temperature\":" + String(temperature) + 
                ",\"pressure\":" + String(pressure) + 
                ",\"altitude\":" + String(altitude) + "}";

  server.send(200, "application/json", data);
}

void setup() {
  // Initialize the serial port
  Serial.begin(9600);

  // Initialize the LittleFS file system
  LittleFS.begin();
  
  // Initialize the BMP280 sensor with the correct I2C address
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Launch the WiFi server
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  // Read the sensor data every 10 seconds
  static unsigned long lastReadTime = 0;
  if (millis() - lastReadTime >= 2000) {
    lastReadTime = millis();
    readSensorData();
  }
}