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
//GPS
#include <Adafruit_GPS.h>
//SIM
#include "SIM800L.h"