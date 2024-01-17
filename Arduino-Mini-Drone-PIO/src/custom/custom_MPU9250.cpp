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
    while (1)
        ; // Halt code so it won't enter main loop until this function commented out
}

void CustomMPU9250::calculate_IMU_error()
{
    float ax, ay, az;
    float gx, gy, gz;

    AccErrorX = 0.0;
    AccErrorY = 0.0;
    AccErrorZ = 0.0;
    GyroErrorX = 0.0;
    GyroErrorY = 0.0;
    GyroErrorZ = 0.0;

    // Read IMU values 12000 times
    int c = 0;
    while (c < 12000)
    {
        CustomMPU9250::getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        // Sum all readings
        AccErrorX = AccErrorX + ax;
        AccErrorY = AccErrorY + ay;
        AccErrorZ = AccErrorZ + az;
        GyroErrorX = GyroErrorX + gx;
        GyroErrorY = GyroErrorY + gy;
        GyroErrorZ = GyroErrorZ + gz;
        c++;
    }
    // Divide the sum by 12000 to get the error value
    AccErrorX = AccErrorX / c;
    AccErrorY = AccErrorY / c;
    AccErrorZ = AccErrorZ / c - 1.0;
    GyroErrorX = GyroErrorX / c;
    GyroErrorY = GyroErrorY / c;
    GyroErrorZ = GyroErrorZ / c;

    Serial.print("float AccErrorX = ");
    Serial.print(AccErrorX);
    Serial.println(";");
    Serial.print("float AccErrorY = ");
    Serial.print(AccErrorY);
    Serial.println(";");
    Serial.print("float AccErrorZ = ");
    Serial.print(AccErrorZ);
    Serial.println(";");

    Serial.print("float GyroErrorX = ");
    Serial.print(GyroErrorX);
    Serial.println(";");
    Serial.print("float GyroErrorY = ");
    Serial.print(GyroErrorY);
    Serial.println(";");
    Serial.print("float GyroErrorZ = ");
    Serial.print(GyroErrorZ);
    Serial.println(";");

    Serial.println("Paste these values in user specified variables section and comment out calculate_IMU_error() in void setup.");
}

void CustomMPU9250::getMotion6(float *ax, float *ay, float *az, float *gx, float *gy, float *gz)
{
    mpu9250.readSensor();
    *ax = mpu9250.getAccelX_mss();
    *ay = mpu9250.getAccelY_mss();
    *az = mpu9250.getAccelZ_mss();
    *gx = mpu9250.getGyroX_rads();
    *gy = mpu9250.getGyroY_rads();
    *gz = mpu9250.getGyroZ_rads();
}

void CustomMPU9250::getMotion9(float *ax, float *ay, float *az, float *gx, float *gy, float *gz, float *mx, float *my, float *mz)
{
    mpu9250.readSensor();
    *ax = mpu9250.getAccelX_mss();
    *ay = mpu9250.getAccelY_mss();
    *az = mpu9250.getAccelZ_mss();
    *gx = mpu9250.getGyroX_rads();
    *gy = mpu9250.getGyroY_rads();
    *gz = mpu9250.getGyroZ_rads();
    *mx = mpu9250.getMagX_uT();
    *my = mpu9250.getMagY_uT();
    *mz = mpu9250.getMagZ_uT();
}

void CustomMPU9250::getNoErrorIMUdata() // Gives error corrected data
{
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;

    CustomMPU9250::getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

    // Correct the outputs with the calculated error values

    // Accel
    AccX = AccX - AccErrorX;
    AccY = AccY - AccErrorY;
    AccZ = AccZ - AccErrorZ;

    // Gyro
    GyroX = GyroX - GyroErrorX;
    GyroY = GyroY - GyroErrorY;
    GyroZ = GyroZ - GyroErrorZ;

    // Mag
    MagX = (MagX - MagErrorX) * MagScaleX;
    MagY = (MagY - MagErrorY) * MagScaleY;
    MagZ = (MagZ - MagErrorZ) * MagScaleZ;
}
