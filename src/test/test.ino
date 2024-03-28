#include <ArduinoBLE.h>
#define VBAT_ENABLE 14

int oldBatteryLevel = 0;  // last battery level reading from analog input
long previousMillis = 0;  // last time the battery level was checked, in ms
int lowest = 100;
int highest = 0;
int stamp;
int x;
int battery;

void setup() {
  Serial.begin(9600);  // initialize serial communication
  while (!Serial)
    ;

  pinMode(VBAT_ENABLE, OUTPUT);
  pinMode(PIN_VBAT, INPUT);
  digitalWrite(VBAT_ENABLE, LOW);
  // power battery control with the transistor
  pinMode(D9, OUTPUT);
  digitalWrite(D9, LOW);

  // battery charging enable with high current 100mA > 50mA
  pinMode(P0_13, OUTPUT);
  digitalWrite(P0_13, LOW);

  Serial.println("Setup...");
}


void loop() {
  updateBatteryLevel();
}

void updateBatteryLevel() {
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the charge level of a battery.
  */
for (int i= )
  float voltage = analogRead(PIN_VBAT);
  voltage=voltage * (4.2 / 1023.0);
  Serial.println(voltage);
  
    x+=1;
    stamp += voltage;
    stamp = (stamp*(x-1)+stamp)/x;
  }else{
    battery = stamp;
    stamp = 0;
    x = 0;
    Serial.print("battery level : ");
    if (battery > 4.1) {
      Serial.println("100%");
    } else if (battery > 4.0) {
      Serial.println("90%");
    } else if (battery > 3.9) {
      Serial.println("80%");
    } else if (battery > 3.85) {
      Serial.println("70%");
    } else if (battery > 3.8) {
      Serial.println("60%");
    } else if (battery > 3.75) {
      Serial.println("50%");
    } else if (battery > 3.72) {
      Serial.println("40%");
    } else if (battery > 3.7) {
      Serial.println("30%");
    } else if (battery > 3.65) {
      Serial.println("20%");
    }
    else{
      Serial.println("Warning! battery under 20%!");
    }
  }
  



  


}