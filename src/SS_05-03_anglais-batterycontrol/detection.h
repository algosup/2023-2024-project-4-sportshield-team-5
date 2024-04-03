#ifndef _MOTION_
#define _MOTION_
#include "definitions.h"

/*
    This file contains every functions related to the detection of movements.
*/

//---------------------------- SETUP -----------------------------

/**
 * This function starts the Inertial Movement Units to enable the movement detection.
 * @param None
 * @result A print appear to declare if an error has been encountered or not.
 */
void imuSetup(void)
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
    static float previous_acceleration = 0;
    float accelX = imu.readFloatAccelX();
    float accelY = imu.readFloatAccelY();
    float accelZ = imu.readFloatAccelZ();

    float current_acceleration = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ) * 100;
    float motion_dataerence = current_acceleration - previous_acceleration; // Calculate the acceleration difference
    previous_acceleration = current_acceleration;

    return fabs(motion_dataerence); // returns a value always positive
}

/**
 * This function provides the absolute difference in acceleration between consecutive calls, helping to monitor changes in motion over time.
 * @param None
 * @result The float value of the detected rotation.
 */
float getRotationData()
{
    static float previous_rotation = 0;

    // Read gyroscope values
    float gyroX = imu.readFloatGyroX();
    float gyroY = imu.readFloatGyroY();
    float gyroZ = imu.readFloatGyroZ();

    float current_rotation = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ); // Calculate the current rotation based on gyroscope readings
    float rotation_dataerence = current_rotation - previous_rotation;             // Calculate the difference in rotation
    previous_rotation = current_rotation;                                         // Update the previous rotation value

    return fabs(rotation_dataerence);
}

#endif