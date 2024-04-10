
//------------------------------- INCLUDES --------------------------------------
#include "definitions.h" // -> libraries' inclusion, the global variables and structures
#include "bluetooth.h"   // -> bluetooth functions and setup
#include "detection.h"   // -> distubtion's detection and specific movement detection and setup
#include "alarm.h"       // -> buzzer and alarm setup and functions and setup
#include "power.h"       // -> battery's and power modes' functions and setup
#include "lock.h"        // -> Electro magnetic lock functions and setup
#include "sim.h"         // -> GPRS functinos with the 2G SIM and setup
#include "gps.h"         // -> GPS module's functions and setup
#include "nfc.h"         // -> NFC detection's and authentification's functions and setup

//-------------------------------- SETUP ----------------------------------------
void setup()
{
  delay(1000);
  Serial.println("SETUP\n");
  delay(1000);

  // debug led initialization
  Serial.print("setup debug red LED ... ");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LEDR, HIGH);
  Serial.println("done !\n");

  // power bridge and battery switch setup
  Serial.print("setup power bridge & battery switches ... "); 
  powerSwitchesSetup();
  Serial.println("done !\n");
  
  //Alarm setup
  Serial.print("Setup alarm ... "); 
  alarmSetup();
  Serial.println("done !\n");

  //EML setup
  Serial.print("Setup electro-magnetic lock ... ");
  lockSetup();
  Serial.println("done !\n");
  
  // change baudrate
  Serial.begin(115200); //Serial initialization
  if (!Serial)
    delay(1000);

  //Bluetooth setup
  Serial.println("setup bluetooth ... ");
  bluetoothSetup();
  Serial.println("bluetooth setup done !\n");

  // IMU setup
  Serial.println("setup IMU ... ");
  imuSetup();
  Serial.println("IMU Setup done !\n");

  // GPS setup
  Serial.print("GPS Setup ... ");
  gpsSetup();
  Serial.println("done !\n");

  // SIM setup
  Serial.print("SIM Setup ... ");
  Serial2.begin(9600);
  delay(100);
  sim800l = new SIM800L((Stream *)&Serial2, SIM800_RST_PIN, 200, 512);
  pinMode(SIM800_DTR_PIN, OUTPUT);
  delay(1000);
  simSetup();
  Serial.println("done !\n");

  // battery charging current setup
  Serial.println("setup battery ... ");
  batterySetup();
  Serial.println("done !\n");

  // Timer setup
  Serial.println ("setup timer ... ");
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, timerHandler)) // Interval in microsecs
  {
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(millis());
  }
  ISR_Timer.setInterval(TIMER_INTERVAL_120S, GPSIsr);
  Serial.println("timer setup done !\n");

  //end of the setup
  Serial.begin(9600);
  Serial.setTimeout(10); //time for reading a string input
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  catchCurrentTime();
  Serial.println("\nSETUP DONE !\n");
}

//--------------------------------------------------- LOOP --------------------------------------------------------------
void loop()
{
  // -------------DATA update about the device-----------------------------------------------
  /*
  // With the final hardware : 
  Device.is_charging = !digitalRead(CHARGING_PIN); // as 0 : not charging and 1 : charging
  Device.is_locked = digitalRead(CONTACT_LOCK_PIN);
  Device.battery_level = getBatteryLevel();
  */

  if (Serial.available() > 0) {
    String str = Serial.readString();

    if (str=="plug"){
      Device.is_charging = true;
      Device.power_mode = NORMAL_MODE;

    }else if(str=="unplug"){
      Device.is_charging = false;
      Serial.print("unplugged");
      
    }else if(str=="lock"){
      Device.is_locked = true;
      
    }else if(str=="bluetooth unlock"){
      if (Device.bluetooth_activated){
        Device.is_locked = false;
        Serial.println("unlocked");
      }else{
        Serial.println("bluetooth disabled");
      }
      
    }else if(str=="nfc unlock"){
      if (Device.nfc_activated){
        Device.is_locked = false;
        Serial.println("unlocked");
      }else{
        Serial.println("NFC disabled");
      }
    
    // weither input = "5%" or "76%", it will set this percentage to the device current information treated after
    }else if (str.charAt(str.length()-1)=='%'){
      str.setCharAt((str.length()-1), '0');
      Device.battery_level = str.toInt()/10;
    }
  }
  //---------------------------------------------------------------------------------------

  //------------Algorithm------------------------------------------------------------------
  
  // Fit the power mode consumption
  if (!Device.is_charging){
    if (Device.power_mode == DEEP_ECO_MODE){
      if (Device.battery_level >= LIGHT_ECO_MODE_BATT_LEVEL){
        turnDeepEco(OFF);
      }
      loop(); //go-back to the beginning of the loop
    }else if(Device.power_mode == LIGHT_ECO_MODE){
      //turn on nfc
      checkNfc();
    }else if(Device.power_mode == NORMAL_MODE){
      if (getAcceleration() > ACCELERATION_MOVEMENT_THRESHOLD || getRotation() > ROTATION_MOVEMENT_THRESHOLD){
        while(checkSpecialMovementTrajectory() && !movement_finished){
          //check again until one of these conditions is false
        }
        if (movement_finished){
          turnSleepMode(OFF);
        }else{
          loop();
        }
      }else{
        loop();
      }
    }else{
      //turn on bluetooth and NFC
      //try ton connect with bluetooth
      checkNfc();
    }
  }

  // Fit the right activity according to the battery level
  if(Device.is_charging){
    adjustChargingCurrent();
    if (Device.is_locked){
      unlock();
    }
    Device.power_mode = DEEP_ECO_MODE;
  }else if (Device.battery_level <= DEEP_ECO_MODE_BATT_LEVEL){
    turnDeepEco(ON);
  }else if (!Device.is_locked){
    if (Device.battery_level <= LIGHT_ECO_MODE_BATT_LEVEL){
      turnDeepEco(ON);
      loop();
    }else{
      if (waiting_for_sleep_mode_time_ref != 0){
        if(getWaitingForSleepTimer() >= SLEEP_MODE_DELAY){
          turnSleepMode(ON);
          loop();
        }
        loop();
      }else{
        lauchWaitingForSleepTimer();
        loop();
      }
    }
  }else{
    if (Device.battery_level <= LIGHT_ECO_MODE_BATT_LEVEL){
      turnLightEco(ON);
    }else{
      turnLightEco(OFF);
    }
    if (getAcceleration() > ACCELERATION_NOISE_THRESHOLD || getRotation() > ROTATION_NOISE_THRESHOLD){

      if (getSmallAlarmTimer() == 0){
        launchSmallAlarm();
      }else if (getSmallAlarmTimer() <= SHORT_SHOCK_DURATION){
        updateAlarm(); 

      }else if (getSmallAlarmTimer() >= SHORT_SHOCK_DURATION){
        delay(100); //to see if it did calm down
        if (getAcceleration() > ACCELERATION_NOISE_THRESHOLD || getRotation() > ROTATION_NOISE_THRESHOLD){
          if (getBigAlarmTimer() == 0){
            resetSmallAlarm();
            launchBigAlarm();
            sendMovement();
            LaunchRegularSent(); 
          }else if (getBigAlarmTimer() <= LONG_ALARM_DURATION){
            updateAlarm();
            updateRegularSent();
          }else{
            resetRegularSent();
            resetBigAlarm();
          }
        }else{
          resetRegularSent();
          resetSmallAlarm();
        }
      }
    }
  }

  if ((Device.power_mode != DEEP_ECO_MODE) && (Device.power_mode != SLEEP_MODE) && Device.is_locked){
    uint sending_timelapse = millis()-time_of_the_last_sent;
    if (sending_timelapse >= frequency_for_sending_data*60000) {
      sendLocationBattery();
      time_of_the_last_sent = millis();
    }
  }
/*

  // capture clocked GPS data
  GPS.read();
  if (GPS.newNMEAreceived())
  {
    Serial.print(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      Serial.println("fail to parse");
    // we can fail to parse a sentence in which case we should just wait for another
  }

  if (GPS.fix && position_acquired == false)
  { // if location detected
    Serial.println("fix + false");
    position_acquired = true;
    GPS.fix = 0;
    digitalWrite(GPS_WKUP_PIN, LOW);
    GPS.sendCommand("$PMTK225,4*2F"); // send to backup mode
  }

  
  if (send_position)
  {
    sendPosition();
  }
*/
} 

//------------- ADDITIONAL FUNCTIONS ------------------------------


void sendMovement(void) //send by GPRS to the app that a motion is detected
{
  /*
  // sending of positions via SIM module
  Serial.println("Envoi detection mouvement");
  sim800l->setupGPRS("iot.1nce.net");
  sim800l->connectGPRS();
  String Route = "http://141.94.244.11:2000/sendNotfication/" + BLE.address();
  String RouteCoord = "http://141.94.244.11:2000/updateCoordinate/" + BLE.address();
  String str = "{\"latitude\": \" " + convertDMMToDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMToDD(String(float(GPS.longitude), 4)) + "\"}";
  String bat = "{\"latitude\": \" " + convertDMMToDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMToDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(Device.battery_level) + "\"}";
  char position[200];
  char posbat[200];
  str.toCharArray(position, str.length() + 1);
  // Serial.println(str);
  bat.toCharArray(posbat, bat.length() + 1);
  Serial.println(posbat);
  char direction[200];
  char directionCoord[200];
  Route.toCharArray(direction, Route.length() + 1);
  RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
  sim800l->doPost(direction, "application/json", position, 10000, 10000);
  sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
  sim800l->disconnectGPRS();
  */
}

void sendPosition()
{
  // regular sending of positions via SIM module
  Serial.println("Envoi regulier position");
  sim800l->setupGPRS("iot.1nce.net");
  sim800l->connectGPRS();
  String RouteCoord = "http://141.94.244.11:2000/updateCoordinate/" + BLE.address();
  String bat = "{\"latitude\": \" " + convertDMMToDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMToDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(Device.battery_level) + "\"}";
  char posbat[200];
  bat.toCharArray(posbat, bat.length() + 1);
  Serial.println(posbat);
  Serial.println(RouteCoord);
  char directionCoord[200];
  RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
  sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
  sim800l->disconnectGPRS();
  send_position = false;
}

void catchCurrentTime(void)
{
  unsigned long millisPassed = millis();
  unsigned int seconds = (millisPassed / 1000) % 60;
  unsigned int minutes = (millisPassed / (1000 * 60)) % 60;
  unsigned int hours = (millisPassed / (1000 * 60 * 60)) % 24;
  Serial.print("Current Time : ");
  Serial.print(hours);
  Serial.print("h");
  Serial.print(minutes);
  Serial.print("mn");
  Serial.print(seconds);
  Serial.println("s");
}

void timerHandler()
{
  ISR_Timer.run();
}
