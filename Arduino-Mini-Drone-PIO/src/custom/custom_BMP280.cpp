#include "custom_BMP280.h"

void CustomBMP280::init(uint8_t deviceAddress)
{
    bme.begin(deviceAddress);
}

/*!
 * @brief Calculates the approximate altitude using barometric pressure and the
 * supplied sea level hPa as a reference.
 * @param seaLevelhPa
 *        The current hPa at sea level.
 * @return The approximate altitude above sea level in meters.
 */
float CustomBMP280::getAltitude(float seaLevelhPa)
{
    return bme.readAltitude(seaLevelhPa);
}

/*!
 * Reads the barometric pressure from the device.
 * @return Barometric pressure in Pa.
 */
float CustomBMP280::getPressure()
{
    return bme.readPressure();
}

/*!
 * Reads the temperature from the device.
 * @return The temperature in degrees celsius.
 */
float CustomBMP280::getTemperature()
{
    return bme.readTemperature();
}