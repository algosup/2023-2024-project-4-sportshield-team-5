#ifndef _SIM_
#define _SIM_
#include "definitions.h"
#include "bluetooth.h"

/*
    This file contains every functions related to the SIM card.
*/

//---------------------------- SETUP -----------------------------

/**
 * This function starts the SIM800L module to enable the use of mobile network. WIP
 * @param None
 * @result None.
 */
void simSetup(void)
{



    // while (!sim800l->isReady())
    // {
    //     Serial.println(F("Problem to initialize AT command, retry in 1 sec"));
    //     digitalWrite(LEDR, !digitalRead(LEDR));
    //     delay(1000);
    // }
    // sim800l->enableEchoMode();
    // sim800l->setupGPRS("iot.1nce.net");

    // uint8_t signal = sim800l->getSignal();
    // while (signal <= 0)
    // {
    //     delay(1000);
    //     signal = sim800l->getSignal();
    // }
    // Serial.println(String(signal));
    // NetworkRegistration network = sim800l->getRegistrationStatus();
    // // while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
    // //   delay(1000);
    // //   network = sim800l->getRegistrationStatus();
    // //   Serial.print(network + " ");
    // //   Serial.println(F("Problem to register, retry in 1 sec"));
    // //   digitalWrite(LEDG, !digitalRead(LEDG));
    // // }
    // delay(50);
    // sim800l->setPowerMode(MINIMUM);     // set minimum functionnality mode
    // digitalWrite(SIM800_DTR_PIN, HIGH); // put in sleep mode
}
//-------------------------- FUNCTIONS ---------------------------
void SIMIsr()
{
    send_position = true;
}

void sendLocationBattery(){
  if(Device.gps_desactivated){
    activateGPS();
  }
  turnPowerBridges(ON);

  Serial.println("Location and battery sent");
  //SEND GPS DATA BATTERY/LOCATION

  if (!Device.alarm_triggered){
    desactivateGPS();
    turnPowerBridge(OFF);
  }

void launchRegularSent(){
  regular_sent_timer_start = millis();
}
void updateRegularSent(){
  regular_sent_timer = millis() - regular_sent_timer_start;
  if (regular_sent_timer >= SENDING_FREQUENCY_WHEN_LOCKED){
    sendLocationBattery();
    regular_sent_timer_start = millis();
  }
}
void resetRegularSent(){
  regular_sent_timer_start = 0;
  regular_sent_timer = 0;
}

#endif