#ifndef _MOTION_
#define _MOTION_
#include "global.h"

/*
    This file contains every functions related to the detection of movements.
*/

//---------------------------- SETUP -----------------------------

/**
 * This function starts the Inertial Movement Units to enable the movement detection.
 * @param None
 * @result A print appear to declare if an error has been encountered or not.
 */
void imu_setup(void)
{
    if (!imu.begin())
    {
        Serial.println("Device error");
    }
    else
    {
        Serial.println("Accelerometer launched");
    }
}

//-------------------------- FUNCTIONS ---------------------------
/**
 * This function provides the absolute difference in acceleration between consecutive calls, helping to monitor changes in motion over time.
 * @param None
 * @result The float value of the detected motion.
 */
float getMotionData(void)
{
    static float previousAcceleration = 0;
    float accelX = imu.readFloatAccelX();
    float accelY = imu.readFloatAccelY();
    float accelZ = imu.readFloatAccelZ();

    float currentAcceleration = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ) * 100;
    float MotionDataerence = currentAcceleration - previousAcceleration; // Calculate the acceleration difference
    previousAcceleration = currentAcceleration;

    return fabs(MotionDataerence); // returns a value always positive
}

/**
 * This function provides the absolute difference in acceleration between consecutive calls, helping to monitor changes in motion over time.
 * @param None
 * @result The float value of the detected rotation.
 */
float getRotationData()
{
    static float previousRotation = 0;

    // Read gyroscope values
    float gyroX = imu.readFloatGyroX();
    float gyroY = imu.readFloatGyroY();
    float gyroZ = imu.readFloatGyroZ();

    float currentRotation = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ); // Calculate the current rotation based on gyroscope readings
    float RotationDataerence = currentRotation - previousRotation;               // Calculate the difference in rotation
    previousRotation = currentRotation;                                          // Update the previous rotation value

    return fabs(RotationDataerence);
}

#endif