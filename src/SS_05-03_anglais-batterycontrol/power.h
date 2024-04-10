#ifndef _POWER_
#define _POWER_
#include "definitions.h"

/*
    This file contains every functions related to the battery management.
*/

//-------------------------- VARIABLES ---------------------------
float battery;
// The values used for this table are taken from this source: https://blog.ampow.com/lipo-voltage-chart/
float battery_percentages[20][2] = {
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

//------------------------------------------------------- FUNCTIONS ------------------------------------------------------

//-------------------------------BATTERY----------------------------------


/**
 * This function gets the battery level and returns a percentage with 5% resolution ased on a array of correspondances.
 * @param None
 * @result An int representing the remaining percentage of the battery with a 5% resolution.
 */
int getBatteryLevel()
{
  int current_battery_level = Device.battery_level;
  // Read the current voltage of the voltage divider bridge on the VBAT pin.
  int bridge_voltage = analogRead(PIN_VBAT);
  float battery_voltage = ((510e3 + 1000e3) / 510e3) * analog_read_ref * bridge_voltage / pow(2,ANALOG_READ_RESOLUTION); //according to the 2 resistances of 510Kohm and 1Mohm
  for (int i=20; i--; i>0){
    if (battery_percentages[i-1][1] <= battery_voltage){
      int percentage = battery_percentages[i-1][0];
      return percentage;
    }
  }
  return current_battery_level;
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
//---------------------------------------------------------------------------

//---------------------------------POWER MODES-------------------------------
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

//-----------------------------------------------------------------------------------

//-----------Power switches (for SIM, Alarm and EML power supply control) ------------

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

void batterySetup(){
  analogReadResolution(ADC_RESOLUTION); // setup battery reading
  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  analogReference(ANALOG_READ_REFERENCE);
  analogReadResolution(ANALOG_READ_RESOLUTION);
  digitalWrite(VBAT_ENABLE, LOW);
  pinMode(POWER_CHARGING_CONTROL, OUTPUT);
  setChargingCurrent(HIGH);
  pinMode(CHARGING_PIN, INPUT);
  Device.is_charging = !digitalRead(CHARGING_PIN);
  Device.battery_level = 50;//getBatteryLevel(); //WARNING, TEST !!!!!!!!!!!!!!!
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