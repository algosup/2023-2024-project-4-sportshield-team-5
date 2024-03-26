#ifndef _GLOBAL_
#define _GLOBAL_

//--------------------------- INCLUDES ---------------------------
#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0
#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"
#include <Arduino.h>
// BLE
#include <ArduinoBLE.h>
#include "struct.h"
// IMU
#include <LSM6DS3.h>
#include <Wire.h>
// GPS
#include <Adafruit_GPS.h>
// SIM
#include "SIM800L.h"

#include "bluetooth.h"

//----------------------- GLOBAL VARIABLES -----------------------
myConfig Config;
bool isAuthenticate = false;
// Timer
#define HW_TIMER_INTERVAL_MS 1
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
NRF52_MBED_ISRTimer ISR_Timer;
#define TIMER_INTERVAL_120S 120000L

// IMU : LSM6DS3
LSM6DS3 imu(I2C_MODE, 0x6A); // I2C device address 0x6A
uint32_t timer_imu = millis();
bool MotionBig = false;
bool MotionSmall = false;
bool MotionDetect = false;

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
const int buzzerPin = D2;
void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff, int intensity);
unsigned long startCycle = 0;
// Electroaimant
const int aimantPin = D3;

bool deactivate = false; // A boolean which if turned on, stop any ongoing alarms. Activated by bluetooth
// Set a threshold to determine a "small" or "big" movement

float SmallMT = 5000.0; //     SmallMotionThreshold
float BigMT = 7000.0;   //    BigMotionThreshold

float SmallRT = 45.0; //     SmallRotationThreshold
float BigRT = 100.0;  //     BigRotationThreshold

// Alarm
float TimeLimit = 1.5;       // The maximum time margin where two shocks can be detected as a risk, unit in seconds
float AlarmStart;            // A value to store when the alarm started
float AlarmDuration;         // The duration of the current alarm;
int MTCounter;               // Number of movements detected within the time limit value
bool FirstAlarm = true;      // A boolean which indicates if it is the first alarm in a given time
bool ActivationAlarm = true; // A boolean to signal the activation of the product

float getBatteryVoltage();

float MotionData;
float RotationData;

unsigned long StartCoolDown = 0; // check point for millis aided cooldown

// batterie
#define VBAT_ENABLE 14

#endif