# ESP8266 Weather Station

This project utilizes an ESP8266 microcontroller and a BMP280 sensor to create a small, WiFi-enabled weather station. This weather station measures temperature, pressure, and altitude, and exposes this data over a simple HTTP interface.

## Prerequisites

The project uses the following hardware components:

- ESP8266 Microcontroller
- BMP280 sensor

And the following Arduino libraries:

- Arduino
- LittleFS for ESP8266
- ESP8266WiFi
- ESP8266WebServer
- Wire
- Adafruit Sensor
- Adafruit BMP280

## Setup and Installation

1. Clone this repository.
2. Open the project in Visual Studio Code.
3. Make sure you have the [PlatformIO IDE](https://platformio.org/platformio-ide) extension installed for handling Arduino code.
4. PlatformIO should automatically detect the libraries needed and prompt to install them. If not, manually install the above-mentioned libraries.
5. Build and upload the code to your ESP8266 using PlatformIO. 
The `index.html` file located in the `/data` folder of the project will be uploaded to the ESP8266's LittleFS filesystem during this step.

## Usage

Once the ESP8266 is powered on and running, connect to the WiFi network with SSID `ESP8266` and password `Test1234!`.
Enter to IP adress : http://192.168.3.1/

The web server has two available routes:

- `/` : This route serves a basic HTML page, which is stored in the ESP8266's LittleFS filesystem at `/data/index.html`. You can extend this page according to your needs.
- `/data` : This route provides the current sensor data in JSON format.

The sensor data is updated every 2000 milliseconds.

## Contributing

Feel free to submit pull requests, create issues or share ideas to improve this weather station!

