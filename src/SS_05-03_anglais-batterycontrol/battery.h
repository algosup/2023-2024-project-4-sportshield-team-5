#ifndef _BATTERY_
#define _BATTERY_
#include "definitions.h"

/*
    This file contains every functions related to the battery management.
*/

float battery;
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
  float batteryLevel = map(battery, 0, 1023, 0, 100);
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