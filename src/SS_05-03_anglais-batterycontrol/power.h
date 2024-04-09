#ifndef _POWER_
#define _POWER_
#include "definitions.h"

/*
    This file contains every functions related to the battery management.
*/

//-------------------------- VARIABLES ---------------------------
float battery;
// The values used for this table are taken from this source: https://blog.ampow.com/lipo-voltage-chart/
float Batterypercentage[50][2] = {
    {100.0, 4.2},
    {95.0, 4.15},
    {90.0, 4.11},
    {85.0, 4.08},
    {80.0, 3.02},
    {75.0, 3.98},
    {70.0, 3.95},
    {65.0, 3.91},
    {60.0, 3.87},
    {55.0, 3.85},
    {50.0, 3.84},
    {45.0, 3.82},
    {40.0, 3.80},
    {35.0, 3.79},
    {30.0, 3.77},
    {25.0, 3.75},
    {20.0, 3.73},
    {15.0, 3.71},
    {10.0, 3.69},
    {5.0, 3.61}

};

//-------------------------- FUNCTIONS ---------------------------

/**
 * This function gets the battery level and returns a percentage.
 * @param None
 * @result An int representing the remaining percentage of the battery.
 */
int getBatteryLevel()
{
  // Read the current voltage level on the VBAT pin.
  battery = analogRead(PIN_VBAT);
  battery = 50;
  return battery;
}

/**
 * This function puts the device into a deep sleep mode, deactivating everything after sending a last notification to the app containing the battery level and the geolocalisation.
 * @param None
 * @result None.
 */
void deepSleepMode()
{
  /*// send battery level and GPS location of the device
  // HERE!!!
  digitalWrite(EML_PIN, LOW);
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
  simSetup();*/
}

//Power switches are for SIM, Alarm and EML power supply control

/**
 * Switch on or off the voltage booster and the battery alimentation of them for SIM, EML ad alarm
 * @param state ON or OFF
 */
void turnPowerSwitches(int state){
  digitalWrite(POWER_BOOST_SWITCH_PIN, state);
  digitalWrite(BATTERY_SWITCH_PIN, state);
}

void powerSwitchesSetup(){
  pinMode(POWER_BOOST_SWITCH_PIN, OUTPUT);
  pinMode(BATTERY_SWITCH_PIN, OUTPUT);
  turnPowerSwitches(ON);
}

/**
 * Switch the intensity of the battery charging current to 100mA for HIGH or to 50ma for LOW
 * @param intensity HIGH or LOW
 */
void setChargingCurrent(int intensity){
  if (intensity==LOW){
    digitalWrite(POWER_CHARGING_CONTROL, HIGH);
    Device.charging_current = 50;
  }else{
    digitalWrite(POWER_CHARGING_CONTROL, LOW);
    Device.charging_current = 100;
  }
  
}

void batterySetup(){
  analogReadResolution(ADC_RESOLUTION); // setup battery reading
  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  digitalWrite(VBAT_ENABLE, LOW);
  pinMode(POWER_CHARGING_CONTROL, OUTPUT);
  setChargingCurrent(HIGH);
  Device.is_charging = !digitalRead(CHARGING_PIN);
  Device.battery_level = getBatteryLevel();
  Serial.print("Battery level: ");
  Serial.print(Device.battery_level);
  Serial.println(" %");
  if (Device.is_charging){
    Serial.print("Currently charging at ");
    Serial.print(Device.charging_current);
    Serial.println(" mA");
  }
  
}

#endif