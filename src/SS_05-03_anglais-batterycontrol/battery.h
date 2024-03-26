#ifndef _BATTERY_
#define _BATTERY_
#include "global.h"

/*
    This file contains every functions related to the battery management.
*/

//-------------------------- FUNCTIONS ---------------------------

/**
 * This function gets the battery level and returns a percentage.
 * @param None
 * @result An int representing the remaining percentage of the battery.
 */
int getBatteryLevel(void)
{
    int battery = analogRead(PIN_VBAT);
    int batteryLevel = map(battery, 0, 1023, 0, 100);

    return batteryLevel;
}

/**
 * This function puts the device into a deep sleep mode, deactivating everything after sending a last notification to the app containing the battery level and the geolocalisation.
 * @param None
 * @result None.
 */
void deepSleepMode()
{
    int battery = getBatteryLevel();
    // HERE
    // send battery level and GPS location of the device
    digitalWrite(aimantPin, LOW);
    digitalWrite(SIM800_RST_PIN, LOW);
    digitalWrite(GPS_WKUP_PIN, LOW);

    while (battery < 20)
    {

        battery = getBatteryLevel();
        delay(1000);
    }
    gps_setup();
    sim_setup();
}

#endif