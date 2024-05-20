# Soil Moisture Sensor on ESP8266
**Flower Project**

The Flower Project is a web application for monitoring soil moisture levels of plants. The application displays the current moisture levels and plant status based on defined moisture ranges. The application is built using PlatformIO and ESP8266, with soil moisture data displayed on an HTML page.

## Requirements

### Hardware
- ESP8266 (D1 Mini)
- Soil moisture sensor (HW-390)
- 2x Capacitors (100uF)
- Voltage regulator (L7805)

### Software
- PlatformIO

## Usage
1. Clone the repository
2. Open the project in PlatformIO
3. Connect the hardware components as shown in the diagram below
4. Upload the code to the ESP8266
5. Open the serial monitor to get the IP address of the ESP8266
6. Open a web browser and enter the IP address of the ESP8266

## Configuration

### Wiring Diagram
```
ESP8266 (D1 Mini)  -> Soil Moisture Sensor (HW-390)
-----------------------------------------------
3V3                -> VCC
GND                -> GND
A0                 -> A0
```

### Settings
1. Set the WiFi SSID and password in the `.env` file (see `.env.example`)
2. Run command `pio run -t uploadfs` to upload files to the ESP8266
3. Run command `pio run -t upload` to upload the code to the ESP8266

## Known Issues
* High energy consumption from async server (~82mAh)
* Ranges are hardcoded in the index html file

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Author

Paweł Szlendak ([@shlendakh](https://github.com/shlendakh))
