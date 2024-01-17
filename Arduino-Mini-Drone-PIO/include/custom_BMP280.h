#ifndef CUSTOM_BMP280_H
#define CUSTOM_BMP280_H

#include <Adafruit_BMP280.h>

class CustomBMP280 {
public:
    void init(uint8_t deviceAddress = 0x76);
    float getAltitude(float seaLevelhPa  = 1013.25);
    float getPressure();
    float getTemperature();

private:
    Adafruit_BMP280 bme;
};

#endif  // CUSTOM_BMP280_H
