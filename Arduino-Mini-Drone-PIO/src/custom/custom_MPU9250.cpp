#include "custom_MPU9250.h"

void CustomMPU9250::init()
{
    int status = mpu9250.begin();

    if (status < 0)
    {
        Serial.println("MPU9250 initialization unsuccessful");
        Serial.println("Check MPU9250 wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
        while (1)
        {
            // Loop indefinitely if initialization fails
        }
    }

    // From the reset state, all registers should be 0x00, so we should be at
    // max sample rate with digital low pass filter(s) off. All we need to
    // do is set the desired full-scale ranges
    mpu9250.setGyroRange(GYRO_SCALE);
    mpu9250.setAccelRange(ACCEL_SCALE);
    mpu9250.setSrd(USE_SR); // Sets gyro and accel read to 1kHz, magnetometer read to 100Hz
    mpu9250.setMagCalX(MagErrorX, MagScaleX);
    mpu9250.setMagCalY(MagErrorY, MagScaleY);
    mpu9250.setMagCalZ(MagErrorZ, MagScaleZ);
}

void CustomMPU9250::calibrateMagnetometer()
{
    float success;
    Serial.println("Beginning magnetometer calibration in");
    Serial.println("3...");
    delay(1000);
    Serial.println("2...");
    delay(1000);
    Serial.println("1...");
    delay(1000);
    Serial.println("Rotate the IMU about all axes until complete.");
    Serial.println(" ");
    success = mpu9250.calibrateMag();
    if (success)
    {
        Serial.println("Calibration Successful!");
        Serial.print("float MagErrorX = ");
        Serial.print(mpu9250.getMagBiasX_uT());
        Serial.println(";");
        Serial.print("float MagErrorY = ");
        Serial.print(mpu9250.getMagBiasY_uT());
        Serial.println(";");
        Serial.print("float MagErrorZ = ");
        Serial.print(mpu9250.getMagBiasZ_uT());
        Serial.println(";");
        Serial.print("float MagScaleX = ");
        Serial.print(mpu9250.getMagScaleFactorX());
        Serial.println(";");
        Serial.print("float MagScaleY = ");
        Serial.print(mpu9250.getMagScaleFactorY());
        Serial.println(";");
        Serial.print("float MagScaleZ = ");
        Serial.print(mpu9250.getMagScaleFactorZ());
        Serial.println(";");
        Serial.println(" ");
        Serial.println("If you are having trouble with your attitude estimate at a new flying location, repeat this process as needed.");
    }
    else
    {
        Serial.println("Calibration Unsuccessful. Please reset the board and try again.");
    }
    while (1); // Halt code so it won't enter main loop until this function commented out
}
