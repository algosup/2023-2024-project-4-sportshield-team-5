
#include "bluetooth.h"
#include "buzzer.h"
#include "motionDetection.h"
#include "sim.h"
#include "gps.h"
#include "battery.h"

//-------------------------------- SETUP ----------------------------------------
void setup()
{
  pinMode(buzzerPin, OUTPUT); // setup for buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  Serial.println(" buzzer");

  pinMode(aimantPin, OUTPUT); // setup electro-aimant
  digitalWrite(aimantPin, HIGH);
  delay(1000);
  digitalWrite(aimantPin, LOW);
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
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler)) // Interval in microsecs
  {
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(millis());
  }
  ISR_Timer.setInterval(TIMER_INTERVAL_120S, GPS_ISR);

  ble_setup();
  Serial.println(" ble_setup");
  imu_setup();
  Serial.println(" imu_setup");
  gps_setup();
  Serial.println(" gps_setup");
  Serial2.begin(9600);
  delay(100);
  sim800l = new SIM800L((Stream *)&Serial2, SIM800_RST_PIN, 200, 512);
  pinMode(SIM800_DTR_PIN, OUTPUT);
  delay(1000);
  sim_setup();
  Serial.println("SIM SETUP");

  analogReadResolution(ADC_RESOLUTION); // setup battery reading
  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  digitalWrite(VBAT_ENABLE, LOW);

  Serial.println("fin setup ");
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  Temps();

  Serial.print("Battery level: ");
  Serial.println(getBatteryLevel());
}

//--------------------------- LOOP -----------------------------
void loop()
{
  if (ActivationAlarm)
  {
    PulseBuzzer(2, 200, 50, 25);
    ActivationAlarm = false;
  }

  MotionData = getMotionData();
  RotationData = getRotationData();
  Config.isActivate = 1; // TO REMOVE !!!
  if (Config.isActivate)
  { // alarm enalbled
    activateGPS();
    if (MotionData > BigMT || RotationData > BigRT)
    { // Big motion detection
      if (MotionData > BigMT)
      {
        Serial.print("Motion detected : ");
        Serial.println(MotionData);
      }
      else
      {
        Serial.print("Rotation detected : ");
        Serial.println(RotationData);
      }
      MotionBig = true;
      MotionSmall = false;
      send_move = true;
    }
    else if (MotionData > SmallMT || RotationData > SmallRT)
    { // Small motion detection
      if (MotionData > SmallMT)
      {
        Serial.print("Small motion: ");
        Serial.println(MotionData);
      }
      else
      {
        Serial.print("Small rota : ");
        Serial.println(RotationData);
      }
      MotionSmall = true;
    }
  }

  if (!MotionSmall && !MotionBig && AlarmDuration - AlarmStart < TimeLimit)
  {
    MTCounter = 0;
    FirstAlarm = true;
  }
  if (MotionSmall || MotionBig)
  {
    MTCounter++;
    if (FirstAlarm && MTCounter >= 2)
    {
      AlarmStart = millis();
    }
    else
    {
      AlarmDuration = millis();
      if (AlarmDuration - AlarmStart >= TimeLimit)
      {
        AlarmStart = millis();
      }
    }
  }

  if ((MotionBig || MotionSmall) && MTCounter > 2)
  {
    if (FirstAlarm)
    {
      // Dissuasion alarm
      PulseBuzzer(3, 200, 100, 12); // repetitions, DurationOn , DurationOff, intensity
      FirstAlarm = false;
    }
    else
    {
      // Theft alarm
      PulseBuzzer(5, 350, 350, 25); // repetitions, DurationOn , DurationOff, intensity
    }
  }
  MotionDetect = true;

  // if a mvt is detected and bluetooth is disabled bluetooth activation
  if (MotionDetect == true)
  {
    tim_connec = millis();
    MotionDetect = false;
    if (BLE_activated == false)
    {
      BLE_activated = true;
      Serial.println("MVT_detect->setup");
      ble_setup();
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

  if (getBatteryLevel() < 20)
  {
    deepSleepMode();
  }
}

//------------- ADDITIONAL FUNCTIONS ------------------------------

void Temps(void)
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

void TimerHandler()
{
  ISR_Timer.run();
}
