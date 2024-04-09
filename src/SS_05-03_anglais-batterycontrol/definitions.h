#ifndef _DEFINITIONS_
#define _DEFINITIONS_

//--------------------------- INCLUDES ---------------------------
#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0
#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"
#include <Arduino.h>
// BLE
#include <ArduinoBLE.h>
// IMU
#include <LSM6DS3.h>
#include <Wire.h>
// GPS
#include <Adafruit_GPS.h>
// SIM
#include "SIM800L.h"


//-------------------------- STRUCTURES --------------------------

// Config
struct myConfig 
{
  short int pin; //unknown feature
  String Name; //
  bool is_locked; //if the security is activated
  bool is_triggered;
  bool is_charging;
  short int battery_level; // battery level in percentage (5% resolution)
  bool is_bluetooth_activated;
  bool is_gps_activated;
  bool power_mode;
};

//----------------------- GLOBAL VARIABLES -----------------------
myConfig Device;

bool is_authenticate = false;

// Timer
#define HW_TIMER_INTERVAL_MS 1
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
NRF52_MBED_ISRTimer ISR_Timer;
#define TIMER_INTERVAL_120S 120000L

// IMU : LSM6DS3
LSM6DS3 imu(I2C_MODE, 0x6A); // I2C device address 0x6A
uint32_t timer_imu = millis();
bool motion_big = false;
bool motion_small = false;
bool motion_detect = false;

// GPS PA1010D
Adafruit_GPS GPS(&Serial1);
bool start_gps = false;
bool position_acquired = false;
uint32_t timer = millis();
#define GPS_WKUP_PIN D8

// SIM800L GSM 2G Module
UART Serial2(D0, D1, NC, NC);
#define SIM800_RST_PIN A5
#define SIM800_DTR_PIN A5
#define TIME_OUT_MS_BLE_ACT 5000 // 300s 300000 times in ms or bluetooth enabled to allow connection following motion detection. (value 5000 for 5s tests)
SIM800L *sim800l;
bool send_position = false;
bool send_move = false;

// Buzzer
#define BUZZER_PIN D2
void pulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff, int intensity);
unsigned long start_cycle = 0;

// Electro magnetic lock
#define EML_PIN D3

bool deactivate = false; // A boolean which if turned on, stop any ongoing alarms. Activated by bluetooth
// Set a threshold to determine a "small" or "big" movement

float small_MT = 5000.0; //     SmallMotionThreshold
float big_MT = 7000.0;   //    BigMotionThreshold

float small_RT = 45.0; //     SmallRotationThreshold
float big_RT = 100.0;  //     BigRotationThreshold

// Alarm
float time_limit = 1.5;       // The maximum time margin where two shocks can be detected as a risk, unit in seconds
float alarm_start;            // A value to store when the alarm started
float alarm_duration;         // The duration of the current alarm;
int MT_counter;               // Number of movements detected within the time limit value
bool first_alarm = true;      // A boolean which indicates if it is the first alarm in a given time
bool activation_alarm = true; // A boolean to signal the activation of the product

float getBatteryVoltage();

float motion_data;
float rotation_data;

unsigned long start_cooldown = 0; // check point for millis aided cooldown

// BATTERY AND SWITCH PINS
#define VBAT_ENABLE 14
#define POWER_CHARGING_CONTROL P0_13 //if this pin is H/L -> 50/100mA to charge
#define POWER_BOOST_SWITCH_PIN D4
#define BATTERY_SWITCH_PIN D9

// POWER MODES
#define NO_MODE 0
#define SLEEP_MODE 1// High 'battery save', while device not used (awaken by special movement)
#define LIGHT_ECO_MODE 2 //'Light sleep mode' or 'ECO mode' when low battery (can't lock anymore, begin to save battery)
#define DEEP_ECO_MODE 3//when really low battery (survivor mode)
#define LIGHT_SLEEP_MODE_BATT_LEVEL 15 //%
#define DEEP_SLEEP_MODE_BATT_LEVEL 5 //%

#endif //DEFINITIONS