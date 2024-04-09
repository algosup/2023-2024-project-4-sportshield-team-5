
//------------------------------- INCLUDES --------------------------------------
// BLE
#include "bluetooth.h"
// IMU
#include "detection.h"
// GPS
#include "gps.h"
// SIM
#include "sim.h"
// BUZZER
#include "buzzer.h"
// BATTERY
#include "battery.h"
//-------------------------------- SETUP ----------------------------------------
void setup()
{
  pinMode(buzzer_pin, OUTPUT); // setup for buzzer
  digitalWrite(buzzer_pin, HIGH);
  delay(1000);
  digitalWrite(buzzer_pin, LOW);
  Serial.println(" buzzer");

  pinMode(aimant_pin, OUTPUT); // setup electro-aimant
  digitalWrite(aimant_pin, HIGH);
  delay(1000);
  digitalWrite(aimant_pin, LOW);
  Serial.println("electro");

  // debug led initialization
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LEDR, LOW);

  // power bridge control
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);

  // power battery control with the transistor
  pinMode(D9, OUTPUT);
  digitalWrite(D9, HIGH);

  // battery charging enable with high current 100mA > 50mA
  pinMode(P0_13, OUTPUT);
  digitalWrite(P0_13, LOW);

  Serial.begin(115200);
  if (!Serial)
    delay(1000);
  Serial.println("BLE Antivol Peripheral");

  // Timer
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, timerHandler)) // Interval in microsecs
  {
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(millis());
  }
  ISR_Timer.setInterval(TIMER_INTERVAL_120S, GPSIsr);

  bleSetup();
  Serial.println(" bleSetup");
  imuSetup();
  Serial.println(" imuSetup");
  gpsSetup();
  Serial.println(" gpsSetup");
  Serial2.begin(9600);
  delay(100);
  sim800l = new SIM800L((Stream *)&Serial2, SIM800_RST_PIN, 200, 512);
  pinMode(SIM800_DTR_PIN, OUTPUT);
  delay(1000);
  simSetup();
  Serial.println("SIM SETUP");

  analogReadResolution(ADC_RESOLUTION); // setup battery reading
  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  digitalWrite(VBAT_ENABLE, LOW);

  Serial.println("fin setup ");
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  temps();

  Serial.print("Battery level: ");
  Serial.println(getBatteryLevel());
}

//--------------------------- LOOP -----------------------------
void loop()
{
  if (activation_alarm)
  {
    pulseBuzzer(2, 200, 50, 25);
    activation_alarm = false;
  }

  motion_data = getMotionData();
  rotation_data = getRotationData();
  Config.isActivate = 1; // TO REMOVE !!!
  if (Config.isActivate)
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
      send_move = true;
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

  if (!motion_small && !motion_big && alarm_duration - alarm_start < time_limit)
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
      if (alarm_duration - alarm_start >= time_limit)
      {
        alarm_start = millis();
      }
    }
  }

  if ((motion_big || motion_small) && MT_counter > 2)
  {
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
      bleSetup();
    }
  }

  // bluetooth actived when we are interacting with the module or when the alarm is on
  if ((BLE_activated == true) || (Config.isActivate))
  {
    BLE.poll(); // communication autorisé
  }

  // at the end of the time during which the lock has not moved, if bluetooth is activated, and the lock is not in activation mode then it is turned off to save the battery
  if ((millis() - tim_connec > TIME_OUT_MS_BLE_ACT) && (BLE_activated == true) && (Config.isActivate != 1))
  {
    BLE_activated = false;
    Serial.println("timeout->BLE_END");
    BLE.end();
  }

  //   //capture clocked GPS data
  //   GPS.read();
  //   if (GPS.newNMEAreceived()) {
  //     Serial.print(GPS.lastNMEA());    // this also sets the newNMEAreceived() flag to false
  //     if (!GPS.parse(GPS.lastNMEA()))  // this also sets the newNMEAreceived() flag to false
  //       Serial.println("fail to parse");
  //     ;  // we can fail to parse a   sentence in which case we should just wait for another
  //   }

  //   if (GPS.fix && position_acquired == false) {  // if location detected
  //     Serial.println("fix + false");
  //     position_acquired = true;
  //     GPS.fix = 0;
  //     digitalWrite(GPS_WKUP_PIN, LOW);
  //     GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
  //   }

  //   if (send_move) {  //sending of positions via SIM module
  //     Serial.println("Envoi detection mouvement");
  //     sim800l->setupGPRS("iot.1nce.net");
  //     sim800l->connectGPRS();
  //     String Route = "http://141.94.244.11:2000/sendNotfication/" + BLE.address();
  //     String RouteCoord = "http://141.94.244.11:2000/updateCoordinate/" + BLE.address();
  //     String str = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\"}";
  //     String bat = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryVoltage()) + "\"}";
  //     char position[200];
  //     char posbat[200];
  //     str.toCharArray(position, str.length() + 1);
  //     //Serial.println(str);
  //     bat.toCharArray(posbat, bat.length() + 1);
  //     Serial.println(posbat);
  //     char direction[200];
  //     char directionCoord[200];
  //     Route.toCharArray(direction, Route.length() + 1);
  //     RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
  //     sim800l->doPost(direction, "application/json", position, 10000, 10000);
  //     sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
  //     sim800l->disconnectGPRS();
  //     send_move = false;
  //   }

  // if (send_position) {  //regular sending of positions via SIM module
  //   Serial.println("Envoi regulier position");
  //   sim800l->setupGPRS("iot.1nce.net");
  //   sim800l->connectGPRS();
  //   String RouteCoord = "http://141.94.244.11:2000/updateCoordinate/" + BLE.address();
  //   String bat = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryVoltage()) + "\"}";
  //   char posbat[200];
  //   bat.toCharArray(posbat, bat.length() + 1);
  //   Serial.println(posbat);
  //   Serial.println(RouteCoord);
  //   char directionCoord[200];
  //   RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
  //   sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
  //   sim800l->disconnectGPRS();
  //   send_position = false;
  // }

  if (getBatteryLevel() <= 20) // if Vmin is reached
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

void temps(void)
{
  unsigned long millisPassed = millis();
  unsigned int seconds = (millisPassed / 1000) % 60;
  unsigned int minutes = (millisPassed / (1000 * 60)) % 60;
  unsigned int hours = (millisPassed / (1000 * 60 * 60)) % 24;
  Serial.print("Détecté a : ");
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
