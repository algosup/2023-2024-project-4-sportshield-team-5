#ifndef _BATTERY_
#define _BATTERY_
#include "definitions.h"

/*
    This file contains every functions related to the battery management.
*/

//-------------------------- VARIABLES ---------------------------
float battery;
float Batterypercentage[50][2] = {
    {100.0, 4.2},
    {95.0, 4.15},
    {90.0, 4.08},
    {85.0, 4.02},
    {80.0, 3.98},
    {75.0, 3.95},
    {70.0, 3.91},
    {65.0, 3.87},
    {60.0, 3.85},
    {55.0, 3.84},
    {50.0, 3.82},
    {45.0, 3.80},
    {40.0, 3.79},
    {35.0, 3.77},
    {30.0, 3.75},
    {25.0, 3.73},
    {20.0, 3.71},
    {15.0, 3.69},
    {10.0, 3.61},
    {5.0, 3.27}

};

//-------------------------- FUNCTIONS ---------------------------

/**
 * This function gets the battery level and returns a percentage.
 * @param None
 * @result An int representing the remaining percentage of the battery.
 */
int getBatteryLevel()
{
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the charge level of a battery.
  */

  battery = analogRead(PIN_VBAT);

  return battery;
}

/**
 * This function puts the device into a deep sleep mode, deactivating everything after sending a last notification to the app containing the battery level and the geolocalisation.
 * @param None
 * @result None.
 */
void deepSleepMode()
{
  int battery = getBatteryLevel();
  // send battery level and GPS location of the device
  // HERE!!!
  digitalWrite(aimant_pin, LOW);
  digitalWrite(SIM800_RST_PIN, LOW);
  digitalWrite(GPS_WKUP_PIN, LOW);

  while (true)
  {
    if (!digitalRead(P0_17))
    {
      break;
    }
  }
  gpsSetup();
  imuSetup();
  simSetup();
}

#endif