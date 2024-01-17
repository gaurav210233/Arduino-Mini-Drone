#ifndef CUSTOM_MPU9250_H
#define CUSTOM_MPU9250_H

#include <MPU9250.h>

#if defined GYRO_250DPS
#define GYRO_SCALE mpu9250.GYRO_RANGE_250DPS
#define GYRO_SCALE_FACTOR 131.0
#elif defined GYRO_500DPS
#define GYRO_SCALE mpu9250.GYRO_RANGE_500DPS
#define GYRO_SCALE_FACTOR 65.5
#elif defined GYRO_1000DPS
#define GYRO_SCALE mpu9250.GYRO_RANGE_1000DPS
#define GYRO_SCALE_FACTOR 32.8
#elif defined GYRO_2000DPS
#define GYRO_SCALE mpu9250.GYRO_RANGE_2000DPS
#define GYRO_SCALE_FACTOR 16.4
#else
// Default values if none of the options are defined
#define GYRO_SCALE mpu9250.GYRO_RANGE_250DPS
#define GYRO_SCALE_FACTOR 131.0
#endif

#if defined ACCEL_2G
#define ACCEL_SCALE mpu9250.ACCEL_RANGE_2G
#define ACCEL_SCALE_FACTOR 16384.0
#elif defined ACCEL_4G
#define ACCEL_SCALE mpu9250.ACCEL_RANGE_4G
#define ACCEL_SCALE_FACTOR 8192.0
#elif defined ACCEL_8G
#define ACCEL_SCALE mpu9250.ACCEL_RANGE_8G
#define ACCEL_SCALE_FACTOR 4096.0
#elif defined ACCEL_16G
#define ACCEL_SCALE mpu9250.ACCEL_RANGE_16G
#define ACCEL_SCALE_FACTOR 2048.0
#else
// Default values if none of the options are defined
#define ACCEL_SCALE mpu9250.ACCEL_RANGE_2G
#define ACCEL_SCALE_FACTOR 16384.0
#endif

#ifndef USE_SR
#define USE_SR 0
#endif

class CustomMPU9250
{
public:
    void init();
    void calibrateMagnetometer();
    void calculate_IMU_error();
    void getMotion6(float *ax, float *ay, float *az, float *gx, float *gy, float *gz);
    void getMotion9(float *ax, float *ay, float *az, float *gx, float *gy, float *gz, float *mx, float *my, float *mz);
    void getNoErrorIMUdata();

    //Magnetometer calibration parameters - if using MPU9250, uncomment calibrateMagnetometer() in void setup() to get these values, else just ignore these
    float MagErrorX = 0, MagErrorY = 0, MagErrorZ = 0;
    float MagScaleX = 1, MagScaleY = 1, MagScaleZ = 1;

    //IMU calibration parameters - calibrate IMU using calculate_IMU_error() in the void setup() to get these values, then comment out calculate_IMU_error()
    float AccErrorX = 0.0, AccErrorY = 0.0, AccErrorZ = 0.0;
    float GyroErrorX = 0.0, GyroErrorY = 0.0, GyroErrorZ = 0.0;

    //Read values
    float AccX, AccY, AccZ;
    float GyroX, GyroY, GyroZ;
    float MagX, MagY, MagZ;

private:
    MPU9250 mpu9250;
};

#endif // CUSTOM_MPU9250_H
