
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
    
    // if input = "5%" or "76%", it will set the right percentage to the device data
    }else if (str.charAt(str.length()-1)=='%'){
      str.setCharAt((str.length()-1), '0');
      Device.battery_level = str.toInt()/10;
    }
  }
  //---------------------------------------------------------------------------------------

  //------------Algorithm------------------------------------------------------------------

  if (activation_alarm)
  {
    pulseBuzzer(2, 200, 50, 25);
    activation_alarm = false;
  }

  motion_data = getMotionData();
  rotation_data = getRotationData();
  Device.is_locked = 1; // TO REMOVE !!!
  if (Device.is_locked)
  { // alarm enalbled
    activateGPS();
    if (motion_data > big_MT || rotation_data > big_RT)
    { // Big motion detection
      if (motion_data > big_MT)
      {
        Serial.print("Motion detected : ");
        Serial.println(motion_data);
      }
      else
      {
        Serial.print("Rotation detected : ");
        Serial.println(rotation_data);
      }
      motion_big = true;
      motion_small = false;
    }
    else if (motion_data > small_MT || rotation_data > small_RT)
    { // Small motion detection
      if (motion_data > small_MT)
      {
        Serial.print("Small motion: ");
        Serial.println(motion_data);
      }
      else
      {
        Serial.print("Small rota : ");
        Serial.println(rotation_data);
      }
      motion_small = true;
    }
  }

  if ((!motion_small && !motion_big) && ((alarm_duration - alarm_start) < SHORT_SHOCK_DURATION))
  {
    MT_counter = 0;
    first_alarm = true;
  }
  if (motion_small || motion_big)
  {
    MT_counter++;
    if (first_alarm && MT_counter >= 2)
    {
      alarm_start = millis();
    }
    else
    {
      alarm_duration = millis();
      if (alarm_duration - alarm_start >= SHORT_SHOCK_DURATION)
      {
        alarm_start = millis();
      }
    }
  }

  if ((motion_big || motion_small) && MT_counter > 2)
  {
    sendMovement();

    if (first_alarm)
    {
      // Dissuasion alarm
      pulseBuzzer(3, 200, 100, 12); // repetitions, DurationOn , DurationOff, intensity
      first_alarm = false;
    }
    else
    {
      // Theft alarm
      pulseBuzzer(5, 350, 350, 25); // repetitions, DurationOn , DurationOff, intensity
    }
  }
  motion_detect = true;

  // if a mvt is detected and bluetooth is disabled bluetooth activation
  if (motion_detect == true)
  {
    tim_connec = millis();
    motion_detect = false;
    if (BLE_activated == false)
    {
      BLE_activated = true;
      Serial.println("MVT_detect->setup");
      bluetoothSetup();
    }
  }

  // bluetooth actived when we are interacting with the module or when the alarm is on
  if ((BLE_activated == true) || (Device.is_locked))
  {
    BLE.poll(); // communication autorisé
  }

  // at the end of the time during which the lock has not moved, if bluetooth is activated, and the lock is not in activation mode then it is turned off to save the battery
  if ((millis() - tim_connec > TIME_OUT_MS_BLE_ACT) && (BLE_activated == true) && (Device.is_locked != 1))
  {
    BLE_activated = false;
    Serial.println("timeout->BLE_END");
    BLE.end();
  }

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

  if (getBatteryLevel() <= 15) // if Vmin is reached
  {
    Serial.print("Enter sleep mode");
    deepSleepMode();
  }
  if (getBatteryLevel() >= 95) // if Vmax is reached
  {
    // this is a placeholder, it will probably not work if unchanged
    digitalWrite(VBAT_ENABLE, HIGH); // stop the charge
  }
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
  String bat = "{\"latitude\": \" " + convertDMMToDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMToDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryLevel()) + "\"}";
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
  String bat = "{\"latitude\": \" " + convertDMMToDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMToDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryLevel()) + "\"}";
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
