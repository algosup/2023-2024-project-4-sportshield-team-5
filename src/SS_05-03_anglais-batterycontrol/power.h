#ifndef _POWER_
#define _POWER_
#include "definitions.h"
#include "bluetooth.h"

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

//----------------------------------------------------------------------------------

//---------------------------------POWER MODES--------------------------------------
/**
 * This function puts the device into a deep eco mode, deactivating everything after sending a last notification to the app containing the battery level and the geolocalisation.
 * @param state turn 'ON' or 'OFF'
 * @result None.
 */
void turnDeepEco(bool state)
{
  if (state==ON){

    // Send a notification to warn the user by GPRS on the app that :
    //- Can't use anymore
    //- Can only use it again by rechharging it
    //- Completely out of battery

    Device.power_mode = DEEP_ECO_MODE;
    Device.bluetooth_activated = false;
    Device.nfc_activated = false;
    Device.gps_activated = false;

    turnPowerSwitches(OFF); // cut current of SIM, Alarm and EML
    digitalWrite(SIM800_RST_PIN, LOW);
    digitalWrite(GPS_WKUP_PIN, LOW);
    //BLE_activated = false;
    BLE.end();
    //turn off the IMU
  }
  if (state==OFF){
    Device.power_mode = NORMAL_MODE;
    Device.bluetooth_activated = true;
    Device.nfc_activated = true;
    Device.gps_activated = true;

    //turn on the IMU
    //BLE_activated = true;
    bluetoothSetup();
    BLE.poll();
  }
}

/**
 * This function puts the device into a light eco mode, deactivating bluetooth, keeping only NFC. It will finish the lock cycle a last time and send GPRS data only every 30 mins
 * @param state turn 'ON' or 'OFF'
 * @result None.
 */
void turnLightEco(bool state)
{
  if (state==ON){

    // Send a notification to warn the user by GPRS on the app that :
    // - Can't lock the device the next time, if not recharged
    // - Can unlock only with NFC
    // - Need to charge ! (but will still work until the end of the lock cycle)

    frequency_for_sending_data = 30; //minutes

    Device.power_mode = LIGHT_ECO_MODE;
    Device.bluetooth_activated = false;
    Device.nfc_activated = true;

    //BLE_activated = false;
    BLE.end();
    // to keep only NFC

  }
  if (state==OFF){

    frequency_for_sending_data = 15;

    Device.power_mode = NORMAL_MODE;
    Device.bluetooth_activated = true;

    //BLE_activated = true;
    bluetoothSetup();
    BLE.poll();

  }
}

/**
 * This function puts the device into sleep mode, deactivating everything except IMU to detect a specifi movement.
 * @param state turn 'ON' or 'OFF'
 * @result None.
 */
void turnSleepMode(bool state)
{
  if (state==ON){

    // Send a notification to warn the user by GPRS on the app that :
    //- Use the specific movement or recharge to awake it
    waiting_for_sleep_mode_time_ref = 0;
    Device.power_mode = SLEEP_MODE;
    Device.bluetooth_activated = false;
    Device.nfc_activated = false;
    Device.gps_activated = false;

    turnPowerSwitches(OFF); // cut current of SIM, Alarm and EML
    digitalWrite(SIM800_RST_PIN, LOW);
    digitalWrite(GPS_WKUP_PIN, LOW);

    //BLE_activated = false;
    BLE.end();

  }
  if (state==OFF){
    Device.power_mode = NORMAL_MODE;
    Device.bluetooth_activated = true;
    Device.nfc_activated = true;
    Device.gps_activated = true;

    //BLE_activated = true;
    bluetoothSetup();
    BLE.poll();
  }
}
void lauchWaitingForSleepTimer(){
  waiting_for_sleep_mode_time_ref = millis();
}
uint getWaitingForSleepTimer(){
  uint diff = millis() - waiting_for_sleep_mode_time_ref;
  return diff;
}
//-----------------------------------------------------------------------------------

//------------------------------------------BATTERY----------------------------------

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

void adjustChargingCurrent(){
  if (Device.battery_level >= 80){
    setChargingCurrent(LOW);
  }else{
    setChargingCurrent(HIGH);
  }
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

//--------------------------------------------------------------------------------------

#endif