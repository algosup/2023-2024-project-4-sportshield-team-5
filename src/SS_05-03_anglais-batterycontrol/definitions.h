#ifndef _DEFINITIONS_
#define _DEFINITIONS_

//--------------------------- INCLUDES ---------------------------
#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0
#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"
#include <Arduino.h>
#include <ArduinoBLE.h>// BLE
#include <LSM6DS3.h>// IMU
#include <Wire.h>// IMU
#include <Adafruit_GPS.h>// GPS
#include "SIM800L.h"// SIM

//-------------------------- STRUCTURES --------------------------

// Config for the device state
struct myConfig 
{
  short int pin; //unknown feature
  String Name; // name of the device
  bool is_locked = true; //is the lock activated
  bool alarm_triggered = false; //is the alarm triggered
  bool is_charging = false; // is it plugged and charging
  short int charging_current = 100; //50 or 100 in mA
  short int battery_level = 50; // battery level in percentage (5% resolution)
  bool bluetooth_activated = true; // obvious
  bool gps_activated = false; // obvious
  bool nfc_activated = false;
  bool power_mode = 0; // the different power modes are defined at the end, there are 4 :
                   // 'NORMAL' 'LIGHT Eco mode' 'deep eco mode' and 'sleep mode' Cf. below
};
myConfig Device;

//----------------------- GLOBAL VARIABLES -----------------------

//general
#define TEST_DURATION 1000 //ms -> bip and EML duratios at setup
#define ON HIGH
#define OFF LOW

//LOCKING
#define UNLOCKING_DURATION 1000 //ms EML opened
bool is_authenticate = false;
// pin of the contact button if locked or not
//  #define CONTACT_LOCK_PIN DX

// TIMER
#define HW_TIMER_INTERVAL_MS 1
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
NRF52_MBED_ISRTimer ISR_Timer;
#define TIMER_INTERVAL_120S 120000L

uint32_t waiting_for_sleep_mode_time_ref = 0;
#define SLEEP_MODE_DELAY 4000 //milliseconds //!!!! To modify

// IMU : LSM6DS3
LSM6DS3 imu(I2C_MODE, 0x6A); // I2C device address 0x6A
uint32_t timer_imu = millis();


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
int frequency_for_sending_data = 15; //minutes, each Xminutes, when locked, it sends geolocation and battery level
uint32_t time_of_the_last_sent = 0;

// Buzzer
#define BUZZER_PIN D2
void pulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff, int intensity);
unsigned long start_cycle = 0;
bool long_motion_alarm = false;
bool short_motion_alarm = false;

// Electro magnetic lock
#define EML_PIN D3

bool deactivate = false; // A boolean which if turned on, stop any ongoing alarms. Activated by bluetooth

// MOVEMENTS
#define ACCELERATION_NOISE_THRESHOLD 5000 //     SmallMotionThreshold
#define ACCELERATION_MOVEMENT_THRESHOLD 7000  //    BigMotionThreshold
#define ROTATION_NOISE_THRESHOLD 45.0 //     SmallRotationThreshold
#define ROTATION_MOVEMENT_THRESHOLD 100.0  //     BigRotationThreshold
bool movement_finished = false;

// Alarm
#define SHORT_SHOCK_DURATION 1200      // The maximum time margin where two shocks can be detected as a risk, unit in seconds
#define LONG_ALARM_DURATION 3500
float alarm_start;            // A value to store when the alarm started
float alarm_duration;         // The duration of the current alarm;
int MT_counter;               // Number of movements detected within the time limit value
bool first_alarm = true;      // A boolean which indicates if it is the first alarm in a given time
bool activation_alarm = true; // A boolean to signal the activation of the product

#define SMALL_ALARM_PERIOD 200 //ms
#define SMALL_ALARM_CYCLES  3//ms
#define SMALL_ALARM_INTENSITY 512 //   /1023
uint32_t small_alarm_timer_start = 0;
uint small_alarm_timer = 0;
uint32_t small_alarm_period_timer_start = 0;
uint small_alarm_period_timer = 0;
int small_alarm_cycles = 0;

#define BIG_ALARM_PERIOD 350 //ms
#define BIG_ALARM_CYCLES  5//ms
#define BIG_ALARM_INTENSITY 1023 //   /1023
uint32_t big_alarm_timer_start = 0;
uint big_alarm_timer = 0;
uint32_t big_alarm_period_timer_start = 0;
uint big_alarm_period_timer = 0;
int big_alarm_cycles = 0;

#define SENDING_FREQUENCY_WHEN_LOCKED 1000 //ms
uint32_t regular_sent_timer_start = 0;
uint regular_sent_timer = 0;


float motion_data;
float rotation_data;

unsigned long start_cooldown = 0; // check point for millis aided cooldown

// BATTERY AND SWITCH PINS
#define VBAT_ENABLE 14
//#define PIN_VBAT P0_31 // automatically defined
#define CHARGING_PIN P0_17
#define POWER_CHARGING_CONTROL P0_13 //if this pin is H/L -> 50/100mA to charge
#define POWER_BOOST_SWITCH_PIN D4
#define BATTERY_SWITCH_PIN D9
#define DEFAULT_CHARGING_POWER_CURRENT HIGH
// For that the analogRead function cuts the voltage from 0 to 2.4v in values between 0 and 2^12 :
#define ANALOG_READ_RESOLUTION 12 //bits
#define ANALOG_READ_REFERENCE AR_INTERNAL2V4 //2.4 volts 
const float analog_read_ref = 2.4; //volts

// POWER MODES
#define NORMAL_MODE 0
#define SLEEP_MODE 1// High 'battery save', while device not used (awaken by special movement)
#define LIGHT_ECO_MODE 2 //'Light sleep mode' or 'ECO mode' when low battery (can't lock anymore, begin to save battery)
#define DEEP_ECO_MODE 3//when really low battery (survivor mode)
#define LIGHT_ECO_MODE_BATT_LEVEL 15 //%
#define DEEP_ECO_MODE_BATT_LEVEL 5 //%

#endif //DEFINITIONS