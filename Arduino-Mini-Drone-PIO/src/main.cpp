#include <Arduino.h>
#include "custom_BMP280.h"
#include "custom_MPU9250.h"


CustomBMP280 bmp;

void setup()
{
  Serial.begin(115200);
  bmp.init();
}

void loop()
{
  float altitude = bmp.getAltitude();
  float pressure = bmp.getPressure();
  float temperature = bmp.getTemperature();

  // Print values or use them as needed
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.print(" meters");

  Serial.print("\tPressure: ");
  Serial.print(pressure);
  Serial.print(" Pa");

  Serial.print("\tTemperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

}
